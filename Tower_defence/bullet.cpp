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
    this->damage = parent->getDamage();
    this->icon = new QPixmap;
    icon->load(":/pictures/bullet_test.png");
    this->width = BULLET_WIDTH;
    this->height = BULLET_WIDTH;
    this->velocity = BULLET_VELOCITY;
    this->position.setX(parent->getPosition().x());
    this->position.setY(parent->getPosition().y());
    //方向想引入随机数


    double dis = Scene::distance((parent->getPosition()), (target->getPosition()));
    double x = target->getPosition().x()-parent->getPosition().x();
    double y = target->getPosition().y()-parent->getPosition().y();
    direction_x = (x/dis);
    direction_y = (y/dis);
    MyPoint direction(direction_x, direction_y);
    double angle = Tool::vector_to_angle(direction) + int(qrand()%360 - 180)/18;
    direction_x = Tool::angel_to_vector(angle).x();
    direction_y = Tool::angel_to_vector(angle).y();
}
Bullet::~Bullet(){
}
