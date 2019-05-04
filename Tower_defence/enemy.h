#ifndef ENEMY_H
#define ENEMY_H
#include "gameobject.h"
#include <vector>
#include <QPoint>

class Enemy: public GameObject
{
public:
    explicit Enemy();
    ~Enemy(){}
    int get_velocity()const{return velocity;}
    double get_direction_x()const{return direction_x;}
    double get_direction_y()const{return direction_y;}
protected:
    int life;
    int velocity;
    double direction_x;
    double direction_y;
};

#endif // ENEMY_H
