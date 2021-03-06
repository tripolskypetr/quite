#ifndef WINDOW_H
#define WINDOW_H

#include <QtDebug>
#include <QObject>
#include <QVariant>

#include "src/ui/component.h"
#include "src/ui/base/element.h"
#include "src/ui/base/diffcounter.h"
#include "src/ui/qml_components/windowcomponent.h"

using namespace Quite::Ui;
using namespace Quite::Ui::Base;
using namespace Quite::Ui::QmlComponents;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Window : public Element {
  Q_OBJECT
  private:
    WindowComponent* window;
    bool initialRenderComplete=false;
  public:
    Window(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Window() override;

  /*
   * Проброс свойств окна
   */
  public slots:
    virtual void propsChanged() override;

  /*
   * Переопределение перерисовки с передачей размера окна
   */
  public slots:
    virtual FlexNode* buildFlexTree(bool fill=false) override;

  /*
   * Переопределение для создания инициализирующего древа
   * компоновки
   */
  protected:
    virtual void updateLayoutNow(int H, int W) override;

  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
