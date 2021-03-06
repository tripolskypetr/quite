#include "wrapper.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

void Wrapper::check(bool found) {
    if(!found){
        qCritical() << "Wrapper" << property << "invalid params";
    }
}

/*---------------------------------------------------------------------------*/

Wrapper::Wrapper(
    QObject* origin,
    QString property,
    QJSEngine* eval,
    QObject* engine)
  : QObject(origin) {
    qDebug() << "Wrapper ctor";
    this->property = property;
    this->engine = engine;
    this->origin = origin;
    this->eval = eval;
}

/*---------------------------------------------------------------------------*/

Wrapper::~Wrapper() {
    qDebug() << "Wrapper dtor";
}

/*---------------------------------------------------------------------------*/

QJSValue Wrapper::call(
    QJSValue p1,
    QJSValue p2,
    QJSValue p3,
    QJSValue p4,
    QJSValue p5,
    QJSValue p6,
    QJSValue p7,
    QJSValue p8,
    QJSValue p9,
    QJSValue p10
) {
    qDebug()
        << "Wrapper call"
        << p1.toString()
        << p2.toString()
        << p3.toString()
        << p4.toString()
        << p5.toString()
        << p6.toString()
        << p7.toString()
        << p8.toString()
        << p9.toString()
        << p10.toString();

    QJSValue result;
    if(p1.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result)
        ));
    } else if(p2.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine))
        ));
    } else if(p3.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine))
        ));
    } else if(p4.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine))
        ));
    } else if(p5.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine))
        ));
    } else if(p6.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval,engine))
        ));
    } else if(p7.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p6,eval,engine))
        ));
    } else if(p8.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p6,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p7,eval,engine))
        ));
    } else if(p9.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p6,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p7,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p8,eval,engine))
        ));
    } else if(p10.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p6,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p7,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p8,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p9,eval,engine))
        ));
    } else {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p6,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p7,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p8,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p9,eval,engine)),
            Q_ARG(QJSValue, Emitter::fromObject(p10,eval,engine))
        ));
    }

    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue Wrapper::fromQObject(
    QObject *engine,
    QObject *obj,
    QJSEngine *eval
) {
    QJSValue object = eval->newQObject(obj);
    QJSValue result = eval->newObject();
    QJSValueIterator it(object);

    while (it.hasNext()) {
        it.next();

        if(it.value().isCallable()) {
            Wrapper* wrapped = new Wrapper(obj, it.name(), eval, engine);
            QJSValue managed = eval->newQObject(wrapped);
            QQmlEngine::setObjectOwnership(wrapped, QQmlEngine::CppOwnership);
            result.setProperty(it.name(),managed.property("call"));
        } else {
            result.setProperty(it.name(),it.value());
        }

    }
    return result;
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
