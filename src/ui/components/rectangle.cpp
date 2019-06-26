#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Rectangle::Rectangle(Node *node, QQmlEngine* engine, Component* parent)
  : Component(node, engine, parent) {
    qDebug() << "Rectangle ctor";
    QQmlComponent rect(engine, ":/qml/Rectangle.qml");
    item = qobject_cast<QQuickItem*>(rect.create());
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
    delete item;
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
