#include "line.h"

void Line::draw(TGAImage & image, TGAColor color)
{
    int x0 = _p0.x;
    int y0 = _p0.y;
    int x1 = _p1.x;
    int y1 = _p1.y;

    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++)
    {
        float t = (float)(x - x0) / (float)(x1 - x0);
        int y = y0 * (1.0 - t) + y1 * t;
        if (steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
    }
}
