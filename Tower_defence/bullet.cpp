#include "bullet.h"
#include <QPixmap>
#include <config.h>
#include "scene.h"
#include <QDebug>
#include "mypoint.h"
#include "tool.h"

Bullet::Bullet(Tower* parent, Enemy* target)
{
    this->parent = parent;
    if((parent->getType()).compare("attacker") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet1.png");
        this->width = BULLET_WIDTH;
        this->height = BULLET_WIDTH;
        this->velocity = BULLET_VELOCITY;
    }
    else if((parent->getType()).compare("attacker1") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet1.png");
        this->width = BULLET1_WIDTH;
        this->height = BULLET1_WIDTH;
        this->velocity = BULLET1_VELOCITY;
    }
    if((parent->getType()).compare("attacker2") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet2.png");
        this->width = BULLET2_WIDTH;
        this->height = BULLET2_WIDTH;
        this->velocity = BULLET2_VELOCITY;
    }
    if((parent->getType()).compare("attacker3") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet2.png");
        this->width = BULLET3_WIDTH;
        this->height = BULLET3_WIDTH;
        this->velocity = BULLET3_VELOCITY;
    }
    if((parent->getType()).compare("attacker4") == 0){
        this->slower=BULLET4_SLOWER;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet3.png");
        this->width = BULLET4_WIDTH;
        this->height = BULLET4_WIDTH;
        this->velocity = BULLET4_VELOCITY;
    }
    float dis = Scene::distance((parent->getPosition()), (target->getPosition()));
    float x = target->getPosition().x()-parent->getPosition().x();
    float y = target->getPosition().y()-parent->getPosition().y();
    direction_x = (x/dis);
    direction_y = (y/dis);
    this->position.setX(parent->getPosition().x() + direction_x * parent->getWidth()/2);
    this->position.setY(parent->getPosition().y() + direction_y * parent->getWidth()/2);
    MyPoint direction(direction_x, direction_y);
    float angle = Tool::vector_to_angle(direction) + int(qrand()%360 - 180)/18;
    direction_x = Tool::angel_to_vector(angle).x();
    direction_y = Tool::angel_to_vector(angle).y();
}
Bullet::Bullet(Tower* parent, MyPoint vec_angle){
    this->parent = parent;

    if((parent->getType()).compare("attacker") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet1.png");
        this->width = BULLET_WIDTH;
        this->height = BULLET_WIDTH;
        this->velocity = BULLET_VELOCITY;
    }
    else if((parent->getType()).compare("attacker1") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet1.png");
        this->width = BULLET1_WIDTH;
        this->height = BULLET1_WIDTH;
        this->velocity = BULLET1_VELOCITY;
    }
    if((parent->getType()).compare("attacker2") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet2.png");
        this->width = BULLET2_WIDTH;
        this->height = BULLET2_WIDTH;
        this->velocity = BULLET2_VELOCITY;
    }
    if((parent->getType()).compare("attacker3") == 0){
        this->slower=0;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet2.png");
        this->width = BULLET3_WIDTH;
        this->height = BULLET3_WIDTH;
        this->velocity = BULLET3_VELOCITY;
    }
    if((parent->getType()).compare("attacker4") == 0){
        this->slower=BULLET4_SLOWER;
        this->damage = parent->getDamage();
        this->icon = new QPixmap;
        icon->load(":/pictures/bullet/bullet3.png");
        this->width = BULLET4_WIDTH;
        this->height = BULLET4_WIDTH;
        this->velocity = BULLET4_VELOCITY;
    }


    this->position.setX(parent->getPosition().x() + vec_angle.x() * parent->getWidth()/2);
    this->position.setY(parent->getPosition().y() + vec_angle.y() * parent->getWidth()/2);


    float angle = Tool::vector_to_angle(vec_angle) + int(qrand()%360 - 180)/18;
    direction_x = Tool::angel_to_vector(angle).x();
    direction_y = Tool::angel_to_vector(angle).y();
}
Bullet::~Bullet(){
    delete icon;
}
