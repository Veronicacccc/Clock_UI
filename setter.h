#ifndef SETTER_H
#define SETTER_H

#include<string>
#include<vector>
#include<QString>
#include<QDebug>

class Bound
{
public:
    Bound(){};
    Bound(int min, int max) : min(min), max(max) {}
    int getMin() {return min;}
    int getMax() {return max;}
    void setMin(int min) {this->min = min;}
    void setMax(int max) {this->max = max;}

    Bound& operator=(const Bound& b)
    {
        this->min = b.min;
        this->max = b.max;
        return *this;
    }

private:
    int min;
    int max;
};

class Setter
{
public:
    Setter();
    void apply();
    void inc();
    QString toString();
    virtual int check() {return 0;}
    virtual void updateBound(){
        // qDebug() << "Setter updateBound is called";
    };
private:



protected:
    int index;
    int length;
    std::vector<int> nums;
    std::vector<Bound> bounds;
    std::vector<int> lengths;

};

#endif // SETTER_H
