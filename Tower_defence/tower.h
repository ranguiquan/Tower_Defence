#ifndef TOWER_H
#define TOWER_H
#include "gameobject.h"
#include "enemy.h"
#include <QPainter>
#include <vector>
#include <string>
#include <QMouseEvent>
#include <QVector>


using namespace std;

class Tower: public GameObject
{
public:
    explicit Tower(string name, bool isInstanlized);
    ~Tower();
    void setActivated(bool set){this->isActivated = set;}
    void setChosen(bool set){this->isChosen = set;}
    int getDamage() const{return damage;}
    int get_discovery_range() const{return discoveryRange;}
    void handleCoolDown();

    bool isFireReady() const {return fireReady;}
    void setFireReady(bool rd){//开火后重置属性
        fireReady = rd;
        coolDown = fireInterval;
    }
    QVector<Enemy*> hatred;
    void show(QPainter* p);
    double getAngle()const{return angle;}
    void setAngle(double r){angle = r;}
    double get_velocity_rotaion()const{return velocity_rotation;}


private:
    int damage;

    bool isActivated;
    bool isChosen;
    int discoveryRange;
    bool fireReady;
    double fireInterval;
    double coolDown;
    double angle;
    double velocity_rotation;
};

#endif // TOWER_H
