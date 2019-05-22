#ifndef TOWER_H
#define TOWER_H
#include "gameobject.h"
#include "enemy.h"
#include <QPainter>
#include <vector>
#include <QMouseEvent>
#include <QVector>


using namespace std;

class Tower: public GameObject
{
public:
    explicit Tower(string name, bool isInstanlized);//感觉后面的参数用不上，可以优化
    ~Tower();
    void setActivated(bool set){this->isActivated = set;}//同样感觉用不上，最后可以删了
    void setChosen(bool set){this->isChosen = set;}//鸡肋冗余
    bool getIsChosen(){return isChosen;}
    int getDamage() const{return damage;}
    int get_discovery_range() const{return discoveryRange;}
    void handleCoolDown();//此功能可以移交Scene也可以不移交，不涉及对象之间交互的都可以放到类里面

    bool isFireReady() const {return fireReady;}//可以开火了吗？两种情况不行，没冷却，没转过来
    void fireCool(){//开火后重置属性
        fireReady = false;
        coolDown = fireInterval;
    }
    void setIsFireReady(bool re){fireReady = re;}
    QVector<Enemy*> hatred;//仇恨列表，为了方便Scene管理，放到public了
    void show(QPainter* p);
    float getAngle()const{return angle;}
    void setAngle(float r){angle = r;}
    float get_velocity_rotaion()const{return velocity_rotation;}
    bool getRotateReady()const{return rotateReady;}
    void setRotateReady(bool i){rotateReady = i;}


private:
    int damage;
    bool isActivated;//冗余
    bool isChosen;//冗余
    int discoveryRange;//侦测范围
    bool rotateReady;
    bool fireReady;
    float fireInterval;//开火时间间隔
    float coolDown;//冷却倒计时
    float angle;//炮管∠
    float velocity_rotation;//炮台转速
};

#endif // TOWER_H
