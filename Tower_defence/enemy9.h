#ifndef ENEMY9_H
#define ENEMY9_H


#include <QObject>
#include "gameobject.h"
#include <vector>
#include "mypoint.h"
#include "enemy.h"

class Enemy9 : public Enemy
{
public:
    Enemy9();
    ~Enemy9(){delete icon;}
};

#endif // ENEMY9_H
