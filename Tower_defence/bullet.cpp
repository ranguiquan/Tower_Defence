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
    icon->load(":/pictures/bullet/bullet1.png");
    this->width = BULLET_WIDTH;
    this->height = BULLET_WIDTH;
    this->velocity = BULLET_VELOCITY;


    double dis = Scene::distance((parent->getPosition()), (target->getPosition()));
    double x = target->getPosition().x()-parent->getPosition().x();
    double y = target->getPosition().y()-parent->getPosition().y();
    direction_x = (x/dis);
    direction_y = (y/dis);
    this->position.setX(parent->getPosition().x() + direction_x * parent->getWidth()/2);
    this->position.setY(parent->getPosition().y() + direction_y * parent->getWidth()/2);
    MyPoint direction(direction_x, direction_y);
    double angle = Tool::vector_to_angle(direction) + int(qrand()%360 - 180)/18;
    direction_x = Tool::angel_to_vector(angle).x();
    direction_y = Tool::angel_to_vector(angle).y();
}
Bullet::Bullet(Tower* parent, MyPoint vec_angle){
    this->parent = parent;
    this->damage = parent->getDamage();
    this->icon = new QPixmap;
    icon->load(":/pictures/bullet/bullet1.png");
    this->width = BULLET_WIDTH;
    this->height = BULLET_WIDTH;
    this->velocity = BULLET_VELOCITY;
    this->position.setX(parent->getPosition().x() + vec_angle.x() * parent->getWidth()/2);
    this->position.setY(parent->getPosition().y() + vec_angle.y() * parent->getWidth()/2);


    double angle = Tool::vector_to_angle(vec_angle) + int(qrand()%360 - 180)/18;
    direction_x = Tool::angel_to_vector(angle).x();
    direction_y = Tool::angel_to_vector(angle).y();
}
Bullet::~Bullet(){
    delete icon;
}
