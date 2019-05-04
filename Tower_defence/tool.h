#ifndef TOOL_H
#define TOOL_H
#include "mypoint.h"

//角度是向右为0度，顺时针旋转为正方向，谨记！

class Tool
{
public:
    Tool();
    static double vector_to_angle(MyPoint p);
    static MyPoint angel_to_vector(double angle);
    static int sign(double a);
};

#endif // TOOL_H
