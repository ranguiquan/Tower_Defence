#ifndef MYPOINT_H
#define MYPOINT_H

#include <QMouseEvent>

class MyPoint
        //自定义的点类，为什么要自定义？一言难尽呐
{
public:
    MyPoint();
    MyPoint(double x, double y);
    MyPoint(const MyPoint& p);
    MyPoint(QMouseEvent* e);
    void setByMouseEvent(QMouseEvent* e);
    void setX(double x){this->_x = x;}
    void setY(double y){this->_y = y;}
    double x()const{return this->_x;}
    double y()const{return this->_y;}

private:
    double _x;
    double _y;
};

#endif // MYPOINT_H
