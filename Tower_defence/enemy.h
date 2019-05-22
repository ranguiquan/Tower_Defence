#ifndef ENEMY_H
#define ENEMY_H
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include <string>

using namespace std;
class Enemy: public GameObject
{
public:
    explicit Enemy(string name);
    ~Enemy(){delete icon;}
    int get_velocity()const{return velocity;}
    double get_direction_x()const{return direction_x;}
    double get_direction_y()const{return direction_y;}
    int getLife(){return life;}
    void setLife(int l){life = l;}
    int getOriginalLife(){return originalLife;}
    bool isChosen(){
        QMouseEvent *e;
        if(this->isMouseEventInIt(e)&&e->button() == Qt::LeftButton)
            return true;
        else return false;
    }
    void setDamaged(bool b)
    {damage=b;}
    bool getDamage(){return damage;}

protected:
    int life;
    int originalLife;
    int velocity;
    double direction_x;
    double direction_y;
    bool damage;
};

#endif // ENEMY_H
