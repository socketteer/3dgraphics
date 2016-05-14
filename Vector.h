#include "Matrix.h"

using namespace std;

class Vector : public Matrix
{
private:
public:
    Vector(double v1, double v2);
    Vector Rotate(double angle);
    Vector Translate(double x, double y);
    Vector Scale(double x, double y);
    Vector MatrixToVector(Matrix mat);
    double Getx();
    double Gety();
};

Vector::Vector(double v1, double v2)
{
    n = 1;
    u = 2;
    
    a = new double*[1];
    for(int i = 0; i < 1; i++)
        a[i] = new double[2];
    
    a[0][0] = v1;
    a[0][1] = v2;
}

Vector Vector::MatrixToVector(Matrix mat)
{
    return*(new Vector(mat.a[0][0],mat.a[0][1]));
}

Vector Vector::Rotate(double angle)
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

Vector Vector::Scale(double x, double y)
{
    double ** newmatrix;
    newmatrix = new double*[2];
    for(int i = 0; i < 2; i++)
    {
        newmatrix[i] = new double[2];
    }
    
    newmatrix[0][0] = x;
    newmatrix[1][0] = 0;
    newmatrix[0][1] = 0;
    newmatrix[1][1] = y;
    
    Matrix tran_mat(2,2,newmatrix);
    
    return MatrixToVector(tran_mat.Multiply(* this));
}

Vector Vector::Translate(double x, double y)
{
    double ** newmatrix;
    newmatrix = new double*[3];
    for(int i = 0; i < 3; i++)
        newmatrix[i] = new double[3];
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
                newmatrix[i][j] = 1;
            else
                newmatrix[i][j] = 0;
        }
    
    newmatrix[2][0] = x;
    newmatrix[2][1] = y;
    
    double ** newvector; //creating 3d vector to represent coordinates being translated
    newvector = new double*[1];
    newvector[0] = new double[3];

    newvector[0][0] = a[0][0];
    newvector[0][1] = a[0][1];
    newvector[0][2] = 1;
    
    Matrix tran_mat(3,3,newmatrix);
    Matrix coord_mat(1,3,newvector);
    
    return MatrixToVector(tran_mat.Multiply(coord_mat));
}


double Vector::Getx()
{
    return a[0][0];
}

double Vector::Gety()
{
    return a[0][1];
}
