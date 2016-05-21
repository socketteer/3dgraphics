#include <iostream>
#include <vector>
#include <cmath>

#include "Matrix.h"
#include "3Vector.h"
#include "bitmap_image.h"
#include "Space.h"
#include "Shape.h"
#include "Sphere.h"
#include "Lightsource.h"
#include "Surface.h"
#include "DynamicShape.h"
#include "Pointnode.h"
#include "Cube.h"

using namespace std;

void drawLineSegment(Vector_3 p1, Vector_3 p2, Space &newspace, int red = 255, int green = 255, int blue = 255)
{
    int x1 = p1.Getx();
    int y1 = p1.Gety();
    int z1 = p1.Getz();
    int x2 = p2.Getx();
    int y2 = p2.Gety();
    int z2 = p2.Getz();
    
    int xdif = x2-x1;
    int ydif = y2-y1;
    int zdif = z2-z1;
    
    int length = round(sqrt(xdif*xdif+ydif*ydif+zdif*zdif));
    if (length == 0) //to avoid division by 0
    {
        return;
    }
    
    double x_comp = xdif/double(length);
    double y_comp = ydif/double(length);
    double z_comp = zdif/double(length);
    
    
    for(int i = 0; i < length; i++)
    {
        newspace.MapTo(*new Vector_3(x1 + i*x_comp, y1 + i*y_comp, z1 + i*z_comp), red, green, blue);
    }
    
}

vector<Vector_3> Cube(int corner[3], int length)
{
    vector<Vector_3> points;
    
    points.push_back(*new Vector_3(corner[0],corner[1],corner[2]));
    points.push_back(*new Vector_3(corner[0]+length,corner[1],corner[2]));
    points.push_back(*new Vector_3(corner[0],corner[1]+length,corner[2]));
    points.push_back(*new Vector_3(corner[0],corner[1],corner[2]+length));
    points.push_back(*new Vector_3(corner[0]+length,corner[1]+length,corner[2]));
    points.push_back(*new Vector_3(corner[0],corner[1]+length,corner[2]+length));
    points.push_back(*new Vector_3(corner[0]+length,corner[1],corner[2]+length));
    points.push_back(*new Vector_3(corner[0]+length,corner[1]+length,corner[2]+length));

    return points;
}

vector<Vector_3> Cuboid(int corner[3], int length, int height, int depth)
{
    vector<Vector_3> points;
    
    points.push_back(*new Vector_3(corner[0],corner[1],corner[2]));
    points.push_back(*new Vector_3(corner[0]+length,corner[1],corner[2]));
    points.push_back(*new Vector_3(corner[0],corner[1]+height,corner[2]));
    points.push_back(*new Vector_3(corner[0],corner[1],corner[2]+depth));
    points.push_back(*new Vector_3(corner[0]+length,corner[1]+height,corner[2]));
    points.push_back(*new Vector_3(corner[0],corner[1]+height,corner[2]+depth));
    points.push_back(*new Vector_3(corner[0]+length,corner[1],corner[2]+depth));
    points.push_back(*new Vector_3(corner[0]+length,corner[1]+height,corner[2]+depth));
    
    return points;
}

void drawCube(vector<Vector_3> points, Space &newspace)
{
    drawLineSegment(points[0], points[1], newspace);
    drawLineSegment(points[0], points[3], newspace);
    drawLineSegment(points[1], points[6], newspace);
    drawLineSegment(points[3], points[6], newspace);
    
    drawLineSegment(points[0], points[2], newspace);
    drawLineSegment(points[3], points[5], newspace);
    drawLineSegment(points[1], points[4], newspace);
    drawLineSegment(points[7], points[6], newspace);
    
    drawLineSegment(points[2], points[4], newspace);
    drawLineSegment(points[2], points[5], newspace);
    drawLineSegment(points[4], points[7], newspace);
    drawLineSegment(points[5], points[7], newspace);
}


void paraFunction(Space &newspace)
{
    /*
     
     Cool functions:
          
     j-50, (0.1)*j*j-40, i-500
     
     j+70, (0.1)*j*j+i, j*i
     
     (0.0001)*j*j*j+100, j-50, i)
     
     j, j+200, i
     
     
     */
    for(int i = -2000; i < 2000; i++)
    {
        for(int j = -1000; j < 1000; j++)
        {
            newspace.MapTo(*new Vector_3( j-50, (0.1)*j*j-40, i-500));
        }
    }
}

void ballPath(int ballSize, int initial_x, int initial_y, int initial_z, int x, int y, int z, double gravity, int numFrames, Space &newspace)
{
    for(int i = 0; i < numFrames; i++)
    {
        Vector_3 newcenter(i*x+initial_x, i*y-gravity*i*i+initial_y, i*z+initial_z);
        Sphere mysphere(newcenter, ballSize);
        mysphere.DrawSphere(newspace);
    }
}

int main()
{
    
    /// LIGHTING TEST
    Space newspace;
    Lightsource light(0,200,0);

    
   
    
    
    Vector_3 p1(400,-200,0);
    Vector_3 p2(300,-200,0);
    Vector_3 p3(300,-200,-100);
    
    vector<Vector_3> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
   
    Surface newsurface(points);
    
    newsurface.Draw(newspace, light);
    
    /*
    Vector_3 p4(200,100,0);
    Vector_3 p5(100,-100,100);
    Vector_3 p6(100,-40,-100);
    
    vector<Vector_3> points2;
    points2.push_back(p4);
    points2.push_back(p5);
    points2.push_back(p6);
    
    
    Surface newsurface2(points2);
    
    newsurface2.Draw(newspace, light);
    
    newsurface.Castshadow(newsurface2, light).Draw(newspace, light, 0, 255, 0, 0);
    */
    
    
    for(int i = 0; i < 8; i++)
    {
        newsurface.Rotate_X(15*i).Translate(-100*i,0,0).Draw(newspace, light);


    }
    
    

    newspace.SaveImage("Lighting");
    
    

    
    return 0;
    
}

