#ifndef BULLET_H
#define BULLET_H
#include "gameobject.h"
#include "tower.h"
#include <QPoint>


class Bullet: public GameObject
{
public:
    Bullet(Tower* parent, Enemy* target);
    ~Bullet();
    int get_velocity()const{return velocity;}
    double get_direction_x()const{return direction_x;}
    double get_direction_y()const{return direction_y;}
protected:
    Tower* parent;
    int damage;
    int velocity;
    double direction_x;
    double direction_y;

};

#endif // BULLET_H
