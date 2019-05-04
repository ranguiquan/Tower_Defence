#ifndef MYPOINT_H
#define MYPOINT_H


class MyPoint
{
public:
    MyPoint();
    MyPoint(const MyPoint& p);
    void setX(double x){this->_x = x;}
    void setY(double y){this->_y = y;}
    double x()const{return this->_x;}
    double y()const{return this->_y;}

private:
    double _x;
    double _y;
};

#endif // MYPOINT_H
