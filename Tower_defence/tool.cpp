#include "tool.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include "config.h"

Tool::Tool()
{

}
float Tool::vector_to_angle(MyPoint p){
    float x = p.x();
    float y = p.y();
    float bevel = pow(pow(x,2)+pow(y,2), 0.5);//斜边
    float _sin = y/bevel;
    float _cos = x/bevel;
    float ans1 = asin(_sin);
    float ans2 = acos(_cos);
    float ans;
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
MyPoint Tool::angel_to_vector(float angle){
    float ang = angle/180*M_PI;
    float _sin = sin(ang);
    float _cos = cos(ang);
    MyPoint p;
    p.setX(_cos);
    p.setY(_sin);
    return p;
}
int Tool::sign(float a){return a>0?1:-1;}
float Tool::abs(float a){return a>0?a:-a;}
