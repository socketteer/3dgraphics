//
//  Sphere.h
//  Matrix Visualization
//
//  Created by Laria R on 10/21/15.
//  Copyright (c) 2015 Laria R. All rights reserved.
//

#ifndef Matrix_Visualization_Sphere_h
#define Matrix_Visualization_Sphere_h
#include "3Vector.h"
#include <cmath>

using namespace std;

class Sphere
{
private:
    Vector_3 center;
    int radius;
    int numlines;
public:
    Sphere(Vector_3 v, int r, int n = 8)
    {
        center = v;
        radius = r;
        numlines = n;
    }
    void DrawSphere(Space &newspace)
    {
        for(double i = 0; i < 2*PI; i+=PI/numlines)
        {
            for(int j = -radius; j < radius; j++)
            {
                newspace.MapTo(*new Vector_3(sqrt(radius*radius-j*j)*cos(i) + center.Getx(), j + center.Gety(), sqrt(radius*radius-j*j)*sin(i)+ center.Getz()));
            }
        }
    }
    
    Sphere Rotate_X(int angle)
    {
        Sphere newsphere(center.Rotate_X(angle), radius);
        return newsphere;
    }
    Sphere Rotate_Y(int angle)
    {
        Sphere newsphere(center.Rotate_Y(angle), radius);
        return newsphere;
    }
    Sphere Rotate_Z(int angle)
    {
        Sphere newsphere(center.Rotate_Z(angle), radius);
        return newsphere;
    }
    Sphere Translate(int x, int y, int z)
    {
        Sphere newsphere(center.Translate(x, y, z), radius);
        return newsphere;
    }
    
};

#endif
