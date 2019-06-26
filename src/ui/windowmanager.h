#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtDebug>
#include <QObject>
#include <QThread>
#include <QList>

#include "src/ui/base/node.h"
#include "src/ui/base/invoker.h"
#include "src/ui/base/component.h"
#include "src/ui/components/window.h"
#include "src/ui/components/button.h"
#include "src/ui/components/rectangle.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {

/*****************************************************************************/

class WindowManager : public QObject {
  Q_OBJECT
  private:
    Components::Window* window = nullptr;
    QQmlEngine engine;
    Invoker invoker;
  public:
    explicit WindowManager(QObject* parent = nullptr);
    virtual ~WindowManager();
  public slots:
    void renderUi(Node* rootNode);
  private:
    Component* renderComponent(Node* node, Component* parent = nullptr);
    Component* renderComponentTree(Node* node, Component* parent = nullptr);
  signals:
    void closed();
    void eval(QJSValue func, QJSValueList args);
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // WINDOWMANAGER_H
