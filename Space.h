#include<cmath>

#include"bitmap_image.h"
#include"3Vector.h"

const int DISTANCE = 1000;
const int SCALE = 1000;

class Space
{
private:
    bitmap_image* i;
    int map[SCALE][SCALE];
public:
    Space();
    void MapTo(Vector_3 vector, int r, int g, int b);
    void MapToCeil(Vector_3 vector);
    void MapToFloor(Vector_3 vector);
    void SaveImage(string fname);
    int Red(double x, double y, double z);
    int Green(double x, double y, double z);

    int Blue(double x, double y, double z);

    
};

Space::Space()
{
    i = new bitmap_image(SCALE,SCALE);
    
    for(int i = 0; i < SCALE; i++)
    {
        for(int j = 0; j < SCALE; j++)
        {
            map[i][j] = (-1)*DISTANCE;
        }
    }
}


void Space::MapTo(Vector_3 vector, int r = 255, int g = 255, int b = 255)
{
    double x,y,z;
    x = vector.Getx();
    y = vector.Gety();
    z = vector.Getz();
    
    double dil_fact = 1;
    dil_fact = DISTANCE / ((-1)*round(z) + DISTANCE);

    int newx = round(dil_fact*round(x) + (SCALE / 2));
    int newy = round(dil_fact*(-1)*round(y) + (SCALE / 2));
    
    if(newx < SCALE && newx > 0 && newy < SCALE && newy > 0)
    {

        if(map[newx][newy] <= z) //checking to make sure pixel isn't "blocked" by closer pixel
        {
            (*i).set_pixel(newx, newy, r, g, b);
            map[newx][newy] = z;
        }

    }
    
}

int Space::Red(double x, double y, double z)
{
    int q = 100 - .2 *z;
    if(q > 255)
        return 255 - (q % 255);
    else if (q < 0)
        return 255 - (q % 255);
    else
        return q;
}

int Space::Green(double x, double y, double z)
{
    int q = .10*z;
    if(q > 255)
        return 255 - (q % 255);
    else if (q < 0)
        return 255 - (q % 255);
    else
        return q;
}

int Space::Blue(double x, double y, double z)
{
    int q = 255 - .30*z;
    if(q > 255)
        return 255 - (q % 255);
    else if (q < 0)
        return 255 - (q % 255);
    else
        return q;
}


void Space::MapToCeil(Vector_3 vector)
{
    double x,y,z;
    x = vector.Getx();
    y = vector.Gety();
    z = vector.Getz();
    
    double dil_fact = 1;
    dil_fact = DISTANCE / ((-1)*ceil(z) + DISTANCE);
    
    int newx = ceil(dil_fact*ceil(x) + (SCALE / 2));
    int newy = ceil(dil_fact*(-1)*ceil(y) + (SCALE / 2));
    
    if(newx < SCALE && newx > 0 && newy < SCALE && newy > 0)
    {
        (*i).set_pixel(newx, newy, 250, 250, 250);
    }
    
}


void Space::MapToFloor(Vector_3 vector)
{
    double x,y,z;
    x = vector.Getx();
    y = vector.Gety();
    z = vector.Getz();
    
    double dil_fact = 1;
    dil_fact = DISTANCE / ((-1)*floor(z) + DISTANCE);
    
    int newx = floor(dil_fact*floor(x) + (SCALE / 2));
    int newy = floor(dil_fact*(-1)*floor(y) + (SCALE / 2));
    
    if(newx < SCALE && newx > 0 && newy < SCALE && newy > 0)
    {
        (*i).set_pixel(newx, newy, 250, 250, 250);
    }
    
}

void Space::SaveImage(string fname)
{
    (*i).save_image([[DIRECTORY]] + fname + ".bmp"); 
}

