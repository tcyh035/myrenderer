#ifndef _POINT_H_
#define _POINT_H_

struct Point
{
    int x;
    int y;
    constexpr Point(int x0 = 0, int y0 = 0) : x(x0), y(y0) {}
};

#endif