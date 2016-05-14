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

using namespace std;

/*
double brightness(Vector_3 p1, Vector_3 p2, Vector_3 p3, Lightsource light)
{
    int x1 = p1.Getx();
    int y1 = p1.Gety();
    int z1 = p1.Getz();
    int x2 = p2.Getx();
    int y2 = p2.Gety();
    int z2 = p2.Getz();
    int x3 = p3.Getx();
    int y3 = p3.Gety();
    int z3 = p3.Getz();
    
    Vector_3 vec1(x2-x1, y2 - y1, z2 - z1);
    Vector_3 vec2(x3-x1, y3 - y1, z3 - z1);
    Vector_3 vec3 = vec1.CrossProduct(vec2);
    int a = vec3.Getx();
    int b = vec3.Gety();
    int c = vec3.Getz();
    
    double u1 = light.get_i();
    double u2 = light.get_j();
    double u3 = light.get_k();
    
    
    return abs(a*u1+b*u2+c*u3) / (sqrt(a*a+b*b+c*c) * sqrt(u1*u1+u2*u2+u3*u3));

}
*/

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


/*void drawSurface(Vector_3 p1, Vector_3 p2, Vector_3 p3, Space &newspace)
{
    int x1 = p1.Getx();
    int y1 = p1.Gety();
    int z1 = p1.Getz();
    int x2 = p2.Getx();
    int y2 = p2.Gety();
    int z2 = p2.Getz();
    int x3 = p3.Getx();
    int y3 = p3.Gety();
    int z3 = p3.Getz();
    
    Vector_3 vec1(x2-x1, y2 - y1, z2 - z1);
    Vector_3 vec2(x3-x1, y3 - y1, z3 - z1);
    Vector_3 vec3 = vec1.CrossProduct(vec2);
        
    int a = vec3.Getx();
    int b = vec3.Gety();
    int c = vec3.Getz();
    
    int x_min, y_min, z_min, x_max, y_max, z_max;
    x_min = findMin(x1, x2, x3);
    y_min = findMin(y1, y2, y3);
    z_min = findMin(z1, z2, z3);
    x_max = findMax(x1, x2, x3);
    y_max = findMax(y1, y2, y3);
    z_max = findMax(z1, z2, z3);

    
    for (int x = x_min; x <= x_max; x++)
    {
        for (int y = y_min; y <= y_max; y++)
        {
            for (int z = z_min; z <= z_max; z++)
            {
                if(a*(x-x1)+b*(y-y1)+c*(z-z1) == 0)
                {
                    newspace.MapTo(*new Vector_3(x, y, z));
                }
            }
        }
    }
    
    double m1 = (y2-y1) / (x2-x1);
    double m2 = (y2-y3) / (x2-x3);
    double m3 = (y2-y1) / (x2-x1);
    double m4 = (y3-y2) / (x3-x2);
    //int xdif = x2-x1;

    int x_incr = 0;
    if (x1 < x2)
        x_incr = 1;
    else
        x_incr = -1;
    
    int y_incr = 0;
    if (y1 < y2)
        y_incr = 1;
    else
        y_incr = -1;
    
    int z_incr = 0;
    if (z1 < z2)
        z_incr = 1;
    else
        z_incr = -1;
    
    //m1*(x-p1.Getx())+p1.Gety()
     //m2*(x-p2.Getx())+p2.Gety()
    
    for (int x = x1; x != x2; x+=x_incr)
    {
        for (int y = m1*(x-x1)+y1; y < m2*(x-x3)+y3; y++)
        {
             newspace.MapTo(*new Vector_3(x, y, 0));
        }
    }
    
}*/

/*void drawSurface(Vector_3 p1, Vector_3 p2, Vector_3 p3, Space &newspace, int red = 255, int green = 255, int blue = 255)
{
    int x1 = p1.Getx();
    int y1 = p1.Gety();
    int z1 = p1.Getz();
    int x2 = p2.Getx();
    int y2 = p2.Gety();
    int z2 = p2.Getz();
    int x3 = p3.Getx();
    int y3 = p3.Gety();
    int z3 = p3.Getz();
    
    int xdif1 = x2-x1;
    int ydif1 = y2-y1;
    int zdif1 = z2-z1;
    
    int length1 = round(sqrt(xdif1*xdif1+ydif1*ydif1+zdif1*zdif1));
    
    int xdif2 = x3-x1;
    int ydif2 = y3-y1;
    int zdif2 = z3-z1;
    
    int length2 = round(sqrt(xdif2*xdif2+ydif2*ydif2+zdif2*zdif2));
    
    int temp;
    if (length1 < length2)
    {
        temp = length1;
        length1 = length2;
        length2 = temp;
    }
    
    double x_comp1 = xdif1/double(length1);
    double y_comp1 = ydif1/double(length1);
    double z_comp1 = zdif1/double(length1);
    
    double x_comp2 = xdif2/double(length1);
    double y_comp2 = ydif2/double(length1);
    double z_comp2 = zdif2/double(length1);
    
    for(int i = 0; i < length1; i++)
    {
        drawLineSegment(*new Vector_3(x1 + i*x_comp1, y1 + i*y_comp1, z1 + i*z_comp1), *new Vector_3(x1 + i*x_comp2, y1 + i*y_comp2, z1 + i*z_comp2), newspace, red, green, blue);
    }

}*/

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

/*void drawCubeSurfaces(vector<Vector_3> points, Space &newspace, Lightsource light, int red = 255, int green = 255, int blue = 255)
{
    int color = 0;
    
    color = brightness(points[0], points[1], points[3], light);
    drawSurface(points[0], points[1], points[3], newspace, round(color*red), round(color*green), round(color*blue));
    drawSurface(points[6], points[1], points[3], newspace, round(color*red), round(color*green), round(color*blue));
    
    color = round(brightness(points[0], points[2], points[3], light));

    drawSurface(points[0], points[2], points[3], newspace, round(color*red), round(color*green), round(color*blue));
    drawSurface(points[5], points[2], points[3], newspace, round(color*red), round(color*green), round(color*blue));
    
    color = round(brightness(points[0], points[1], points[2], light));

    drawSurface(points[0], points[1], points[2], newspace, round(color*red), round(color*green), round(color*blue));
    drawSurface(points[4], points[1], points[2], newspace, round(color*red), round(color*green), round(color*blue));
    
    color = round(brightness(points[1], points[4], points[6], light));

    drawSurface(points[1], points[4], points[6], newspace, round(color*red), round(color*green), round(color*blue));
    drawSurface(points[7], points[4], points[6], newspace, round(color*red), round(color*green), round(color*blue));
    
    color = round(brightness(points[2], points[5], points[4], light));

    drawSurface(points[2], points[5], points[4], newspace, round(color*red), round(color*green), round(color*blue));
    drawSurface(points[7], points[5], points[4], newspace, round(color*red), round(color*green), round(color*blue));
    
    color = round(brightness(points[5], points[3], points[7], light));

    drawSurface(points[5], points[3], points[7], newspace, round(color*red), round(color*green), round(color*blue));
    drawSurface(points[6], points[3], points[7], newspace, round(color*red), round(color*green), round(color*blue));


}*/

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
    
    
    /*Space newspace;

    paraFunction(newspace);
    
    newspace.SaveImage("Cubes_wireframe");
     */
    
    /*int corner[3] = {0,100,200};
    Shape newcube(Cube(corner,100),8);
    drawCube(newcube.GetPoints(), newspace);
    drawCube(newcube.Rotate_X(40).Translate(-100, -200, 30).GetPoints(), newspace);
    */
   
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
    
    
    
    /*Space newspace2;
    paraFunction(newspace2);
    newspace2.SaveImage("Function1");*/
    
    
    /*Space newspace3;
    ballPath(20, -5, 40, -140, 10, 80, 60, 8, 15, newspace3);
    ballPath(20, -5, 40, -140, -40, 100, 20, 8, 20, newspace3);
    ballPath(20, -5, 40, -400, -100, 100, 100, 8, 10, newspace3);
    ballPath(20, -5, 40, -400, 100, 400, -200, 8, 40, newspace3);


    
    newspace3.SaveImage("Spheres1");*/

    
    
    
    /*Vector_3 newcorner(200,200,200);

    
    Sphere mysphere(newcorner, 200);
    mysphere.DrawSphere(newspace);
    mysphere.Rotate_Y(90).Translate(-500,0,0).DrawSphere(newspace);
    mysphere.Rotate_X(90).Translate(0,-200,0).DrawSphere(newspace);
    
    newspace.SaveImage("Cubes_wireframe");*/
    
    
    

    
    return 0;
    
}

