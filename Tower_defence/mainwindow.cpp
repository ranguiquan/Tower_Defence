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

    ui->frame->hide();

    //world.setScene("");//初始化游戏世界

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
    addMoney->stop();
    setscene->stop();
    if(world.mapname.compare(":/pictures/background/backGround1.png") == 0)
    {
        QMessageBox message(QMessageBox::NoIcon, "Ready for Next Round", "New round! Are you ready?");
        message.setIconPixmap(QPixmap(":/pictures/enemy/enemy1.png"));
        message.exec();
        world.setScene(":/pictures/background/backGround2.png");
        world.frequency=3;
        refresher->start(1000/FPS);
        addMoney->start(10000);
        setscene->start(ROUND_TIME);//进入下一关
    }
    else if(world.mapname.compare(":/pictures/background/backGround2.png") == 0)
    {
        QMessageBox message(QMessageBox::NoIcon, "Ready for Next Round", "New round! Are you ready?");
        message.setIconPixmap(QPixmap(":/pictures/enemy/enemy2.png"));
        message.exec();
        world.setScene(":/pictures/background/backGround3.png");
        world.frequency=2;
        refresher->start(1000/FPS);
        addMoney->start(10000);
        setscene->start(ROUND_TIME);//每3分钟进入下一关
    }
    else if(world.mapname.compare(":/pictures/background/backGround3.png") == 0)
    {
        QMessageBox message(QMessageBox::NoIcon, "Ready for Next Round", "New round! Are you ready?");
        message.setIconPixmap(QPixmap(":/pictures/enemy/enemy4.png"));
        message.exec();
        world.setScene(":/pictures/background/backGround4.png");
        world.frequency=1;
        refresher->start(1000/FPS);
        addMoney->start(10000);
        setscene->start(ROUND_TIME);//每3分钟进入下一关
    }
    else if(world.mapname.compare(":/pictures/background/backGround4.png") == 0)
    {
        int nRet2=QMessageBox::information(NULL, "Congratulations!", "Congratulations! You win!", QMessageBox::Yes, QMessageBox::Yes);
        if (QMessageBox::Yes == nRet2) {
            world.clearScene();
            ui->frame->hide();
            ui->frame_2->show();
        }
    }
}

void MainWindow::on_pushButton_clicked()//stop
{
    refresher->stop();
    addMoney->stop();
    setscene->stop();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()//start
{
    refresher->start();
    addMoney->start();
    setscene->start();
/*本来想加一个记录当前计时器描述，避免重新开始后清零的，但是有问题
    int a,b;
    a=abs(addMoney->remainingTime());
    b=abs(setscene->remainingTime());
    addMoney1->setSingleShot(1);
    addMoney1->start(a);
    if(addMoney1->remainingTime()==0)
        addMoney->start(10000);
//    QObject::connect(addMoney, SIGNAL(timeout()),this, SLOT(add_money()));
    //为防止暂停后计时器清零，记录当前时间

    setscene1->singleShot(b,setscene,SLOT(start(ROUND_TIME)));
//    QObject::connect(setscene, SIGNAL(timeout()),this, SLOT(set_Scene()));
*/
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()//start new game
{
    if(world.savedscene==1)
        world.clearScene();//开始新游戏前判断是否有旧游戏，如果有删档
    ui->frame_2->hide();
    ui->frame->show();
    world.setScene(":/pictures/background/backGround1.png");
    //设计计时器，以FPS帧数刷新画面
    world.savedscene=1;
    world.lose=0;
    world.frequency=4;
    world.player->setLife(100);
    world.player->setMoney(100);//因为没办法在新游戏开始时建立新的player，只能在这里将player复原
    this->refresher = new QTimer;
    refresher->start(1000/FPS);
    QObject::connect(refresher, SIGNAL(timeout()), this, SLOT(update()));

    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
    QObject::connect(refresher, SIGNAL(timeout()), this, SLOT(show_lose()));

    this->addMoney = new QTimer;
    addMoney->start(10000);
    QObject::connect(addMoney, SIGNAL(timeout()),this, SLOT(add_money()));

    this->setscene=new QTimer;
    setscene->start(ROUND_TIME);//每3分钟进入下一关
    QObject::connect(setscene, SIGNAL(timeout()),this, SLOT(set_Scene()));
}

void MainWindow::on_pushButton_3_clicked()//点击后退回主界面，可以在这里加存档功能quit
{
    refresher->stop();
    addMoney->stop();
    setscene->stop();
    int nRet = QMessageBox::question(NULL, "Quit?", "Are you sure to quit?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    // 选择是，这里可以加对话框问是否存档
    if (QMessageBox::Yes == nRet) {
        int nRet1=QMessageBox::question(NULL, "Save?", "Save the file?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (QMessageBox::No == nRet1) {
            world.clearScene();
            ui->frame->hide();
            ui->frame_2->show();
            ui->pushButton_5->setEnabled(false);
        }
        if (QMessageBox::Yes == nRet1) {
            world.saveScene();
            ui->frame->hide();
            ui->frame_2->show();
            ui->pushButton_5->setEnabled(true);
        }
    }

    // 选择否
    if (QMessageBox::No == nRet) {
        refresher->start(1000/FPS);
        addMoney->start(10000);
        setscene->start(ROUND_TIME);
    }
}

void MainWindow::show_lose()
{
    if(world.lose==1)
    {
        refresher->stop();
        addMoney->stop();
        setscene->stop();
        int a=QMessageBox::warning(NULL, "warning", "YOU LOSE!", QMessageBox::Yes, QMessageBox::Yes);
        if (QMessageBox::Yes == a) {
            world.clearScene();
            ui->frame->hide();
            ui->frame_2->show();
        }
    }
}

void MainWindow::on_pushButton_6_clicked()//exit
{
    MainWindow::close();
}

void MainWindow::on_pushButton_5_clicked()//continue last game
{
    world.returntoScene();
    ui->frame_2->hide();
    ui->frame->show();
    refresher->start(1000/FPS);
    addMoney->start(10000);
    setscene->start(ROUND_TIME);
}
