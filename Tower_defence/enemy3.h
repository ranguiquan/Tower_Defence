#ifndef ENEMY3_H
#define ENEMY3_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy3 : public Enemy
{
public:
    Enemy3();
    ~Enemy3(){delete icon;}
};

#endif // ENEMY3_H
