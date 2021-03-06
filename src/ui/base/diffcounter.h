#ifndef DIFFCOUNTER_H
#define DIFFCOUNTER_H

#include <QtDebug>
#include <QObject>
#include <QMutex>

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class DiffCounter : public QObject {
  Q_OBJECT
  private:
    bool rendering=false;
    int resolveCounter=0;
    QMutex locker;
  private:
    explicit DiffCounter();
    virtual ~DiffCounter();
  public:
    bool tryIncrementCounter();
    void decrementCounter();
    Q_DECL_DEPRECATED bool tryBeginRender();
    Q_DECL_DEPRECATED void endRender();
    bool changesResolved();
  public:
    static DiffCounter* instance();
  signals:
    void diffFree();
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // DIFFCOUNTER_H
