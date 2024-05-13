#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QObject>
#include <QThread>

class TimeThread : public QThread
{
    Q_OBJECT

public:
    TimeThread(QObject* parent = nullptr);
    void run();

signals:
    void addTime();
};

#endif // TIMETHREAD_H
