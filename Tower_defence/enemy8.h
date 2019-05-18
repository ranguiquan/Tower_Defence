#ifndef ENEMY8_H
#define ENEMY8_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy8 : public Enemy
{
public:
    Enemy8();
    ~Enemy8(){delete icon;}
};

#endif // ENEMY8_H
