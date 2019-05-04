#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "mypoint.h"
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>


class GameObject
{
public:
    explicit GameObject();
    ~GameObject();
    void setGameObject(double x, double y);//设定中心坐标
    MyPoint getPosition(){return position;}
    void show(QPainter* p);
    bool isMouseEventInIt(QMouseEvent* e);//检测鼠标事件是否点中该对象
    bool isMyPointInIt(MyPoint p);//检测点是否在对象中
protected:
    MyPoint position;//注意！这个position是中点位置
    QPixmap* icon;
    int width, height;//width是在x轴上的长度, height是在y轴上的长度

};

#endif // GAMEOBJECT_H
