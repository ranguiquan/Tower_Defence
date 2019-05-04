#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include <QTime>

int main(int argc, char *argv[])
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
