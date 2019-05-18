#ifndef ENEMY6_H
#define ENEMY6_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy6 : public Enemy
{
public:
    Enemy6();
    ~Enemy6(){delete icon;}
};

#endif // ENEMY6_H
