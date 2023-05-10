
#include "widget.h"
#include "ui_widget.h"
#include "QSimpleLed.h"
#include <QPushButton>
#include <Qtime>
#include <QDate>
#include <QLayout>
#include <QTimer>
#include <QDebug>
#include <QtWidgets/QLCDNumber>
#include <QSpacerItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::Widget)
{
    en =false;
    set = false;
    showflag = 0;
    en_watch = false;
    en_alarm = false;

    lcdNumber = new QLCDNumber(this);
    lcdNumber->setHidden(true);
    lcdNumber->setObjectName("lcdNumber");
    lcdNumber->setGeometry(QRect(40, 210, 831, 221));
    lcdNumber->setStyleSheet(QString::fromUtf8(""));
    lcdNumber->setDigitCount(12);

    alarmTime.setHMS(0,0,0);

    ui->setupUi(this);


    alarmled = new QSimpleLed(this, QSimpleLed::GREEN);
    houralarmled = new QSimpleLed(this, QSimpleLed::RED);

    alarmled->setGeometry(QRect(580, 80, 70, 70));
    houralarmled->setGeometry(QRect(750, 80, 70, 70));

    alarmled->setStates(QSimpleLed::OFF);
    houralarmled->setStates(QSimpleLed::OFF);

    //alarmled->setStates(QSimpleLed::BLINK);

    dateSetter = DateSetter();
    timeSetter = TimeSetter();
}

Widget::~Widget()
{
    delete  ui;
}

void Widget::updatetime(){
    dateTime = dateTime.addSecs(1);
    if(en_alarm && dateTime.time().minute() == 0 && dateTime.time().second() == 0){
        halarmtimer.start(60000);
        houralarmled->setStates(QSimpleLed::BLINK);
        connect(&halarmtimer, &QTimer::timeout, this, &Widget::off_halarmled);
    }
    if(en_alarm && dateTime.time().hour() == alarmTime.hour() && dateTime.time().minute() == alarmTime.minute() && dateTime.time().second() == 0){
        alarmtimer.start(60000);
        alarmled->setStates(QSimpleLed::BLINK);
        connect(&alarmtimer, &QTimer::timeout, this, &Widget::off_alarmled);
    }
    showLCD();
}

void Widget::updatewatch(){
    watchTime = watchTime.addSecs(1);
    showLCD();
}

void Widget::off_alarmled(){
    alarmtimer.stop();
    alarmled->setStates(QSimpleLed::OFF);
    disconnect(&alarmtimer, &QTimer::timeout, this, &Widget::off_alarmled);
}

void Widget::off_halarmled(){
    halarmtimer.stop();
    houralarmled->setStates(QSimpleLed::OFF);
    disconnect(&halarmtimer, &QTimer::timeout, this, &Widget::off_halarmled);
}

void Widget::showLCD(){
    if(en){
        QString text;
        if(!set){
            if(showflag == 0){
                text = dateTime.toString("hh:mm:ss");
            }
            else if(showflag == 1){
                text = dateTime.toString("yyyy:MM:dd");
            }
            else if(showflag == 2){
                text = alarmTime.toString("hh:mm:ss");
            }
            else if(showflag >= 3){
                text = watchTime.toString("hh:mm:ss");
            }
        }
        else if(showflag >= 3)
            text = watchTime.toString("hh:mm:ss");
        else if(showflag == SHOW_TIME)
        {
            text = timeSetter.toString();
        }
        else if(showflag == SHOW_DATE)
        {
            text = dateSetter.toString();
        }
        else{

//            int y1 = setnum.one / 1000;
//            int y2 = setnum.one / 100;
//            int h1 = setnum.one / 10;
//            int h2 = setnum.one % 10;
//            int m1 = setnum.two / 10;
//            int m2 = setnum.two % 10;
//            int s1 = setnum.three / 10;
//            int s2 = setnum.three % 10;

//            switch (pos) {
//            case 0:
//                text = QString::number(y1)+"."+QString::number(y2)+QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2);
//                break;
//            case 1:
//                text = QString::number(y1)+QString::number(y2)+"."+QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2);
//                break;
//            case 2:
//                if(showflag == 1)
//                    text = QString::number(y1)+QString::number(y2)+QString::number(h1)+"."+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2);
//                else
//                    text = QString::number(h1)+"."+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2);
//                break;
//            case 3:
//                if(showflag == 1)
//                    text = QString::number(y1)+QString::number(y2)+QString::number(h1)+QString::number(h2)+"."+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2);
//                else
//                    text = QString::number(h1)+QString::number(h2)+"."+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2);
//                break;
//            case 4:
//                if(showflag == 1)
//                    text = QString::number(y1)+QString::number(y2)+QString::number(h1)+QString::number(h2)+QString::number(m1)+"."+QString::number(m2)+QString::number(s1)+QString::number(s2);
//                else
//                    text = QString::number(h1)+QString::number(h2)+QString::number(m1)+"."+QString::number(m2)+QString::number(s1)+QString::number(s2);
//                break;
//            case 5:
//                if(showflag == 1)
//                    text = QString::number(y1)+QString::number(y2)+QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+"."+QString::number(s1)+QString::number(s2);
//                else
//                    text = QString::number(h1)+QString::number(h2)+QString::number(m1)+QString::number(m2)+"."+QString::number(s1)+QString::number(s2);
//                break;
//            case 6:
//                if(showflag == 1)
//                    text = QString::number(y1)+QString::number(y2)+QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+"."+QString::number(s2);
//                else
//                    text = QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+"."+QString::number(s2);
//                break;
//            case 7:
//                if(showflag == 1)
//                    text = QString::number(y1)+QString::number(y2)+QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2)+".";
//                else
//                    text = QString::number(h1)+QString::number(h2)+QString::number(m1) +QString::number(m2)+QString::number(s1)+QString::number(s2)+".";
//                break;
//            }
        }
        lcdNumber->display(text);
    }
}

void Widget::on_enable_clicked()
{
    this->en = !this->en;
    if(!this->en){
        lcdNumber->setHidden(true);
        disconnect(&timer, &QTimer::timeout, this, &Widget::updatetime);
    }
    else{
        dateTime = QDateTime::currentDateTime();
        timer.start(1000);
        connect(&timer, &QTimer::timeout, this, &Widget::updatetime);
        this->lcdNumber->setHidden(false);
        this->showLCD();
    }
}


void Widget::on_setter_clicked()
{
    set = !set;
    if(showflag == 3 || showflag == 4){
        return;
    }
    if(showflag <= 2 && !set){
        if(this->showflag == SHOW_TIME){
            QTime time = timeSetter.finishSetting();
            dateTime.setTime(time);
        }
        else if(this->showflag == SHOW_DATE){
            QDate date = dateSetter.finishSetting();
            dateTime.setDate(date);
        }
        else if (this->showflag == SHOW_ALARM){
            QTime time;
            if(time.setHMS(setnum.one, setnum.two, setnum.three))
                alarmTime.setHMS(setnum.one, setnum.two, 0);
        }
    }
    else if(set){
        if(showflag == SHOW_DATE)
        {
            pos = 0;
            QDate date = this->dateTime.date();
            dateSetter.setDate(date);
        }
        else
        {
            pos = 2;
            if(showflag == SHOW_TIME)
            {
                QTime time = this->dateTime.time();
                timeSetter.setTime(time);
            }
        }
    }
    showLCD();
}


void Widget::on_reset_clicked()
{
    off_alarmled();
    off_halarmled();

    QDate date;
    date.setDate(2000, 1, 1);
    dateTime.setDate(date);

    QTime time;
    time.setHMS(0,0,0);
    dateTime.setTime(time);

    alarmTime.setHMS(0,0,0);

    if(en_alarm && dateTime.time().minute() == 0 && dateTime.time().second() == 0){
        halarmtimer.start(60000);
        houralarmled->setStates(QSimpleLed::BLINK);
        connect(&halarmtimer, &QTimer::timeout, this, &Widget::off_halarmled);
    }
    if(en_alarm && dateTime.time().hour() == alarmTime.hour() && dateTime.time().minute() == alarmTime.minute() && dateTime.time().second() == 0){
        alarmtimer.start(60000);
        alarmled->setStates(QSimpleLed::BLINK);
        connect(&alarmtimer, &QTimer::timeout, this, &Widget::off_alarmled);
    }

    showLCD();
}


void Widget::on_switch_2_clicked()
{
    if(showflag == 3)
        return;
    if(showflag >= 2){
        showflag = 0;
    }
    else
        showflag++;
    showLCD();
}


void Widget::on_stopwatch_clicked()
{
    en_watch = !en_watch;
    if(en_watch){
        showflag = 3;
        watchTime.setHMS(0,0,0);
        watchtimer.start(1000);
        connect(&watchtimer, &QTimer::timeout, this, &Widget::updatewatch);
    }
    else{
        disconnect(&watchtimer, &QTimer::timeout, this, &Widget::updatewatch);
        watchtimer.stop();
        showflag = 4;
        showLCD();
    }

}


void Widget::on_apply_clicked(){
    if(set){
        switch(showflag){
        case SHOW_TIME:
            if(pos == 7)
                pos = 2;
            else
                pos++;
            timeSetter.apply();
            break;
        case SHOW_DATE:
            if(pos == 7)
                pos = 0;
            else
                pos++;
            dateSetter.apply();
            break;
        case SHOW_ALARM:
            if(pos == 5)
                pos = 2;
            else
                pos++;
            break;
        default:
            break;
        }
    }
    showLCD();
}


void Widget::on_inc_clicked()
{
    if(set && showflag <= 2){
        if(showflag == SHOW_DATE){
            dateSetter.inc();
        }
        else if (showflag == SHOW_TIME){
            timeSetter.inc();

        }
        else if(showflag == 2){

        }
    }
    showLCD();
}


void Widget::on_analarm_clicked()
{
    en_alarm = !en_alarm;
    if(!en_alarm){
        off_alarmled();
        off_halarmled();
    }
}

