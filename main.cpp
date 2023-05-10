
#include "widget.h"

#include <QApplication>//QT的框架头文件


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//Qt框架初始化，必须存在一个

    Widget w;//定义一个窗口对象
    w.show();//将创建的窗口控件显示
    return a.exec();    //a.exec()作用程序进入消息循环
}
