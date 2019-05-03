#ifndef TOWER_H
#define TOWER_H
#include "gameobject.h"
#include "enemy.h"
#include <QPainter>
#include <vector>
#include <string>
#include <QMouseEvent>


using namespace std;

class Tower: public GameObject
{
public:
    explicit Tower(string name, bool isInstanlized);
    ~Tower();
    void setActivated(bool set){this->isActivated = set;}
    void setChosen(bool set){this->isChosen = set;}


private:
    int damage;
    vector<Enemy*> enemies;
    bool isActivated;
    bool isChosen;

};

#endif // TOWER_H
