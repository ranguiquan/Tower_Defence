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
    float get_direction_x()const{return direction_x;}
    float get_direction_y()const{return direction_y;}
    int getLife(){return life;}
    void setLife(int l){life = l;}
    void setVelocity(int v){velocity=v;}
    int getOriginalLife(){return originalLife;}
    void setDamaged(bool b){damage=b;}
    bool getDamage(){return damage;}
    bool isChosen=0;
public slots:
    void setischosen(bool b){isChosen=b;}

protected:
    int life;
    int originalLife;
    int velocity;
    double direction_x;
    double direction_y;
    bool damage;
};

#endif // ENEMY_H
