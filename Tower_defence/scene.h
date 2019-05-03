#ifndef SCENE_H
#define SCENE_H
#include <QString>
#include <QPainter>
#include <vector>
#include "gameobject.h"
#include "tower.h"
#include "enemy.h"




class Scene
{
public:
    Scene();
    ~Scene();
    //void setScene(QString map_name);
    void show(QPainter* p);//最终画图的，画之前要先更新成员状态


    void processor_mouseMoveEvent(QMouseEvent* e);
    void processor_mousePressEvent(QMouseEvent* e);

private:
    std::vector<Tower*> towers;
    std::vector<Enemy*> enemies;
    std::vector<Tower*> displayMenuOfTowers;
    std::vector<Tower*> dragedTower;
};

#endif // SCENE_H
