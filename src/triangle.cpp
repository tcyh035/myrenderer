#include "triangle.h"

#include <vector>
#include <chrono>
#include <iostream>

#include "geometry.h"
#include "line.h"

void Triangle::barycentric(Point p, float& u, float&v)
{
    Vec3f a = Vec3f(_p2.x - _p0.x, _p1.x - _p0.x, _p0.x - p.x) ^ Vec3f(_p2.y - _p0.y, _p1.y - _p0.y, _p0.y - p.y);
    if (std::abs(a.z) < 1) {
        u = 1;
        v = 1;
        return;
    }
    u = a.y / a.z;
    v = a.x / a.z;
}

bool Triangle::inside(Point p)
{
    float u, v;
    barycentric(p, u, v);
    return (u >= 0) && (v >= 0) && (1-v-u >= 0);
}

void Triangle::draw(TGAImage &image, const TGAColor &color)
{
    int xmin = std::min(_p0.x, std::min(_p1.x, _p2.x));
    int xmax = std::max(_p0.x, std::max(_p1.x, _p2.x));
    int ymin = std::min(_p0.y, std::min(_p1.y, _p2.y));
    int ymax = std::max(_p0.y, std::max(_p1.y, _p2.y));
    #pragma omp parallel for
    for (int i = xmin; i <= xmax; i++)
    {
        for (int j = ymin; j <= ymax; j++)
        {
            if (inside(Point(i, j)))
            {
                image.set(i, j, color);
            }
        }
    }
}