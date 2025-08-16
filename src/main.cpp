#include "tgaimage.h"
#include "line.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv)
{
    TGAImage image(100, 100, TGAImage::RGB);
    Line l1(13, 20, 80, 40);
    Line l2(20, 13, 40, 80);
    Line l3(80, 40, 13, 20);
    l1.draw(image, white);
    l2.draw(image, red);
    l3.draw(image, red);
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}