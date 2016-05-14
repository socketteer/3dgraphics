#include"bitmap_image.h"
#include "3Vector.h"


class Shape
{
protected:
    vector<Vector_3> arr;
    int n;
public:
    Shape(vector<Vector_3> points, int size);
    Shape Rotate_X(double angle);
    Shape Rotate_Y(double angle);
    Shape Rotate_Z(double angle);
    Shape Scale(double x, double y, double z);
    Shape Translate(double x, double y, double z);
    vector<Vector_3> GetPoints();
    void MapToSpace(Space newspace);
    void Print();
};

Shape::Shape(vector<Vector_3> points, int size)
{
    n = size;
    for (int i = 0; i < n; i++)
    {
        arr.push_back(points[i]);
    }
}

Shape Shape::Rotate_X(double angle)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Rotate_X(angle));
    }
    Shape newshape(new_arr, n);
    return newshape;
}

Shape Shape::Rotate_Y(double angle)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Rotate_Y(angle));
    }
    Shape newshape(new_arr, n);
    return newshape;
}

Shape Shape::Rotate_Z(double angle)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Rotate_Z(angle));
    }
    Shape newshape(new_arr, n);
    return newshape;
}

Shape Shape::Scale(double x, double y, double z)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Scale(x, y, z));
    }
    Shape newshape(new_arr, n);
    return newshape;
}

Shape Shape::Translate(double x, double y, double z)
{
    vector<Vector_3> new_arr;
    for (int i = 0; i < n; i++)
    {
        new_arr.push_back(arr[i].Translate(x, y, z));
    }
    Shape newshape(new_arr, n);
    return newshape;
}


void Shape::MapToSpace(Space newspace)
{
    for (int i = 0; i < n; i++)
    {
        newspace.MapTo(arr[i]);
    }
}

vector<Vector_3> Shape::GetPoints()
{
    return arr;
}

void Shape::Print()
{
    for (int i = 0; i < n; i++)
    {
        arr[i].Print();
    }
}

