#include "tgaimage.h"
#include "model.h"
#include "line.h"

#include <vector>
#include <memory>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv)
{
    int width = 800;
    int height = 800;
    TGAImage image(width, height, TGAImage::RGB);
    std::shared_ptr<Model> model = std::make_shared<Model>("../../../../obj/african_head.obj");
    for (int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++)
        {
            Vec3f v0 = model->vert(face[j % 3]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.0f) * width / 2.0f;
            int y0 = (v0.y + 1.0f) * height / 2.0f;
            int x1 = (v1.x + 1.0f) * width / 2.0f;
            int y1 = (v1.y + 1.0f) * height / 2.0f;
            Line l(x0, y0, x1, y1);
            l.draw(image, white);
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}