#ifndef TIMERMONITOR_H
#define TIMERMONITOR_H

#include <QTimer>
#include <QtDebug>
#include <QObject>
#include <QJSValue>

#include "src/base/monitor.h"

using namespace Quite::Base;

namespace Quite {
namespace Monitors {

/*****************************************************************************/

class TimerMonitor : public Base::Monitor{
  Q_OBJECT
  private:
    QJSValue handler;
    QTimer* timer = nullptr;
    bool started = false;
    bool canceled = false;
    bool finished = false;
    bool singleshot = false;
    int msec = 0;
    int id = -1;
  public:
    void setId(int id);
    TimerMonitor(
        QJSValue handler,
        int msec,
        bool singleshot = true
    );
    virtual ~TimerMonitor();
    virtual bool isStarted();
    virtual bool isCanceled();
    virtual bool isFinished();
    virtual void start(QThreadPool* pool, QJSEngine* eval, QObject* engine);
    void cancel();
  private slots:
    void tick();
  signals:
    void clear(int id);
};

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite

#endif // TIMERMONITOR_H
