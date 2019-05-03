#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include "config.h"
#include <QDebug>

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    world()//world被默认初始化
{
    ui->setupUi(this);

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);


    setWindowFlags(false);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    //world.setScene("");//初始化游戏世界

    //设计计时器，以20帧刷新画面
    this->refresher = new QTimer;
    refresher->start(1000/FPS);
    QObject::connect(refresher, SIGNAL(timeout()), this, SLOT(refresher_receiver()));



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

void slots MainWindow::refresher_receiver(){
    this->repaint();
}

void MainWindow::keyPressEvent(QKeyEvent* e){

}
void MainWindow::mousePressEvent(QMouseEvent* e){
    world.processor_mousePressEvent(e);
}
void MainWindow::mouseMoveEvent(QMouseEvent* e){
    world.processor_mouseMoveEvent(e);
}



