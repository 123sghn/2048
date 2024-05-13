#include "timethread.h"
#include <QTime>

TimeThread::TimeThread(QObject* parent) : QThread(parent)
{

}

void TimeThread::run()
{
    //线程任务
    while(1)
    {
        sleep(1); //延时
        emit addTime(); //通过信号把时间发送出去
    }
}
