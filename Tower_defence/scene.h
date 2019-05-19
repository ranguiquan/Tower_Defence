#ifndef SCENE_H
#define SCENE_H
#include <QString>
#include <QPainter>
#include <vector>
#include "gameobject.h"
#include <QPixmap>
#include "tower.h"
#include "tower.h"
#include "enemy.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "enemy5.h"
#include "enemy6.h"
#include "enemy7.h"
#include "enemy8.h"
#include "enemy9.h"
#include "bullet.h"
#include "player.h"
#include <QTime>

class Scene: public QObject
{
    Q_OBJECT
public:
    Scene();
    ~Scene();

    //一个未实现的场景切换
    //void setScene(QString map_name);

    void show(QPainter* p);//最终画图的，画之前要先更新成员状态

    void processor_mouseMoveEvent(QMouseEvent* e);//处理鼠标移动的
    void processor_mousePressEvent(QMouseEvent* e);//处理鼠标点击的
    void processor_keyPressEvent(QKeyEvent* e);
    void processor_mouseReleseEvent(QMouseEvent* e);

    void processor_hatredControll();//管理仇恨列表
    void creator_bullets();//子弹生成器
    void processor_damageConfirm();//确认造成伤害
    void processor_Move();//使子弹、敌人移动
    void processor_Tower_rotate();//炮塔的旋转
    void object_delete();//对象出界删除，删除到达终点或失去生命的敌人，删除生命为0的炮塔，删除死亡的主角


    static float distance(MyPoint a, MyPoint b);//返回两点间距离，不应该放在这，懒得改了，乐意改的话可以优化一下

private:
    QVector<Tower*> towers;//防御塔列表（已激活）
    QVector<Enemy*> enemies;//敌人容器
    QVector<Tower*> displayMenuOfTowers;//防御塔菜单（未激活的塔，不参与游戏）
    QVector<Tower*> dragedTower;//被鼠标拖动的塔
    QVector<Bullet*> bullets;//子弹容器
    QPixmap* background;//背景
    Player *player;
    float secondCounter;
    bool manualMod;//可以手动控制
    MyPoint mouseMoveEventPoint;
    bool mouseLeftPressed;
private slots:
    void enemy_generator();//敌人生成器
};

#endif // SCENE_H
