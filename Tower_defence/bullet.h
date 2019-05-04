#ifndef BULLET_H
#define BULLET_H
#include "gameobject.h"
#include "tower.h"
#include "mypoint.h"


class Bullet: public GameObject
{
public:
    Bullet(Tower* parent, Enemy* target);//子弹用炮塔和敌人初始化
    ~Bullet();
    int get_velocity()const{return velocity;}
    double get_direction_x()const{return direction_x;}
    double get_direction_y()const{return direction_y;}
    int getDamage(){return damage;}
protected:
    Tower* parent;
    int damage;//单颗伤害
    int velocity;//速度
    double direction_x;
    double direction_y;//方向

};

#endif // BULLET_H
