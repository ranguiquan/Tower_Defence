#include "scene.h"
#include <QPixmap>
#include "config.h"
#include <QDebug>
#include <math.h>
Scene::Scene()
{
    Tower* displayedTower = new Tower("attacker", false);
    displayedTower->setGameObject(ATTACKER_WIDTH/2, MAINWINDOW_HEIGHT-ATTACKER_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);

    background = new QPixmap;
    background->load(":/pictures/backGround2.png");

    Enemy* e = new Enemy();
    this->enemies.push_back(e);

}

Scene::~Scene(){
}

/*void Scene::setScene(QString map_name){

}*/

void Scene::show(QPainter* p){
    //画背景

    p->drawPixmap(0,MAINWINDOW_HEIGHT-BACK_GROUND_HEIGHT,BACK_GROUND_WIDTH,BACK_GROUND_HEIGHT,*background);
    int i;
    for(i = 0; i < towers.size(); i++){
        towers[i]->handleCoolDown();
    }
    processor_hatredControll();
    creator_bullets();
    processor_Move();



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
        enemies[i]->show(p);
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
            //delete tmp;
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


double Scene::distance(QPoint a, QPoint b){
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
                    && index==-1){
                towers[i]->hatred.push_back(enemies[j]);
                qDebug()<<"add to hatred\n";
            }
            if(dis > towers[i]->get_discovery_range()
                    && index != -1){
                towers[i]->hatred.remove(index, 1);
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
        int xPre = enemies[i]->getPosition().x();
        int yPre = enemies[i]->getPosition().y();
        int x = xPre + enemies[i]->get_velocity()*enemies[i]->get_direction_x()/FPS;
        int y = yPre + enemies[i]->get_velocity()*enemies[i]->get_direction_y()/FPS;
        enemies[i]->setGameObject(x, y);
    }
    for(i = 0; i < bullets.size(); i++){
        int xPre = bullets[i]->getPosition().x();
        int yPre = bullets[i]->getPosition().y();
        int x = xPre + bullets[i]->get_velocity()*bullets[i]->get_direction_x()/FPS;
        int y = yPre + bullets[i]->get_velocity()*bullets[i]->get_direction_y()/FPS;
        bullets[i]->setGameObject(x, y);
    }

}
