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
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    w.show();
    w.show_lose();
    return a.exec();
}
