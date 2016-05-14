//
//  Surface.h
//  Matrix Visualization
//
//  Created by Laria R on 5/12/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

#ifndef Matrix_Visualization_Surface_h
#define Matrix_Visualization_Surface_h

#include "3Vector.h"
#include <cmath>

using namespace std;

class Surface : public Shape
{
private:
public:
    Surface(vector<Vector_3> points, int size = 3) : Shape(points, size)
    {
        n = size;
        for (int i = 0; i < n; i++)
        {
            arr.push_back(points[i]);
        }
    }
    Surface Rotate_X(double angle);
    Surface Rotate_Y(double angle);
    Surface Rotate_Z(double angle);
    Surface Scale(double x, double y, double z);
    Surface Translate(double x, double y, double z);
    Surface Castshadow(Surface s, Lightsource light);
        
    double Brightness(Lightsource light);

    void Draw(Space &newspace, Lightsource light, bool lighting = 1, int red = 255, int green = 255, int blue = 255);
    void Line(Vector_3 p1, Vector_3 p2, Space &newspace, int red = 255, int green = 255, int blue = 255);

};


Surface Surface::Rotate_X(double angle)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Rotate_X(angle));
    }
    Surface newsurface(new_arr);
    return newsurface;
}

Surface Surface::Rotate_Y(double angle)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Rotate_Y(angle));
    }
    Surface newsurface(new_arr);
    return newsurface;
}

Surface Surface::Rotate_Z(double angle)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Rotate_Z(angle));
    }
    Surface newsurface(new_arr);
    return newsurface;
}


Surface Surface::Scale(double x, double y, double z)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Scale(x, y, z));
    }
    Surface newsurface(new_arr);
    return newsurface;
}

Surface Surface::Translate(double x, double y, double z)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Translate(x, y, z));
    }
    Surface newsurface(new_arr);
    return newsurface;
}

void Surface::Draw(Space &newspace, Lightsource light, bool lighting, int red, int green, int blue)
{
    int x1 = arr[0].Getx();
    int y1 = arr[0].Gety();
    int z1 = arr[0].Getz();
    int x2 = arr[1].Getx();
    int y2 = arr[1].Gety();
    int z2 = arr[1].Getz();
    int x3 = arr[2].Getx();
    int y3 = arr[2].Gety();
    int z3 = arr[2].Getz();
    
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
    
    double bright = 1;
    
    if(lighting == 1)
    {
        bright = Brightness(light);
    }
    
    for(int i = 0; i < length1; i++)
    {
        Line(*new Vector_3(x1 + i*x_comp1, y1 + i*y_comp1, z1 + i*z_comp1), *new Vector_3(x1 + i*x_comp2, y1 + i*y_comp2, z1 + i*z_comp2), newspace, red * bright, green * bright, blue * bright);
    }
    
}

void Surface::Line(Vector_3 p1, Vector_3 p2, Space &newspace, int red, int green, int blue)
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

double Surface::Brightness(Lightsource light)
{
    int x1 = arr[0].Getx();
    int y1 = arr[0].Gety();
    int z1 = arr[0].Getz();
    int x2 = arr[1].Getx();
    int y2 = arr[1].Gety();
    int z2 = arr[1].Getz();
    int x3 = arr[2].Getx();
    int y3 = arr[2].Gety();
    int z3 = arr[2].Getz();
    
    Vector_3 vec1(x2-x1, y2 - y1, z2 - z1);
    Vector_3 vec2(x3-x1, y3 - y1, z3 - z1);
    Vector_3 vec3 = vec1.CrossProduct(vec2);
    int a = vec3.Getx();
    int b = vec3.Gety();
    int c = vec3.Getz();
    
    double u1 = light.get_i();
    double u2 = light.get_j();
    double u3 = light.get_k();
    
    /*double val = (a*u1+b*u2+c*u3) / (sqrt(a*a+b*b+c*c) * sqrt(u1*u1+u2*u2+u3*u3));
     if (val >=0)
     return val;
     else
     return 0;*/
    
    return abs(a*u1+b*u2+c*u3) / (sqrt(a*a+b*b+c*c) * sqrt(u1*u1+u2*u2+u3*u3));
    
}

Surface Surface::Castshadow(Surface s, Lightsource light)
{
    int x1 = arr[0].Getx();
    int y1 = arr[0].Gety();
    int z1 = arr[0].Getz();
    int x2 = arr[1].Getx();
    int y2 = arr[1].Gety();
    int z2 = arr[1].Getz();
    int x3 = arr[2].Getx();
    int y3 = arr[2].Gety();
    int z3 = arr[2].Getz();
    
    Vector_3 vec1(x2-x1, y2 - y1, z2 - z1);
    Vector_3 vec2(x3-x1, y3 - y1, z3 - z1);
    Vector_3 normal = vec1.CrossProduct(vec2);
    
    
    Vector_3 origin(light.get_i(), light.get_j(), light.get_k());
    
    Vector_3 point1 = s.GetPoints()[0];
    Vector_3 point2 = s.GetPoints()[1];
    Vector_3 point3 = s.GetPoints()[2];

    Vector_3 line1 (point1.Getx()-origin.Getx(),point1.Gety()-origin.Gety(),point1.Getz()-origin.Getz());
    Vector_3 line2 (point2.Getx()-origin.Getx(),point2.Gety()-origin.Gety(),point2.Getz()-origin.Getz());
    Vector_3 line3 (point3.Getx()-origin.Getx(),point3.Gety()-origin.Gety(),point3.Getz()-origin.Getz());


    
    double a = normal.Getx();
    double b = normal.Gety();
    double c = normal.Getz();
    
    double i = origin.Getx();
    double j = origin.Gety();
    double k = origin.Getz();
    
    double u = line1.Getx();
    double v = line1.Gety();
    double w = line1.Getz();
    
    double u2 = line2.Getx();
    double v2 = line2.Gety();
    double w2 = line2.Getz();
    
    double u3 = line3.Getx();
    double v3 = line3.Gety();
    double w3 = line3.Getz();
    
    
    double d = a * x1 + b * y1 + c * z1;
    
    double t = (d - a*i - b*j - c*k) / (a*u + b*v + c*w);
    Vector_3 shadowpoint1(i + u*t, j + v*t, k + w*t);
    
    double t2 = (d - a*i - b*j - c*k) / (a*u2 + b*v2 + c*w2);
    Vector_3 shadowpoint2(i + u2*t2, j + v2*t2, k + w2*t2);

    double t3 = (d - a*i - b*j - c*k) / (a*u3 + b*v3 + c*w3);
    Vector_3 shadowpoint3(i + u3*t3, j + v3*t3, k + w3*t3);
    
    /*cout <<"shadowcoordinates1: " << endl << shadowpoint1.Getx() << endl << shadowpoint1.Gety() << endl << shadowpoint1.Getz() << endl << endl;
    cout <<"shadowcoordinates2: " << endl << shadowpoint2.Getx() << endl << shadowpoint2.Gety() << endl << shadowpoint2.Getz() << endl << endl;
    cout <<"shadowcoordinates3: " << endl << shadowpoint3.Getx() << endl << shadowpoint3.Gety() << endl << shadowpoint3.Getz() << endl << endl;*/
    
    vector<Vector_3> shadowpoints;
    shadowpoints.push_back(shadowpoint1);
    shadowpoints.push_back(shadowpoint2);
    shadowpoints.push_back(shadowpoint3);
    
    Surface shadow(shadowpoints);
    
    return shadow;
}



#endif
