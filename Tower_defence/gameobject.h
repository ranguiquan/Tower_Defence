#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

class GameObject
{
public:
    explicit GameObject();
    ~GameObject();
    void setGameObject(int x, int y);
    void show(QPainter* p);
    bool isMouseEventInIt(QMouseEvent* e);
protected:
    QPoint position;//注意！这个position是中点位置
    QPixmap* icon;
    int width, height;//width是在x轴上的长度, height是在y轴上的长度

};

#endif // GAMEOBJECT_H
