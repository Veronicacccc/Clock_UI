
#ifndef TIMESETTER_H
#define TIMESETTER_H

#include <QTime>

#include "setter.h"

class TimeSetter : public Setter
{
public:
    TimeSetter();
    void setTime(QTime time);
    QTime finishSetting();
    void updateBound();
    int check();
    int hour();
    int minute();
    int second();
};

#endif // TIMESETTER_H
