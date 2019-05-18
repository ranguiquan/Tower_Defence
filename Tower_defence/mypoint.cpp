#include "mypoint.h"

MyPoint::MyPoint()
{
    _x = 0, _y = 0;
}
MyPoint::MyPoint(double x, double y){
    _x = x, _y = y;
}
MyPoint::MyPoint(const MyPoint& p){
    _x = p.x();
    _y = p.y();
}
MyPoint::MyPoint(QMouseEvent* e){
    _x = e->x();
    _y = e->y();
}
void MyPoint::setByMouseEvent(QMouseEvent *e){
    this->_x = e->x();
    this->_y = e->y();
}
