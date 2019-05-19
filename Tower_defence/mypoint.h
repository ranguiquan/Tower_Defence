#ifndef MYPOINT_H
#define MYPOINT_H

#include <QMouseEvent>

class MyPoint
        //自定义的点类，为什么要自定义？一言难尽呐
{
public:
    MyPoint();
    MyPoint(float x, float y);
    MyPoint(const MyPoint& p);
    MyPoint(QMouseEvent* e);
    void setByMouseEvent(QMouseEvent* e);
    void setX(float x){this->_x = x;}
    void setY(float y){this->_y = y;}
    float x()const{return this->_x;}
    float y()const{return this->_y;}

private:
    float _x;
    float _y;
};

#endif // MYPOINT_H
