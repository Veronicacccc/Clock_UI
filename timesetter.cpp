
#include "timesetter.h"

TimeSetter::TimeSetter(): Setter()
{
    this->nums = std::vector<int>();
    this->bounds = std::vector<Bound>(3);
    this->length = 6;
}

void TimeSetter::setTime(QTime time)
{
    nums.clear();
    int cnt;

    int second = time.second();
    cnt = 0;
    while(second || cnt < 2)
    {
        nums.push_back(second % 10);
        second /= 10;
        cnt++;
    }

    int minute = time.minute();
    cnt = 0;
    while(minute || cnt < 2)
    {
        nums.push_back(minute % 10);
        minute /= 10;
        cnt++;
    }

    int hour = time.hour();
    cnt = 0;
    while(hour || cnt < 2)
    {
        nums.push_back(hour % 10);
        hour /= 10;
        cnt++;
    }

    this->index = 0;
    std::reverse(nums.begin(), nums.end());
    this->updateBound();
}

int TimeSetter::hour()
{
    int hour = 0;
    for(int i = 0; i < 2; i++) {
        hour += nums[i] * pow(10, 1 - i);
    }
    return hour;
}

int TimeSetter::minute()
{
    int minute = 0;
    for(int i = 2; i < 4; i++) {
        minute += nums[i] * pow(10, 3 - i);
    }
    return minute;
}

int TimeSetter::second()
{
    int second = 0;
    for(int i = 4; i < 6; i++) {
        second += nums[i] * pow(10, 5 - i);
    }
    return second;
}

void TimeSetter::updateBound()
{
    bounds[0] = Bound(0, 23);
    bounds[1] = Bound(0, 59);
    bounds[2] = Bound(0, 59);
}

int TimeSetter::check()
{
    int hour = this->hour();
    int minute = this->minute();
    int second = this->second();
    if(hour < bounds[0].getMin())
    {
        return -1;
    }
    if(hour > bounds[0].getMax())
    {
        return 1;
    }
    if(minute < bounds[1].getMin())
    {
        return -2;
    }
    if(minute > bounds[1].getMax())
    {
        return 2;
    }
    if(second < bounds[2].getMin())
    {
        return -3;
    }
    if(second > bounds[2].getMax())
    {
        return 3;
    }
    return 0;
}

QTime TimeSetter::finishSetting()
{
    int hour = this->hour();
    int minute = this->minute();
    int second = this->second();

    return QTime(hour, minute, second, 0);
}
