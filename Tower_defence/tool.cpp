#include "tool.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include "config.h"

Tool::Tool()
{

}
double Tool::vector_to_angle(MyPoint p){
    double x = p.x();
    double y = p.y();
    double bevel = pow(pow(x,2)+pow(y,2), 0.5);//斜边
    double _sin = y/bevel;
    double _cos = x/bevel;
    double ans1 = asin(_sin);
    double ans2 = acos(_cos);
    double ans;
    if(_sin >= 0 && _cos >= 0){
        ans = ans1;
    }else if(_sin >= 0 && _cos <= 0){
        ans = ans2;
    }else if(_sin <= 0 && _cos >= 0){
        ans = ans1+ M_PI*2;
    }else{
        ans = 2*M_PI - ans2;
    }
    return ans*180/M_PI;
}
MyPoint Tool::angel_to_vector(double angle){
    double ang = angle/180*M_PI;
    double _sin = sin(ang);
    double _cos = cos(ang);
    MyPoint p;
    p.setX(_cos);
    p.setY(_sin);
    return p;
}
int Tool::sign(double a){return a>0?1:-1;}
