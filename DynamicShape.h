#include "3Vector.h"
#include <cmath>
#include "Pointnode.h"
#include "Space.h"
#include <iostream>

using namespace std;

class DynamicShape
{
public:
    DynamicShape(int x = 0, int y = 0, int z = 0, int s = 1);
    void drawline(Pointnode p1, Pointnode p2, Space &newspace, int red = 255, int green = 255, int blue = 255);
    void connectlines(Space &newspace);
    void movevertex(int x, int y, int z, int v);
protected:
    vector<Pointnode *> points;
    int size;


};

DynamicShape::DynamicShape(int x, int y, int z, int s)
{
    size = s;
    for(int i = 0; i < size; i++)
    {
        points.push_back(new Pointnode);
    }
    
}

void DynamicShape::movevertex(int x, int y, int z, int v)
{
    points[v]->setx(points[v]->getx()+x);
    points[v]->sety(points[v]->gety()+y);
    points[v]->setz(points[v]->getz()+z);
    
}

void DynamicShape::connectlines(Space &newspace)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < (points[i]->getnumconnect()); j++)
        {
            drawline(*points[i], *points[i]->adjnode(j), newspace);
            
        }
    }
}

void DynamicShape::drawline(Pointnode p1, Pointnode p2, Space &newspace, int red, int green, int blue)
{
    int x1 = p1.getx();
    int y1 = p1.gety();
    int z1 = p1.getz();
    int x2 = p2.getx();
    int y2 = p2.gety();
    int z2 = p2.getz();
    
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

#endif
