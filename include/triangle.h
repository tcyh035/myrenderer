#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "point.h"
#include "shape.h"

class Triangle : public Shape
{
public:
    void barycentric(Point p, float &u, float &v);
    bool inside(Point p);
    void draw(TGAImage &, const TGAColor &, float* zbuffer) override;
    Triangle(const Point& p0, const Point& p1, const Point& p2) 
        : _p0(p0), _p1(p1), _p2(p2) {}
    Triangle(float x0, float y0, float x1, float y1, float x2, float y2) 
        : _p0(Point(x0, y0)), _p1(Point(x1, y1)), _p2(Point(x2, y2)) {}
private:
    Point _p0;
    Point _p1;
    Point _p2;
};

#endif