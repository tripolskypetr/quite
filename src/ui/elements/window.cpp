#include "window.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Window::Window(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Window.qml")),
        node,
        engine,
        nullptr
    ) {
    qDebug() << "Window ctor";
    if(parent!=nullptr) {
        qCritical() << "Window parent must be nullptr";
    } else {
        window = qobject_cast<WindowComponent*>(getItem());
        connect(
            window,
            SIGNAL(closed()),
            this,
            SIGNAL(closed())
        );
        connect(
            window,
            SIGNAL(resize()),
            this,
            SLOT(updateLayout())
        );
        startLayoutUpdate();
        /*
         * Default props place
         */
        //window->setProperty("alignItems","center");
        //window->setProperty("justifyContent","center");
    }
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

void Window::propsChanged() {
    qDebug() << "Window propsChanged";
    window->commitWindowProps(getProps());
    Element::propsChanged();
}

/*---------------------------------------------------------------------------*/

FlexNode* Window::buildFlexTree(bool fill) {
    qDebug() << "Window updateLayout";
    Q_UNUSED(fill)
    FlexNode* layout = new FlexNode(
        getItem(),
        window->getHeight(),
        window->getWidth()
    );
    QLinkedList<Element*> child=getChild();
    QLinkedList<Element*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        layout->appendChild((*iter)->buildFlexTree(
            false
        ));
        (*iter)->startLayoutUpdate();
    }
    return layout;
}

/*---------------------------------------------------------------------------*/

void Window::updateLayoutNow(int h, int w) {
    Q_UNUSED(h)
    Q_UNUSED(w)
    qDebug() << "Window updateLayoutNow";
    if (!initialRenderComplete) {
        layout=buildFlexTree();
        layout->printTree();
        layout->buildTree();
        layout->calculateLayoutLtr(
            window->getHeight(),
            window->getWidth()
        );
        initialRenderComplete=true;
    } else {
        Element::updateLayoutNow();
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
