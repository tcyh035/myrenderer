#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "tgaimage.h"

class Shape
{
public:
    virtual void draw(TGAImage&, const TGAColor&, float* zbuffer = nullptr) = 0;
    virtual ~Shape() = default;
};

#endif