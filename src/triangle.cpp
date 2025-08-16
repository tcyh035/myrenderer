#include "triangle.h"
#include "line.h"

void Triangle::draw(TGAImage &image, const TGAColor &color)
{
    // old version: draw the three edges
    Line l1(_p0, _p1);
    Line l2(_p1, _p2);
    Line l3(_p2, _p0);
    l1.draw(image, color);
    l2.draw(image, color);
    l3.draw(image, color);
}