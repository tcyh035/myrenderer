#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "tgaimage.h"

class Shape
{
public:
    virtual void draw(TGAImage &, TGAColor) = 0;
    virtual ~Shape() = default;
};

#endif