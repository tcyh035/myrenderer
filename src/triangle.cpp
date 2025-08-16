#include "triangle.h"
#include "line.h"

void Triangle::draw(TGAImage &image, const TGAColor &color)
{
    // sort
    if (_p0.y > _p1.y)
    {
        std::swap(_p0, _p1);
    }
    if (_p0.y > _p2.y)
    {
        std::swap(_p0, _p2);
    }

    // rasterize left and right edges
    if (_p1.x > _p2.x)
    {
        std::swap(_p1, _p2);
    }

    Line l1(_p0, _p1);
    Line l2(_p0, _p2);
    l1.draw(image, color);
    l2.draw(image, color);

    // rasterize lines
    if (_p1.y > _p2.y)
    {
        std::swap(_p1, _p2);
    }

    auto a1 = (_p1.y - _p0.y) / (float)(_p1.x - _p0.x);
    auto b1 = _p0.y - a1 * _p0.x;
    auto a2 = (_p2.y - _p0.y) / (float)(_p2.x - _p0.x);
    auto b2 = _p0.y - a2 * _p0.x;
    int maxy = _p2.y;

    for (int i = _p0.y; i <= _p1.y; i++)
    {
        int x1 = (i - b1) / a1;
        int x2 = (i - b2) / a2;
        Line l(x1, i, x2, i);
        l.draw(image, color);
    }

    auto a3 = (_p2.y - _p1.y) / (float)(_p2.x - _p1.x);
    auto b3 = _p1.y - a3 * _p1.x;

    for (int i = _p1.y + 1; i <= maxy; i++)
    {
        int x2 = (i - b2) / a2;
        int x3 = (i - b3) / a3;
        Line l(x2, i, x3, i);
        l.draw(image, color);
    }
}