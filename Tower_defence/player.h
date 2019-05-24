#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include <vector>
#include "mypoint.h"


class Player: public GameObject
{
public:
    Player();//游戏主人公，可以有小人和公主
    int getLife(){return life;}
    void setLife(int l){life = l;}
    int getMoney(){return money;}
    void setMoney(int m){money = m;}



protected:
    int life;
    int money;

};

#endif // PLAYER_H
