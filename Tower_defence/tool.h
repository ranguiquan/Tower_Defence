#ifndef TOOL_H
#define TOOL_H
#include "mypoint.h"

//角度是向右为0度，顺时针旋转为正方向，谨记！

class Tool
{
public:
    Tool();
    static double vector_to_angle(MyPoint p);//把向量转换成角度制的∠
    static MyPoint angel_to_vector(double angle);//上面的反过来
    static int sign(double a);//符号函数
};

#endif // TOOL_H