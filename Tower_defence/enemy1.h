#ifndef ENEMY1_H
#define ENEMY1_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy1 : public Enemy
{
public:
    Enemy1();
    ~Enemy1(){delete icon;}
};

#endif // ENEMY1_H
