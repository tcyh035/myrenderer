#include "tgaimage.h"
#include "model.h"
#include "line.h"
#include "triangle.h"

#include <vector>
#include <memory>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv)
{
    int width = 800;
    int height = 800;
    TGAImage image(width, height, TGAImage::RGB);
    Point p0(400, 200);
    Point p1(200, 600);
    Point p2(600, 600);
    Triangle t(p0, p1, p2);
    t.draw(image, red);

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}