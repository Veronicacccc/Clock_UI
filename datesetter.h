#ifndef DATESETTER_H
#define DATESETTER_H

#include <QDate>
#include "setter.h"


class DateSetter : public Setter
{
public:
    DateSetter();
    void setDate(QDate date);
    QDate finishSetting();
    void updateBound();
    int check();
    int year();
    int month();
    int day();
private:
    QCalendar cal;
};

#endif // DATESETTER_H
