#include "mainwindow.h"
#include "weather.h"
#include <QApplication>
#include <QTabWidget>
#include <QScrollArea>
#include <QDesktopWidget>//desktop使用
#include <QLabel>

MainWindow *radio = NULL;
Weather *weather = NULL;
QTabWidget *tabwidget;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    tabwidget = new QTabWidget;


    radio = new MainWindow();


    //radio->setGeometry(0, 0, 1050, 2200);
    radio->setWindowTitle("Edit Radio");

    QScrollArea *scrollArea_r = new QScrollArea;
    scrollArea_r->setWidget(radio);
    //页的方式显示
    tabwidget->addTab(scrollArea_r,"Radio");
    //tabwidget->resize(1050,600);
    //tabwidget->move((QApplication::desktop()->width() - radio->width()*6/5),0);
    //tabwidget->show();

/////////////////////////
    weather = new Weather();
    weather->setWindowTitle("Edit Weather");

    QScrollArea *scrollArea_w = new QScrollArea;
    scrollArea_w->setWidget(weather);
    tabwidget->addTab(scrollArea_w,"Weather");


//设置显示位置
    tabwidget->resize(1050,650);
    tabwidget->move((QApplication::desktop()->width() - radio->width())/2,10);
    tabwidget->show();

    qDebug() << QApplication::desktop()->width();
    qDebug() << radio->width();



    return a.exec();
}
