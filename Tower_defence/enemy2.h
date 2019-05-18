#ifndef ENEMY2_H
#define ENEMY2_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy2 : public Enemy
{
public:
    Enemy2();
    ~Enemy2(){delete icon;}
};

#endif // ENEMY2_H
