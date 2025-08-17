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

int getIndex(int x, int y, int width)
{
    return y * width + x;
}

void Triangle::draw(TGAImage &image, const TGAColor &color, float* zbuffer)
{
    int xmin = static_cast<int>(std::min(_p0.x, std::min(_p1.x, _p2.x)));
    int xmax = static_cast<int>(std::max(_p0.x, std::max(_p1.x, _p2.x)));
    int ymin = static_cast<int>(std::min(_p0.y, std::min(_p1.y, _p2.y)));
    int ymax = static_cast<int>(std::max(_p0.y, std::max(_p1.y, _p2.y)));

    for (int i = xmin; i <= xmax; i++)
    {
        for (int j = ymin; j <= ymax; j++)
        {
            float u, v;
            barycentric(Point(static_cast<float>(i), static_cast<float>(j)), u, v);
            if (u >= 0 && v >= 0 && (1-u-v) >= 0)
            {
                if (zbuffer)
                {
                    float z = (1-u-v) * _p0.z + u * _p1.z + v * _p2.z;
                    int idx = getIndex(i, j, image.get_width());
                    if (z < zbuffer[idx])
                    {
                        zbuffer[idx] = z;
                        image.set(i, j, color);
                    }
                }
            }
        }
    }
}