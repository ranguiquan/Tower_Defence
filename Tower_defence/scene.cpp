#include "scene.h"
#include <QPixmap>
#include "config.h"
#include <QDebug>
#include <math.h>
#include "tool.h"
#include <QtGlobal>
#include <QTime>
#include <QTimer>

Scene::Scene()
{
    Tower* displayedTower = new Tower("attacker", false);
    displayedTower->setGameObject(ATTACKER_WIDTH/2, MAINWINDOW_HEIGHT-ATTACKER_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

    background = new QPixmap;
    background->load(":/pictures/backGround2.png");
    Player *player = new Player;

}

Scene::~Scene(){
}

/*void Scene::setScene(QString map_name){

}*/

void Scene::show(QPainter* p){
    //画背景
    player->show(p);
    time = QTime::currentTime();
    p->drawPixmap(0,MAINWINDOW_HEIGHT-BACK_GROUND_HEIGHT,BACK_GROUND_WIDTH,BACK_GROUND_HEIGHT,*background);
    int i;
    for(i = 0; i < towers.size(); i++){
        towers[i]->handleCoolDown();
    }

    processor_hatredControll();
    processor_Tower_rotate();
    processor_Move();
    creator_bullets();
    processor_damageConfirm();
    if((int(time.second())%5)==0)
         enemy_generator();
    object_delete();


    for(i = 0; i < towers.size(); i++){
        towers[i]->handleCoolDown();
    }

    for(i = 0; i < towers.size(); i++){
        towers[i]->show(p);
    }
    for(i = 0; i < displayMenuOfTowers.size(); i++){
        displayMenuOfTowers[i]->show(p);
    }
    for(i = 0; i < dragedTower.size(); i++){
        dragedTower[i]->show(p);
    }
    for(i = 0; i < enemies.size(); i++){
        if(enemies[i]->getLife() > 0){
            enemies[i]->show(p);
        }
    }
    for(i = 0; i < bullets.size(); i++){
        bullets[i]->show(p);
    }
}
void Scene::processor_mousePressEvent(QMouseEvent *e){
    int i;
    if(e->button() == Qt::LeftButton){
        for(i = 0; i < displayMenuOfTowers.size(); i++){
            if(displayMenuOfTowers[i]->isMouseEventInIt(e)){
                int j;
                for(j = 0; j <dragedTower.size(); j++){
                    delete dragedTower[j];
                }
                dragedTower.clear();
                Tower* tmp = new Tower("attacker", false);
                tmp->setGameObject(e->x(), e->y());
                tmp->setChosen(true);
                this->dragedTower.push_back(tmp);
                return;
            }
        }
        int j = 0;
        for(j = 0; j < dragedTower.size(); j++){
            dragedTower[j]->setActivated(true);
            towers.push_back(dragedTower[j]);

        }
        dragedTower.clear();
    }else if(e->button() == Qt::RightButton){
        qDebug()<<"dragedTower.size():"<<dragedTower.size()<<endl;
        qDebug()<<"towers.size():"<<towers.size()<<endl;


        for(i = 0; i <dragedTower.size(); i++){
            Tower* tmp = dragedTower[i];
            dragedTower.remove(i,1);
            i--;
            delete tmp;
            qDebug()<<"dragedTower.size():"<<dragedTower.size()<<endl;
        }
        qDebug()<<"!!!"<<endl;


    }
}
void Scene::processor_mouseMoveEvent(QMouseEvent *e){
    int i;
    for(i = 0; i < dragedTower.size(); i++){
        dragedTower[i]->setGameObject(e->x(), e->y());
    }
}
void Scene::processor_keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_0){
        qDebug()<<"delete\n";
        delete enemies[0];
        qDebug()<<"after delete\n";
    }
}


double Scene::distance(MyPoint a, MyPoint b){
    double x = pow(a.x()-b.x(),2);
    double y = pow(a.y()-b.y(),2);
    double ans = pow(x+y,0.5);
    return ans;
}


void Scene::processor_hatredControll(){
    int i,j;
    for(i = 0; i < towers.size(); i++){
        for(j = 0; j < enemies.size(); j++){
            double dis = distance(towers[i]->getPosition(), enemies[j]->getPosition());
            int index = towers[i]->hatred.indexOf(enemies[j]);
            if(dis<= towers[i]->get_discovery_range()
                    && index==-1 && enemies[j]->getLife() > 0){
                towers[i]->hatred.push_back(enemies[j]);
                qDebug()<<"add to hatred\n";
            }
            if(index != -1 &&(dis > towers[i]->get_discovery_range() || enemies[j]->getLife() <= 0)){
                towers[i]->hatred.erase(towers[i]->hatred.begin()+index);
            }
        }
    }
}
void Scene::creator_bullets()
{
    int i;
    for(i = 0; i < towers.size(); i++){
        //qDebug()<<"hatred.isEmpty"<<towers[i]->hatred.isEmpty()<<endl;
        if(!towers[i]->hatred.isEmpty() && towers[i]->isFireReady()){
            Enemy* target = towers[i]->hatred[0];
            towers[i]->setFireReady(false);
            Bullet* b = new Bullet(towers[i], target);
            bullets.push_back(b);
            //qDebug()<<"bullet created\n";
        }
    }
}

void Scene::processor_Move(){
    int i;
    for(i = 0; i < enemies.size(); i++){
        double xPre = enemies[i]->getPosition().x();
        double yPre = enemies[i]->getPosition().y();
        double x = xPre + enemies[i]->get_velocity()*enemies[i]->get_direction_x()/FPS;
        double y = yPre + enemies[i]->get_velocity()*enemies[i]->get_direction_y()/FPS;
        enemies[i]->setGameObject(x, y);
    }
    for(i = 0; i < bullets.size(); i++){
        double xPre = bullets[i]->getPosition().x();
        double yPre = bullets[i]->getPosition().y();
        double x = xPre + bullets[i]->get_velocity()*bullets[i]->get_direction_x()/FPS;
        double y = yPre + bullets[i]->get_velocity()*bullets[i]->get_direction_y()/FPS;
        bullets[i]->setGameObject(x, y);
    }

}

void Scene::processor_damageConfirm(){
    int i, j;
    for(i = 0; i < enemies.size(); i++){
        for(j = 0; j < bullets.size(); j++){
            if(enemies[i]->isMyPointInIt(bullets[j]->getPosition())){
                enemies[i]->setLife(enemies[i]->getLife() - bullets[j]->getDamage());
                delete bullets[j];

                bullets.erase(bullets.begin()+j);
                j--;
            }
        }

    }
}
void Scene::processor_Tower_rotate(){
    int i;
    for(i = 0; i < towers.size(); i++){
        if(!towers[i]->hatred.isEmpty()){
            MyPoint vec_aim;
            MyPoint aim(towers[i]->hatred[0]->getPosition());
            MyPoint pole(towers[i]->getPosition());
            vec_aim.setX(aim.x()-pole.x());
            vec_aim.setY(aim.y()-pole.y());
            double angle_aim = Tool::vector_to_angle(vec_aim);
            if(abs(angle_aim - towers[i]->getAngle()) > towers[i]->get_velocity_rotaion()/FPS){
                //缓慢旋转中
                towers[i]->setAngle(towers[i]->getAngle()
                                    + Tool::sign(angle_aim - towers[i]->getAngle())//这是一个符号函数，算方向的
                                    * towers[i]->get_velocity_rotaion()/FPS);
                towers[i]->setFireReady(false);
            }else{
                //能转到，爽
                towers[i]->setAngle(angle_aim);
            }
        }
    }
}


void Scene::enemy_generator()
{
    int a,b;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    a=qrand()%7;//设置生成的敌人种类，种类数为7

    b=qrand()%3;//设置一次生成的敌人个数，敌人个数不超过3
    Enemy *e[b];
    for(int i=0;i<b;i++)
    {
        e[i] = new Enemy();
        enemies.push_back(e[i]);
    }
}//未完成，随机生成种类不同敌人部分待补充

void Scene::object_delete()
{
    for(QVector<Enemy*>::iterator iter=enemies.begin(); iter!=enemies.end(); )
    {
        if(((*iter)->getLife())<=0)
        {
            delete *iter;
            iter =  enemies.erase(iter);
        }
        if(((*iter)->getPosition_x())>=(MAINWINDOW_WIDTH-ENEMY_1_WIDTH/2))
        {
            player->setLife(player->getLife()-1);
            delete *iter;
            iter =  enemies.erase(iter);
        }
        else
        {
            iter++;
        }
    }
   if(player->getLife()==0)
   {
       //游戏结束，失败
   }
}




