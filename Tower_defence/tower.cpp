#include "tower.h"
#include <QPixmap>
#include <config.h>
#include <QtDebug>

Tower::Tower(string name, bool isInstanlized)
//只有通过鼠标事件才能生成实例化的防御塔（尚不确定的想法）
{
    if(!isInstanlized){
        if(name.compare("attacker") == 0){
            this->damage = ATTACKER_DAMAGE;
            icon->load(":/pictures/tower/tower1.png");
            width = ATTACKER_WIDTH;
            height = ATTACKER_HEIGHT;
            discoveryRange = ATTACKER_DISCOVERY;

            isActivated = false;
            isChosen = false;
            fireReady = false;
            fireInterval = ATTACKER_FIRE_INTERVAL;
            coolDown = ATTACKER_FIRE_INTERVAL;
            velocity_rotation = ATTACKER_VELOCITY_ROTATION;
            angle = 180;

        }
        else if(name.compare("attacker1") == 0)
        {
            this->damage = ATTACKER1_DAMAGE;
            icon->load(":/pictures/tower/tower2.png");
            width = ATTACKER1_WIDTH;
            height = ATTACKER1_HEIGHT;
            discoveryRange = ATTACKER1_DISCOVERY;

            isActivated = false;
            isChosen = false;
            fireReady = false;
            fireInterval = ATTACKER1_FIRE_INTERVAL;
            coolDown = ATTACKER1_FIRE_INTERVAL;
            velocity_rotation = ATTACKER1_VELOCITY_ROTATION;
            angle = 180;
        }
        else if(name.compare("attacker2") == 0)
        {
            this->damage = ATTACKER1_DAMAGE;
            icon->load(":/pictures/tower/tower3.png");
            width = ATTACKER2_WIDTH;
            height = ATTACKER2_HEIGHT;
            discoveryRange = ATTACKER2_DISCOVERY;

            isActivated = false;
            isChosen = false;
            fireReady = false;
            fireInterval = ATTACKER2_FIRE_INTERVAL;
            coolDown = ATTACKER2_FIRE_INTERVAL;
            velocity_rotation = ATTACKER2_VELOCITY_ROTATION;
            angle = 180;
        }
        else if(name.compare("attacker3") == 0)
        {
            this->damage = ATTACKER3_DAMAGE;
            icon->load(":/pictures/tower/tower4.png");
            width = ATTACKER3_WIDTH;
            height = ATTACKER3_HEIGHT;
            discoveryRange = ATTACKER3_DISCOVERY;

            isActivated = false;
            isChosen = false;
            fireReady = false;
            fireInterval = ATTACKER3_FIRE_INTERVAL;
            coolDown = ATTACKER3_FIRE_INTERVAL;
            velocity_rotation = ATTACKER3_VELOCITY_ROTATION;
            angle = 180;
        }
    }else{

    }
}
Tower::~Tower(){
    qDebug()<<"delete Tower\n";
    delete icon;
    qDebug()<<"Tower deleted\n";
}
void Tower::handleCoolDown(){
    coolDown = coolDown- 1.0/FPS;
    if(coolDown < 0 ){
        fireReady = true;
        coolDown = fireInterval;
    }
    //qDebug()<<"cooldown:"<<coolDown<<endl;
    //qDebug()<<"fireReady"<<fireReady<<endl;
}
void Tower::show(QPainter *p){
    p->translate(this->position.x(), this->position.y());
    p->rotate(angle);
    p->drawPixmap(-width/2,-height/2,width, height, *icon);
    p->rotate(-angle);
    p->translate(-this->position.x(), -this->position.y());

}
