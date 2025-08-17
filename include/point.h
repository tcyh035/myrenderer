#ifndef __POINT_H__
#define __POINT_H__

struct Point
{
    float x;
    float y;
    float z;
    constexpr Point(float x0 = 0.0f, float y0 = 0.0f, float z0 = 0.0f) : x(x0), y(y0), z(z0) {}
};

#endif