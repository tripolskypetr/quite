#ifndef TIMEREXTENSION_H
#define TIMEREXTENSION_H

#include <QHash>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QRandomGenerator>
#include <QJSValueIterator>

#include "src/monitors/timermonitor.h"
#include "src/events/throwerror.h"
#include "src/base/extension.h"
#include "src/events/await.h"

using namespace Quite::Base;

namespace Quite {
namespace Extensions {

/*****************************************************************************/

class TimerExtension : public Extension {
  Q_OBJECT
  private:
    QHash<int, Monitors::TimerMonitor*> timers;
    int append(Monitors::TimerMonitor* timer);
    const int MAXIMUM_TIMERS = 1000;
    QRandomGenerator generator;
  public:
    explicit TimerExtension(QObject* parent = nullptr);
    virtual ~TimerExtension();
    virtual void install(
        QJSValue global,
        QJSValue current,
        QJSEngine* eval
    );
  public slots:
    QJSValue setTimeout(QJSValue handler, QJSValue timeout);
    QJSValue clearTimeout(QJSValue timeout);
  private slots:
    void clearPointer(int id);
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // TIMEREXTENSION_H
