#include "mypoint.h"

MyPoint::MyPoint()
{

}
MyPoint::MyPoint(double x, double y){
    _x = x, _y = y;
}
MyPoint::MyPoint(const MyPoint& p){
    _x = p.x();
    _y = p.y();
}
