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
    int getOriginalLife(){return originalLife;}

protected:
    int life;
    int originalLife;
    int velocity;
    float direction_x;
    float direction_y;

};

#endif // ENEMY_H
