#include "mypoint.h"

MyPoint::MyPoint()
{

}
MyPoint::MyPoint(const MyPoint& p){
    _x = p.x();
    _y = p.y();
}
