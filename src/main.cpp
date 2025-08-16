#include "tgaimage.h"
#include "model.h"
#include "line.h"
#include "triangle.h"

#include <vector>
#include <memory>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

TGAColor randomColor()
{
    return TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);
}

int main(int argc, char** argv)
{
    int width = 800;
    int height = 800;
    TGAImage image(width, height, TGAImage::RGB);
    std::shared_ptr<Model> model = std::make_shared<Model>("../../../../obj/african_head.obj");
    Vec3f light_dir(0,0,-1);
    for (int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++)
        {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.);
            world_coords[j]  = v;
        }

        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        n.normalize();
        float intensity = n*light_dir;
        if (intensity > 0)
        {
            Triangle t(Point(screen_coords[0].x, screen_coords[0].y),
                       Point(screen_coords[1].x, screen_coords[1].y),
                       Point(screen_coords[2].x, screen_coords[2].y));
            t.draw(image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
            // t.draw(image, TGAColor(randomColor()));
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}