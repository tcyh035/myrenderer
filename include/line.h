#ifndef __LINE_H__
#define __LINE_H__

#include "point.h"
#include "shape.h"

class Line : public Shape
{
public:
    void draw(TGAImage&, const TGAColor&) override;
    Line(const Point& p0, const Point& p1) : _p0(p0), _p1(p1) {}
    Line(int x0, int y0, int x1, int y1) 
        : _p0(Point(x0, y0)), _p1(Point(x1, y1)) {}

private:
    Point _p0;
    Point _p1;
};

#endif