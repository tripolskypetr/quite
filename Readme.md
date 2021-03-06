
# QuiteJS

> Альтернатива ElectronJS, выраженная кастомной JSX factory с diff рендерингом компонентов и визуальными элементами из библиотеки Qt. Наконец-то флексбокс со скроллингом без костылей!

![Демонстрация](main.gif)

Код, запущенный на гифке можно посмотреть [тут](main.js)

## Good night, sweet prince (deprecated)

В процессе реализации этого инструмента я понял, что существует [имбовый способ](https://github.com/tripolskypetr/material-ui-umd/blob/master/packages/how-it-is-made/README.md) обойти проблему отсутствия типизации TypeScript и невозможности генерации оной для umd дистрибутивов JavaScript проектов, гвоздями прибитых к WebPack или другим бандлерам. В итоге я [таки запилил](https://github.com/tripolskypetr/material-ui-umd/blob/master/packages/form-generator-app/README.md) инструмент для офлайн разработки на TypeScript + React без сторонних зависимостей и бандлеров, а так же подключения к интернету как такового вообще, но сделано это было уже без C++. Под капотом используется весьма проработанный готовый набор компонентов `material-ui`, который отлично ведет себя как на десктопе, так и мобильных устройствах. Я оставлю этот репозиторий, так как в академических целях этот проект остается интересным...

## Документы
 - [Брифинг](docs/briefing.md)
 - [Рендеринг пользовательского интерфейса](docs/diff-render.md)
 - [Компоновка пользовательского интерфейса](docs/flex-layout.md)
 - [Архитектура надстройки javascript интерпретатора](docs/v4-addons.md)

## Запуск

В Qt Creator задайте дополнительные параметры командной строки при запуске, которые включат логгирование и укажут директорию, где должен лежать файл "точка входа" main.js

```
--path /Users/tripolskypetr/Quite -v
```

## Что это?

Малоизвестный JavaScript движок [V4](https://wiki.qt.io/V4), разработанный компанией Nokia как **«элегантное оружие более цивилизованной эпохи»**, к глобальному объекту которого прикручено бесчисленное множество классных штук. Последний описан в формате [файлов декларации](https://www.typescriptlang.org/docs/handbook/namespaces.html#ambient-namespaces) TypeScript, что позволяет программировать на этом языке без *npm-иглы*, из-за которой каждый день твой проект рискует не собраться, так как неизвестно, с каких именно интернет-ресурсов и что качают зависимости. Это очень полезно, когда в проекте один-два человека (фриланс). Также, **пропадает нужда в «Я его слепила из того, что было»**.

Утилита включает в себя (когда будет готова):

 - JSX factory для построения UI с использованием примитивов [Qt Quick Controls 2](https://doc.qt.io/qt-5/qtquickcontrols-index.html). Встроенный аналог [Redux](https://getinstance.info/articles/react/learning-react-redux/), компоненты с тем же `this.setState()`.
 - Помимо `alert()` и `prompt()` синхронные диалоги для выбора файлов, дат, времени.
 - Встроенный в платформу конфигуратор (~~привет 1C~~), позволяющий смотреть логи (все действия платформы логгируются чуть ли не до вызова функций), смотреть состояние приложения, смотреть древо компонентов. Доступен в отдельном окне при запуске с флагом `-d` 
 - Вкомпилированая копия SQLite, не нужно бояться, что у заказчика не стартанет драйвер.
 - Классы для Http запросов, [WebSocket](https://ru.wikipedia.org/wiki/WebSocket) клиент. Последний гарантирует очередность запросов, что позволяет применить [функциональное программирование](https://ru.wikipedia.org/wiki/Функциональное_программирование) на стороне сервера (синхронизировать Redux контейнер и состояние клиента на сервере, транслируя вызываемые Action)

## Зачем это?

 - Эстетическая красота кода (для тех, кто не может жить без [namespace](https://www.typescriptlang.org/docs/handbook/namespaces.html#namespaced-validators))
 - Попытка отказа от практики качать всё и вся из npm, где в 2k19 не завезли [модерацию пакетов](https://www.npmjs.com/search?q=hello-world)
 - Попытка дать отпор насаждаемой монополии [cdn модулей](https://ru.stackoverflow.com/questions/927526/Почему-NodeJS-так-долго-не-реализует-поддержку-модулей-ES6) для JavaScript
 - Наконец-то получить инструмент, который гарантирует запуск прикладной программы при любых условиях - полностью изолированный рантайм. ~~И это не Docker, который git clone из master ветки делает~~
