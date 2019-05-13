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

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);


    setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    //world.setScene("");//初始化游戏世界

    //设计计时器，以FPS帧数刷新画面
    this->refresher = new QTimer;
    refresher->start(1000/FPS);
    QObject::connect(refresher, SIGNAL(timeout()), this, SLOT(update()));


/* 备用的生成敌人的计时器，两种方法在绘制中都会出现重影现象
    //设计计时器，添加新的敌人
    QTimer *timer = new QTimer(this);
    int f;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    f=qrand()%3;//设置生成的敌人频率
    timer->start(5000/f);
    QObject::connect(timer, SIGNAL(timeout()), &world, SLOT(enemy_generator()));
*/
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
}
void MainWindow::mouseMoveEvent(QMouseEvent* e){
    world.processor_mouseMoveEvent(e);
}



