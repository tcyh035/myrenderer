#include "triangle.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "geometry.h"
#include "line.h"

void Triangle::barycentric(Point p, float& u, float&v)
{
    Vec3f s0(
        _p2.x - _p0.x,  // C.x - A.x
        _p1.x - _p0.x,  // B.x - A.x
        _p0.x - p.x     // A.x - P.x
    );
    Vec3f s1(
        _p2.y - _p0.y,  // C.y - A.y
        _p1.y - _p0.y,  // B.y - A.y
        _p0.y - p.y     // A.y - P.y
    );

    Vec3f crossResult = cross(s0, s1);

    if (std::abs(crossResult.z) < 1e-2f) {
        u = 1.0f;
        v = 1.0f;
        return;
    }

    u = crossResult.y / crossResult.z;
    v = crossResult.x / crossResult.z;
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
    float xmin = std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float xmax = -std::numeric_limits<float>::max();
    float ymax = -std::numeric_limits<float>::max();

    xmin = std::max(0.0f, std::min(std::min(_p0.x, _p1.x), _p2.x));
    xmax = std::min((float)(image.get_width()-1), std::max(std::max(_p0.x, _p1.x), _p2.x));
    ymin = std::max(0.0f, std::min(std::min(_p0.y, _p1.y), _p2.y));
    ymax = std::min((float)(image.get_height()-1), std::max(std::max(_p0.y, _p1.y), _p2.y));

    Vec3f P;
    for (P.x = xmin; P.x <= xmax; P.x++)
    {
        for (P.y = ymin; P.y <= ymax; P.y++)
        {
            float u, v;
            barycentric(Point(P.x, P.y, P.z), u, v);
            if (u >= 0 && v >= 0 && (1-u-v) >= 0)
            {
                if (zbuffer)
                {
                    P.z = 0;
                    P.z += _p0.z * (1-u-v);
                    P.z += _p1.z * u;
                    P.z += _p2.z * v;
                    int idx = getIndex(P.x, P.y, image.get_width());
                    if (P.z > zbuffer[idx])
                    {
                        zbuffer[idx] = P.z;
                        image.set(P.x, P.y, color);
                    }
                }
            }
        }
    }
}