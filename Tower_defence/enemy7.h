#ifndef ENEMY7_H
#define ENEMY7_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy7 : public Enemy
{
public:
    Enemy7();
    ~Enemy7(){delete icon;}
};

#endif // ENEMY7_H
