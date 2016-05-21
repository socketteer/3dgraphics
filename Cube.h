#include "DynamicShape.h"

#include "3Vector.h"
#include <cmath>

using namespace std;

class Cube : public DynamicShape
{
private:
    int side;
public:
    Cube(int x, int y, int z, int sidelength = 100, int s = 8) : DynamicShape(x, y, z, s)
    {
        side = sidelength;
        for(int i = 0; i < size; i++)
        {
            points.push_back(new Pointnode);
        }
        Setcoordinates(x, y, z);
    }
    void Setcoordinates(int x, int y, int z)
    {
        points[0]->setcoord(x, y, z);
        points[1]->setcoord(x+side, y, z);
        points[2]->setcoord(x, y, z+side);
        points[3]->setcoord(x, y+side, z);
        points[4]->setcoord(x, y+side, z+side);
        points[5]->setcoord(x+side, y+side, z);
        points[6]->setcoord(x+side, y, z+side);
        points[7]->setcoord(x+side, y+side, z+side);
        
        points[0]->Insert(points[1]); //connecting appropriate vertices
        points[0]->Insert(points[2]);
        points[0]->Insert(points[3]);
        
        points[4]->Insert(points[2]);
        points[4]->Insert(points[3]);
        points[4]->Insert(points[7]);
        
        points[5]->Insert(points[3]);
        points[5]->Insert(points[7]);
        points[5]->Insert(points[1]);
        
        points[6]->Insert(points[7]);
        points[6]->Insert(points[1]);
        points[6]->Insert(points[2]);
        
    }

};
