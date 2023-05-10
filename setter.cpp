#include "setter.h"
#include <QDebug>


Setter::Setter()
{
    this->index = 0;
}

void Setter::apply()
{
    index++;
    if(index == length)
    {
        index = 0;
    }
    this->updateBound();
    //    qDebug() << "index:" << index << "length:" << length;
}

void Setter::inc()
{
    nums[index]++;
    if(nums[index] == 10)
    {
        nums[index] = 0;
    }
    int check = this->check();
    // qDebug() << "check:" << check;
    if(check < 0)
    {
        nums[index]++;
        if(nums[index] == 10)
        {
            nums[index] = 0;
        }
    }
    else if(check > 0)
    {
        nums[index] = 0;
    }
}

QString Setter::toString()
{
    QString str = "";
    for(int i = 0; i < length; i++)
    {
        str += QString::number(nums[i]);
        if(i == index)
        {
            str += ".";
        }
    }
    return str;

}
