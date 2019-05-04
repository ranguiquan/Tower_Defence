#include "bullet.h"
#include <QPixmap>
#include <config.h>
#include "scene.h"
#include <QDebug>

Bullet::Bullet(Tower* parent, Enemy* target)
{
    this->parent = parent;
    this->damage = parent->getDamage();
    this->icon = new QPixmap;
    icon->load(":/pictures/bullet_test.png");
    width = BULLET_WIDTH;
    height = BULLET_WIDTH;
    this->velocity = BULLET_VELOCITY;
    this->position.setX(parent->getPosition().x());
    this->position.setY(parent->getPosition().y());
    //方向想引入随机数
    double dis = Scene::distance((parent->getPosition()), (target->getPosition()));
    double x = target->getPosition().x()-parent->getPosition().x();
    double y = target->getPosition().y()-parent->getPosition().y();
    direction_x = (x/dis);

    direction_y = (y/dis);
}
Bullet::~Bullet(){
}
