
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>  //  所有控件的基类，就是一个窗口
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <QDateTime>
#include <QTimer>
#include <QGroupBox>
#include <QtWidgets/QLCDNumber>
#include "QSimpleLed.h"
#include "datesetter.h"
#include "timesetter.h"

#define SHOW_TIME 0
#define SHOW_DATE 1
#define SHOW_ALARM 2
#define SHOW_STOPWATCH_ON 3
#define SHOW_STOPWATCH_OFF 4

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

private:
    QLCDNumber *lcdNumber;

    bool en;
    bool set;
    bool en_alarm;
    bool en_watch;

    int showflag;
    int pos;

    QSimpleLed *alarmled = nullptr;
    QSimpleLed *houralarmled = nullptr;

    QTimer alarmtimer;
    QTimer halarmtimer;

    QDateTime dateTime;
    QTime alarmTime;
    QTime watchTime;

    QTimer timer;
    QTimer watchtimer;

    DateSetter dateSetter;
    TimeSetter timeSetter;

    struct SetNum{
        int one;
        int two;
        int three;
    } setnum;

public:
    QPushButton *button;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void showLCD();

private slots:
    void updatetime();
    void updatewatch();
    void on_enable_clicked();
    void on_setter_clicked();
    void on_reset_clicked();
    void on_switch_2_clicked();
    void on_stopwatch_clicked();
    void on_apply_clicked();
    void on_inc_clicked();
    void off_alarmled();
    void off_halarmled();

    void on_analarm_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
