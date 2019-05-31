#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include "config.h"
#include "scene.h"
#include <QDebug>
#include <QTime>

#include <QMessageBox>

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
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);

    this->addMoney = new QTimer;
    addMoney->start(10000);
    QObject::connect(addMoney, SIGNAL(timeout()),this, SLOT(add_money()));

    this->setscene=new QTimer;
    setscene->start(20000);//每3分钟进入下一关
    QObject::connect(setscene, SIGNAL(timeout()),this, SLOT(set_Scene()));

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
//    world.life_show(e);
}
void MainWindow::mouseMoveEvent(QMouseEvent* e){
    //qDebug()<<"used:"<<count++<<endl;
    world.processor_mouseMoveEvent(e);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    world.processor_mouseReleseEvent(e);
}

void MainWindow::add_money(){
    world.money_add(PLAYER_1_MONEY_ADD);
}

void MainWindow::set_Scene(){
    refresher->stop();
    if(world.mapname.compare(":/pictures/background/backGround1.png") == 0)
    {
        world.setScene(":/pictures/background/backGround2.png");
        world.frequency=3;
    }
    else if(world.mapname.compare(":/pictures/background/backGround2.png") == 0)
    {
        world.setScene(":/pictures/background/backGround3.png");
        world.frequency=2;
    }
    else if(world.mapname.compare(":/pictures/background/backGround3.png") == 0)
    {
        world.setScene(":/pictures/background/backGround4.png");
        world.frequency=1;
    }
    else if(world.mapname.compare(":/pictures/background/backGround4.png") == 0)
    {
        QMessageBox message1(QMessageBox::NoIcon, "Congratulations!", "Congratulations! You win!");
        message1.setIconPixmap(QPixmap(":/pictures/enemy/enemy10.png"));
        message1.exec();
    }
    refresher->start(1000/FPS);
}

void MainWindow::on_pushButton_clicked()
{
    refresher->stop();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    refresher->start();
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
}
