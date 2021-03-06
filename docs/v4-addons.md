
# Архитектурная надстройка JavaScript интерпретатора

Как было упомянуто на основной статье данного руководства программиста программного обеспечения, фреймворк расширяет функциональность JavaScript интерпретатора [V4](https://wiki.qt.io/V4). В этом документе будут расписаны доводы, послужившие катализатором выбора именно этого движка, а так же описание особенностей его публичного API и архитектуры дополнения.

## Критерии выбора JavaScript интерпретатора

В процессе выбора JavaScript интерпретатора были выделены следующие критерии:

 - Отсутствие вкроплений не C++ кода 

    Например, Objective-C. Это связано с основным требованием к данному программному обеспечению, выроженным максимальной переносимостью между операционными системами и [компиляторами](https://ru.stackoverflow.com/questions/1021524/Заголовочные-файлы-при-использовании-шаблонных-классов-c-с-компилятором-clang)

 - Возможность компиляции без развертки тяжелой системы сборки

    С ходом времени, все большее колличество C++ разработчиков отказываются от общепринятого способа размещения зависимостей проекта внутри поддиректории ["third party"](https://en.wikipedia.org/wiki/Third-party_software_component) в пользу применения тяжеловесных систем сборки проекта (например, [Bazel](https://bazel.build/)). В огромных программах это оправдано, но скачивать более 15 гигабайт хлама ради компиляции этого инструмента не рационально из-за розни с целями проекта.

    Как следствие, необходимо к разрешению:

    1. Не более 25-50 заголовочных файлов
        
        Вероятность совпадения имен объектных модулей при сборке.

    2. Потенциальная возможность переноса на QMake

        На текущий момент разворачивается тренд на применение утилиты CMake во всех C++ проектах глобально. В приоретете перенос на QMake в связи с безотказностью работы. 

 - Корпоративная поддержка

    Некоторые open source JavaScript интерпретаторы являются "toy project": поддержка ES6 выборочная, последний коммит в "2015". Это не серьезно.

## Выбор JavaScript интерпретатора. Анализ потенциальных движков

 - [Duktape](https://duktape.org/)

    Легковесный JavaScript интерпретатор без JIT для интеграции в существующее программное обеспечение в качестве движка скриптинга.

    #### Причина отказа:
    
    На момент августа 2019 частичная поддержка ES5 в синтаксисе [стрелочных функций](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Functions/Arrow_functions). Случайный код работает некорректно при правильном синтаксисе. Фатальный недостаток.

 - [JavaScriptCore](https://github.com/WebKit/webkit/tree/master/Source/JavaScriptCore)

    Популярнейший JavaScript интерпритатор с JIT ускорением от Apple. Применяется везде: Nintendo Switch, Sony Playstation, iPhone Safary, Mac Safary и др. Рассматривалась версия интерпретатора, [совместимая с iOS 6](https://github.com/phoboslab/JavaScriptCore-iOS) как с самым слабым звеном. 

    #### Причина отказа:
    
    Отказ от поддержки данной версии последующими версиями iOS, вкропления кода Objective-C (Фатально)

 - [V8](https://v8.dev/)

    JavaScript интерпретатор, применяемый в Google Chrome и NodeJS

    #### Причина отказа:
    
    Отсутствие официального GitHub репозитория (неудобно качать). Полупроприетарная утилита для сборки проекта GN (["This is awesome! I've been waiting for a standalone GN for ages!!"](https://www.reddit.com/r/cpp/comments/90vabm/gn_a_metabuild_system_that_generates_build_files/)). Слишком сложно расширять и поддерживать на целевом множестве платформ при текущих финансовых ограничениях (фатально).

 - [JerryScript](https://github.com/jerryscript-project/jerryscript)

    Встраиваемый JavaScript интерпретатор от Samsung для устройств интернета вещей

    #### Причина отказа:
    
    Перемещение из-под крыла Samsung в обособленную open source организацию. Применение C99 в реализации (Фатально)

 - [KJS](https://github.com/KDE/kjs)

    JavaScript интерпретатор от разработчиков KDE. По ощущениям, это JavaScriptCore без Objective-C вкроплений в исходном коде и потенциально браузерно обвеса (например, WebAssembly). Примечательно, что исходный код реализован без библиотеки Qt и набор привязок поставляется [отдельно](https://github.com/KDE/kjsembed): потенциально большая масштабируемость.

    #### Причина отказа:
    
    Минусом данного решения является отсутствие обновлений с 2015 года. Мне неизвество, есть ли поддержка современных стандартов JavaScript. Было решено копать дальше.

 - [Hermes](https://github.com/facebook/hermes)

    Относительно новый (начало 2019) JavaScript интерпретатор от FaceBook,созданный с поправкой на React Native и мобильные операционные системы.

    #### Причина отказа:
    
    Слишком не спелый. Я не нашел публичного стабильного API прикладного программиста.

 - [V4](https://wiki.qt.io/V4)

    Встроенный в библиотеку Qt5 JavaScript интерпретатор с поддержкой ES6, JIT компиляцией и стабильным публичным API, выраженным абстракией (потенциально возможно переопределение с безболезненным переносом на другой движок, есть альтернативная реализация поверх V8). Это и послужило основной причиной выбора

    #### Недостатки:
    
    Отсутствие публичного API для [отладки](https://stackoverflow.com/questions/38064798/debugging-qjsengine) с момента появления в библиотеке. Сам движок реализует, но его API не публичное. В перспективе нужна реализация, оттолкнуться можно от родителя [QtScript](https://doc.qt.io/archives/qt-4.8/qscriptenginedebugger.html).

## Особенности публичного API движка V4

Библиотека Qt5 реализует публичное API поверх JavaScript интерпретатора V4. Оно выражено двумя классами: [QJSValue](https://doc.qt.io/qt-5/qjsvalue.html) и [QJSEngine](https://doc.qt.io/qt-5/qjsengine.html). Через первый мы можем манипулировать JavaScript значениями (вызвать функции, преобразовывать результат работы функций в C++ значение), через последний создавать функции или значения (передача аргументов в параметры) и вызывать сборщик мусора. Подразумевается, что в целях скриптинга приложение исполняет исключительно синхронный JavaScript код. Как следствие, цикл событий пришлось реализовать самостоятельно.

## Цикл событий фреймворка

В процессе развертки приложения классом Application запускается Engine - наследник QThread, который содержит в методе QThread::run() бесконечный цикл с исполнением очереди событий из локального [QEventLoop](https://doc.qt.io/archives/qt-4.8/qeventloop.html) (цикл событий **нового потока**). При этом сам объект [фильтрует](https://doc.qt.io/qt-5/qobject.html#installEventFilter) события и обрабытывает [только](https://doc.qt.io/qt-5/qevent.html#registerEventType) внутренние события фреймворка (**события механизма сигналов-слотов** и другие пробрасываются далее в QEventLoop)

Подразумевается, что расширение глобального объекта не исполняет вызываемое QJSValue синхронно, а бросает в очередь класса Engine с использованием [QCoreApplication::sendEvent()](https://doc.qt.io/qt-5/qcoreapplication.html#sendEvent). Данный процесс автоматизирован оберткой всех слотов через специальную прослойку **Wrapper**, об этом ниже.

## Подробнее о Wrapper и Emitter

Библиотека Qt реализует инструментарий, позволяющий ["перебросить"](https://doc.qt.io/qt-5/qjsengine.html#newQObject) слот наследника QObject в поле объекта на стороне JavaScript, выраженное функцией. Слот исполняется синхронно(Qt::ConnectionType::DirectConnection) в том же потоке, так как **может вернуть на сторону JavaScript значение**.

Таким образом, [коллбеки](https://ru.wikipedia.org/wiki/Callback_(программирование)) из параметров по умолчанию будут выполняться не через цикл событий, а синхронно (без нашего вмешательства). Для решения этого вопроса, была создана обертка Wrapper. По принципу работы [декораторов ES2016](https://habr.com/ru/post/277021/) она подменяет подаваемые значения аргументов в параметры слота, если они вызываемы (не вызываемые просто игнорируются). Именно так вызов коллбека происходит не на прямую, а через итерацию цикла событий.

Для пробросса вызова QJSValue в цикл событий был создан класс Emitter. Emitter оборачивает собой данное ему значение и при вызове бросает его в цикл событий. Для удобства, оригинальное значение прописывается в прототип как поле _emitterOrigin.

## Класс Extension

Расширения устанавливаются пробросом специального собыия в цикл событий фреймворка. Расширение наследует от базового класса Extension и должно реализовать данный абстрактный метод:
```
virtual void install(
    QJSValue global,
    QJSValue current,
    QJSEngine* eval
) = 0;
```
Где global - контейнер QJSValue глобального объекта JavaScript интерпретатора, current - сам обработанный через Wrapper наследник Extension (см выше). 

## Класс Monitor

События QEventLoop не могут быть отложены штатным образом - они живут в очереди на удаление и процесс невозможно прервать. Поэтому, когда необходимо дождаться какого-либо результата, применяется наследование от класса Monitor.
```
virtual bool isStarted() = 0;
virtual bool isCanceled() = 0;
virtual bool isFinished() = 0;
virtual void start(
    QThreadPool* pool,
    QJSEngine* eval,
    QObject* engine
) = 0;
```
Переопределяемые абстрактные методы должны быть потокобезопасными. Отдельное событие получает в конструкторе указатель на наследника Monitor, но не удаляет его в деструкторе. При поступлении события в исполнение проверяется, закончил ли "монитор мониторить". Зависимо от результата проверки, возвращается разное значение. Именно сам Engine складывает мониторы в [QStack](https://ru.wikipedia.org/wiki/FIFO)(до тех пор, пока "мониторят") и, когда все события выполнены, достает (проброс новых событий в цикл).

## Когда приложение завершается?

Классически, когда очередь событий пуста. Но, есть исключение - наличие открытых окон пользовательского интерфейса и не пустой стек мониторов. Собственно говоря, именно для корректного завершения вовремя и был написан свой цикл событий.