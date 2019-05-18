#ifndef ENEMY5_H
#define ENEMY5_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy5 : public Enemy
{
public:
    Enemy5();
    ~Enemy5(){delete icon;}
};

#endif // ENEMY5_H
