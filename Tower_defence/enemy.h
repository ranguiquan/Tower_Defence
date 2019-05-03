#ifndef ENEMY_H
#define ENEMY_H
#include "gameobject.h"
#include <vector>

class Enemy: public GameObject
{
public:
    explicit Enemy();
    ~Enemy(){}

protected:
    int life;
};

#endif // ENEMY_H
