//
//  3Vector.h
//  Matrix Visualization
//
//  Created by Laria R on 10/15/15.
//  Copyright (c) 2015 Laria R. All rights reserved.
//

#ifndef Matrix_Visualization__Vector_h
#define Matrix_Visualization__Vector_h

using namespace std;

class Vector_3 : public Matrix
{
private:
public:
    Vector_3(double v1 = 0, double v2 = 0, double v3 = 0);
    
    Vector_3 Rotate(double angle);
    
    Vector_3 Rotate_X(double angle);
    Vector_3 Rotate_Y(double angle);
    Vector_3 Rotate_Z(double angle);
    
    Vector_3 Translate(double x, double y, double z);
    Vector_3 Scale(double x, double y, double z);
    Vector_3 MatrixToVector(Matrix mat);
    
    Vector_3 CrossProduct(Vector_3 &v);
    
    Vector_3& operator =(Vector_3 &v);
    
    
    void Print();
    
    double Getx();
    double Gety();
    double Getz();
};

Vector_3::Vector_3(double v1, double v2, double v3)
{
    n = 1;
    u = 3;
    
    a = new double*[1];
    for(int i = 0; i < 3; i++)
        a[i] = new double[3];
    
    a[0][0] = v1;
    a[0][1] = v2;
    a[0][2] = v3;
}

Vector_3& Vector_3::operator= (Vector_3 &v)
{
    a[0][0] = v.Getx();
    a[0][1] = v.Gety();
    a[0][2] = v.Getz();
    
    return *this;
}

Vector_3 Vector_3::CrossProduct(Vector_3 &v)
{
    Vector_3 newvector(a[0][1]*v.Getz()-a[0][2]*v.Gety(),
                       a[0][2]*v.Getx()-a[0][0]*v.Getz(),
                       a[0][0]*v.Gety()-a[0][1]*v.Getx());
    return newvector;
}


Vector_3 Vector_3::MatrixToVector(Matrix mat)
{
    return*(new Vector_3(mat.a[0][0],mat.a[0][1],mat.a[0][2]));
}

Vector_3 Vector_3::Rotate(double angle)
{
    double radians = (PI / 180)*angle;
    double ** newmatrix;
    newmatrix = new double*[2];
    for(int i = 0; i < 2; i++)
    {
        newmatrix[i] = new double[2];
    }
    
    newmatrix[0][0] = cos(radians);
    newmatrix[1][0] = (-1)*sin(radians);
    newmatrix[0][1] = sin(radians);
    newmatrix[1][1] = cos(radians);
    
    Matrix tran_mat(2,2,newmatrix);
    
    return MatrixToVector(tran_mat.Multiply(* this));
}

Vector_3 Vector_3::Rotate_Z(double angle)
{
    double radians = (PI / 180)*angle;
    double ** newmatrix;
    newmatrix = new double*[3];
    for(int i = 0; i < 3; i++)
    {
        newmatrix[i] = new double[3];
    }
    
    newmatrix[0][0] = cos(radians);
    newmatrix[1][0] = (-1)*sin(radians);
    newmatrix[2][0] = 0;
    
    newmatrix[0][1] = sin(radians);
    newmatrix[1][1] = cos(radians);
    newmatrix[2][1] = 0;
    
    newmatrix[0][2] = 0;
    newmatrix[1][2] = 0;
    newmatrix[2][2] = 1;

    
    Matrix tran_mat(3,3,newmatrix);
    
    return MatrixToVector(tran_mat.Multiply(* this));
}

Vector_3 Vector_3::Rotate_X(double angle)
{
    double radians = (PI / 180)*angle;
    double ** newmatrix;
    newmatrix = new double*[3];
    for(int i = 0; i < 3; i++)
    {
        newmatrix[i] = new double[3];
    }
    
    newmatrix[0][0] = 1;
    newmatrix[1][0] = 0;
    newmatrix[2][0] = 0;
    
    newmatrix[0][1] = 0;
    newmatrix[1][1] = cos(radians);
    newmatrix[2][1] = (-1)*sin(radians);
    
    newmatrix[0][2] = 0;
    newmatrix[1][2] = sin(radians);
    newmatrix[2][2] = cos(radians);
    
    
    
    Matrix tran_mat(3,3,newmatrix);
    
    return MatrixToVector(tran_mat.Multiply(* this));
}

Vector_3 Vector_3::Rotate_Y(double angle)
{
    double radians = (PI / 180)*angle;
    double ** newmatrix;
    newmatrix = new double*[3];
    for(int i = 0; i < 3; i++)
    {
        newmatrix[i] = new double[3];
    }
    
    newmatrix[0][0] = cos(radians);
    newmatrix[1][0] = 0;
    newmatrix[2][0] = sin(radians);
    
    newmatrix[0][1] = 0;
    newmatrix[1][1] = 1;
    newmatrix[2][1] = 0;
    
    newmatrix[0][2] = (-1)*sin(radians);
    newmatrix[1][2] = 0;
    newmatrix[2][2] = cos(radians);
    
    
    
    Matrix tran_mat(3,3,newmatrix);
    
    return MatrixToVector(tran_mat.Multiply(* this));
}

Vector_3 Vector_3::Scale(double x, double y, double z)
{
    double ** newmatrix;
    newmatrix = new double*[4];
    for(int i = 0; i < 4; i++)
        newmatrix[i] = new double[4];
    
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
                newmatrix[i][j] = 1;
            else
                newmatrix[i][j] = 0;
        }
    
    newmatrix[0][0] = x;
    newmatrix[1][1] = y;
    newmatrix[2][2] = z;
    
    
    Matrix tran_mat(4,4,newmatrix);
    
    double ** newvector; 
    newvector = new double*[1];
    newvector[0] = new double[4];
    
    newvector[0][0] = a[0][0];
    newvector[0][1] = a[0][1];
    newvector[0][2] = a[0][2];
    newvector[0][3] = 1;
    
    
    Matrix coord_mat(1,4,newvector);
    return MatrixToVector(tran_mat.Multiply(coord_mat));
}

Vector_3 Vector_3::Translate(double x, double y, double z)
{
    double ** newmatrix;
    newmatrix = new double*[4];
    for(int i = 0; i < 4; i++)
        newmatrix[i] = new double[4];
    
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
                newmatrix[i][j] = 1;
            else
                newmatrix[i][j] = 0;
        }
    
    newmatrix[3][0] = x;
    newmatrix[3][1] = y;
    newmatrix[3][2] = z;
    
    double ** newvector; //creating 3d vector to represent coordinates being translated
    newvector = new double*[1];
    newvector[0] = new double[4];
    
    newvector[0][0] = a[0][0];
    newvector[0][1] = a[0][1];
    newvector[0][2] = a[0][2];
    newvector[0][3] = 1;
    
    Matrix tran_mat(4,4,newmatrix);
    Matrix coord_mat(1,4,newvector);
    
    return MatrixToVector(tran_mat.Multiply(coord_mat));
}

void Vector_3::Print()
{
    cout << endl << a[0][0] << endl << a[0][1] << endl << a[0][2] << endl;
}

double Vector_3::Getx()
{
    return a[0][0];
}

double Vector_3::Gety()
{
    return a[0][1];
}

double Vector_3::Getz()
{
    return a[0][2];
}


#endif
