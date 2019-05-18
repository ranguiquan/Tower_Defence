#ifndef ENEMY4_H
#define ENEMY4_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy4 : public Enemy
{
public:
    Enemy4();
    ~Enemy4(){delete icon;}
};

#endif // ENEMY4_H
