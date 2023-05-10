#include "datesetter.h"
#include <QDebug>
#include <QCalendar>

DateSetter::DateSetter(): Setter()
{
    this->nums = std::vector<int>();
    this->bounds = std::vector<Bound>(3);
    this->cal = QCalendar();
    this->length = 8;
}
void DateSetter::setDate(QDate date)
{
    nums.clear();
    int day = date.day();
    int cnt = 0;
    while(day || cnt < 2)
    {
        nums.push_back(day % 10);
        day /= 10;
        cnt++;
    }

    int month = date.month();
    cnt = 0;
    while(month || cnt < 2)
    {
        nums.push_back(month % 10);
        month /= 10;
        cnt++;
    }

    int year = date.year();
    cnt = 0;
    while(year || cnt < 4)
    {
        nums.push_back(year % 10);
        year /= 10;
        cnt++;
    }
    this->index = 0;
    std::reverse(nums.begin(), nums.end());
    this->updateBound();
}

int DateSetter::year()
{
    int year = 0;
    for(int i = 0; i < 4; i++) {
        year += nums[i] * pow(10, 3 - i);
    }
    return year;
}

int DateSetter::month()
{
    int month = 0;
    for(int i = 4; i < 6; i++) {
        month += nums[i] * pow(10, 5 - i);
    }
    return month;
}

int DateSetter::day()
{
    int day = 0;
    for(int i = 6; i < 8; i++) {
        day += nums[i] * pow(10, 7 - i);
    }
    return day;
}

void DateSetter::updateBound()
{
    // qDebug() << "DatteSetter updateBound is called";
    bounds[0] = Bound(0, 9999);
    bounds[1] = Bound(1, 12);
    bounds[2] = Bound(1, cal.daysInMonth(this->month(), this->year()));
    // qDebug() << "year:" << this->year() << "month:" << this->month() << "day:" << this->day();
    // qDebug() << "bound:" << bounds[0].getMin() << bounds[0].getMax() << bounds[1].getMin() << bounds[1].getMax() << bounds[2].getMin() << bounds[2].getMax();
}

int DateSetter::check()
{
    int year = this->year();
    int month = this->month();
    int day = this->day();
    if(year < bounds[0].getMin())
    {
        return -1;
    }
    if(year > bounds[0].getMax())
    {
        return 1;
    }
    if(month < bounds[1].getMin())
    {
        return -2;
    }
    if(month > bounds[1].getMax())
    {
        return 2;
    }
    if(day < bounds[2].getMin())
    {
        return -3;
    }
    if(day > bounds[2].getMax())
    {
        return 3;
    }
    return 0;
}

QDate DateSetter::finishSetting()
{
    int year = this->year();
    int month = this->month();
    int day = this->day();

    return QDate(year, month, day);
}
