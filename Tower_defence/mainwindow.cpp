#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include "config.h"
#include "scene.h"
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    world()//world被默认初始化
{
    ui->setupUi(this);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);


    setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    //world.setScene("");//初始化游戏世界

    //设计计时器，以FPS帧数刷新画面
    this->refresher = new QTimer;
    refresher->start(1000/FPS);
    QObject::connect(refresher, SIGNAL(timeout()), this, SLOT(update()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent* e){
    QPainter *p = new QPainter();
    p->begin(this);
    this->world.show(p);
    p->end();
    delete p;
}


void MainWindow::keyPressEvent(QKeyEvent* e){
    world.processor_keyPressEvent(e);
}
void MainWindow::mousePressEvent(QMouseEvent* e){
    world.processor_mousePressEvent(e);
    world.life_show(e);
}
void MainWindow::mouseMoveEvent(QMouseEvent* e){
    world.processor_mouseMoveEvent(e);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    world.processor_mouseReleseEvent(e);
}



