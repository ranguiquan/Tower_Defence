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
    player = new Player;
    secondCounter = 0.0;

}

Scene::~Scene(){
}

/*void Scene::setScene(QString map_name){

}*/

void Scene::show(QPainter* p){
    secondCounter += 1.0/FPS;
    //画背景
    player->show(p);
    p->drawPixmap(0,0/*MAINWINDOW_HEIGHT-BACK_GROUND_HEIGHT*/,BACK_GROUND_WIDTH,BACK_GROUND_HEIGHT,*background);
    int i;
    for(i = 0; i < towers.size(); i++){
        towers[i]->handleCoolDown();
    }

    processor_hatredControll();
    processor_Tower_rotate();
    processor_Move();
    creator_bullets();
    processor_damageConfirm();
    if(((secondCounter - int(secondCounter/5)*5) >= 0.0) && ((secondCounter - int(secondCounter/5)*5) < 1.0/FPS)){

         enemy_generator();
    }
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
    player->show(p);
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
    a=qrand()%7;//设置生成的敌人种类，种类数为7

    b=qrand()%7;//设置一次生成的敌人个数，敌人个数不超过3
    for(int i=0;i<b;i++)
    {
        Enemy* tmp = new Enemy();
        tmp->setGameObject(0,100+i*100);
        enemies.push_back(tmp);
    }
}//未完成，随机生成种类不同敌人部分待补充

void Scene::object_delete()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        if(((enemies[i])->getLife())<=0)
        {
            for(int j = 0; j < towers.size(); j++){
                int index = towers[j]->hatred.indexOf(enemies[i]);
                if(index != -1){
                    towers[j]->hatred.erase(towers[j]->hatred.begin() + index);
                }
            }
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            i--;
            if(i < 0){break;}
        }
        if(((enemies[i])->getPosition_x())>=(MAINWINDOW_WIDTH-ENEMY_1_WIDTH/2))
        {
            for(int j = 0; j < towers.size(); j++){
                int index = towers[j]->hatred.indexOf(enemies[i]);
                if(index != -1){
                    towers[j]->hatred.erase(towers[j]->hatred.begin() + index);
                }
            }
            player->setLife(player->getLife()-1);
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            i--;
            if(i < 0){break;}
        }
    }
   if(player->getLife()==0)
   {
       //游戏结束，失败
   }
}




