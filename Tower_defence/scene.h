#ifndef SCENE_H
#define SCENE_H
#include <QString>
#include <QPainter>
#include <vector>
#include "gameobject.h"
#include <QPixmap>
#include "tower.h"
#include "enemy.h"
#include "bullet.h"




class Scene
{
public:
    Scene();
    ~Scene();
    //void setScene(QString map_name);
    void show(QPainter* p);//最终画图的，画之前要先更新成员状态


    void processor_mouseMoveEvent(QMouseEvent* e);
    void processor_mousePressEvent(QMouseEvent* e);
    void processor_keyPressEvent(QKeyEvent* e);

    void processor_hatredControll();//管理仇恨列表
    void creator_bullets();//子弹生成器
    void processor_damageConfirm();//确认造成伤害
    void processor_Move();//使子弹、敌人移动
    void processor_Tower_rotate();//炮塔的旋转

    static double distance(MyPoint a, MyPoint b);
private:
    QVector<Tower*> towers;
    QVector<Enemy*> enemies;
    QVector<Tower*> displayMenuOfTowers;
    QVector<Tower*> dragedTower;
    QVector<Bullet*> bullets;
    QPixmap* background;
};

#endif // SCENE_H
