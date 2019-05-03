#include "scene.h"
#include <QPixmap>
#include "config.h"
Scene::Scene()
{
    Tower* displayedTower = new Tower("attacker", false);
    displayedTower->setGameObject(ATTACKER_WIDTH/2, MAINWINDOW_HEIGHT-ATTACKER_HEIGHT/2);
    displayMenuOfTowers.push_back(displayedTower);
}

Scene::~Scene(){
}

/*void Scene::setScene(QString map_name){

}*/

void Scene::show(QPainter* p){
    //画背景
    QPixmap backgroud;
    backgroud.load(":/pictures/backGround2.png");
    p->drawPixmap(0,MAINWINDOW_HEIGHT-BACK_GROUND_HEIGHT,BACK_GROUND_WIDTH,BACK_GROUND_HEIGHT,backgroud);

    int i;
    for(i = 0; i < towers.size(); i++){
        towers[i]->show(p);
    }
    for(i = 0; i < displayMenuOfTowers.size(); i++){
        displayMenuOfTowers[i]->show(p);
    }
    for(i = 0; i < dragedTower.size(); i++){
        dragedTower[i]->show(p);
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
                    dragedTower.clear();
                }
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
        int i;
        for(i = 0; i <dragedTower.size(); i++){
            delete dragedTower[i];
        }
        dragedTower.clear();
    }
}
void Scene::processor_mouseMoveEvent(QMouseEvent *e){
    int i;
    for(i = 0; i < dragedTower.size(); i++){
        dragedTower[i]->setGameObject(e->x(), e->y());
    }
}



