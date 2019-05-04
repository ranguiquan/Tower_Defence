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
    void setGameObject(double x, double y);
    MyPoint getPosition(){
        return position;
    }
    void show(QPainter* p);
    bool isMouseEventInIt(QMouseEvent* e);
    bool isMyPointInIt(MyPoint p);
protected:
    MyPoint position;//注意！这个position是中点位置
    QPixmap* icon;
    int width, height;//width是在x轴上的长度, height是在y轴上的长度

};

#endif // GAMEOBJECT_H
