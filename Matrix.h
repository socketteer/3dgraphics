//This is just a bunch of matrix operations in case I need them in the future 

#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265359;

class Matrix {
private:
    bool square;
public:
    int n;
    int u;
    double ** a;
    Matrix(int m, int f, double **matrix);
    double mDeterminant(double **b, int size);
    Matrix Transpose();
    Matrix Cofactor();
    Matrix Invert();
    Matrix Scale(double val);
    Matrix Multiply(Matrix & mat);
    Matrix Add(Matrix & mat);
    Matrix Subtract(Matrix & mat);
    double **GetMatrix();
    int GetSize();
    int GetSizeY();
    void SetMatrixValues();
    void Print();
};

Matrix::Matrix(int m = 1, int f = 1, double **matrix = 0)
{
    n = m;
    u = f;
    
    if(n == u)
        square = 1;
    else
        square = 0;
    
    a = new double *[n];
    for (int i = 0; i < n; i++)
        a[i] = new double[u];
    if (matrix != 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < u; j++)
            {
                a[i][j] = matrix[i][j];
            }
    }
    
}


double ** Matrix::GetMatrix()
{
    return a;
}

int Matrix::GetSize()
{
    return n;
}

int Matrix::GetSizeY()
{
    return u;
}

void Matrix::SetMatrixValues()
{
    cout << "Please enter values in the matrix: " << endl;
    for (int j = 0; j < u; j++)
    {
        cout << "Row " << j+1 << ": ";
        for (int i = 0; i < n; i++)
            cin >> a[i][j];
    }
    cout << endl;
}

void Matrix::Print()
{
    for(int j = 0; j < u; j++)
    {
        for (int i = 0; i < n; i++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

Matrix Matrix::Transpose()
{
    double ** newmatrix;
    newmatrix = new double*[u];
    for(int i = 0; i < u; i++)
    {
        newmatrix[i] = new double[n]; 
    }
    for (int i = 0; i < u; i++)
        for (int j = 0; j < n; j++)
        {
            newmatrix[i][j] = a[j][i];
        }
    Matrix newm (u, n, newmatrix);
    return newm;
}

Matrix Matrix::Cofactor()
{
    if (square == 0)
    {
        cout << "Matrix needs to be square!" << endl;
        return * this;
    }
    double ** newmatrix;
    double ** comatrix;
    newmatrix = new double*[n-1];
    comatrix = new double*[n];
    int x, y;
    bool sign = 0;
    
    
    for(int i = 0; i < n-1; i++)
    {
        newmatrix[i] = new double[n-1];
    }
    for(int i = 0; i < n; i++)
    {
        comatrix[i] = new double[n];
    }
    
    
    for(int xcord = 0; xcord < n; xcord++)
    {
        for(int ycord = 0; ycord < n; ycord++)
        {
            x = 0;
            for(int i = 0; i < n-1; i++)
            {
                y = 0;
                if (i == xcord)
                    x = 1;
                if (i + x < n)
                {
                    for (int j = 0; j < n-1; j++)
                    {
                        if (j == ycord)
                            y = 1;
                        if (j + y < n)
                        {
                            newmatrix[i][j] = a[i+x][j+y];
                        }
                    }
                }
            }
            if (sign == 0)
            {
                comatrix[xcord][ycord] = mDeterminant(newmatrix, n-1);
                sign = 1;
            }
            else
            {
                comatrix[xcord][ycord] = (-1)*mDeterminant(newmatrix, n-1);
                sign = 0;
            }
        }
        
    }
    
    Matrix newm(n, n, comatrix);
    return newm;
}

Matrix Matrix::Scale(double val)
{
    
    double ** newmatrix;
    newmatrix = new double*[n];
    for(int i = 0; i < n; i++)
    {
        newmatrix[i] = new double[u];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < u; j++)
        {
            newmatrix[i][j] = (a[i][j] * val);
        }
    }
    Matrix newm(n, u, newmatrix);
    return newm;
}

Matrix Matrix::Multiply(Matrix & mat)
{
    if (n != mat.GetSizeY())
    {
        cout << "Columns in 1st matrix must equal rows in 2nd matrix." <<endl;
        return * this;
    }
    double ** newmatrix;
    int newcolumns = mat.GetSize();
    int newrows = u;
    newmatrix = new double*[newcolumns];
    for(int i = 0; i < newcolumns; i++)
    {
        newmatrix[i] = new double[newrows];
    }
    for(int ypos = 0; ypos < newrows; ypos++)
    {
        for(int xpos = 0; xpos < newcolumns; xpos++)
        {
            for(int i = 0; i < n; i++)
            {
                newmatrix[xpos][ypos] += (a[i][ypos]*(mat.GetMatrix())[xpos][i]);
            }
            
        }
    }
    Matrix newm(newcolumns, newrows, newmatrix);
    return newm;
}

Matrix Matrix::Add(Matrix & mat)
{
    if (mat.GetSize() != n || mat.GetSizeY() != u)
    {
        cout << "Matrices must be of the same size." <<endl;
        return mat;
    }
    double ** newmatrix;
    newmatrix = new double*[n];
    for(int i = 0; i < n; i++)
    {
        newmatrix[i] = new double[u];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < u; j++)
        {
            newmatrix[i][j] = a[i][j] + mat.GetMatrix()[i][j];
        }
    }
    Matrix newm(n, u, newmatrix);
    return newm;
}

Matrix Matrix::Subtract(Matrix & mat)
{
    if (mat.GetSize() != n || mat.GetSizeY() != u)
    {
        cout << "Matrices must be of the same size." <<endl;
        return mat;
    }
    double ** newmatrix;
    newmatrix = new double*[n];
    for(int i = 0; i < n; i++)
    {
        newmatrix[i] = new double[u];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < u; j++)
        {
            newmatrix[i][j] = a[i][j] - mat.GetMatrix()[i][j];
        }
    }
    Matrix newm(n, u, newmatrix);
    return newm;
}



Matrix Matrix::Invert()
{
    if (mDeterminant(a, n) == 0)
        cout << "Matrix not invertible; determinant is 0!" << endl;
    if (square == 0)
    {
        cout << "Matrix needs to be square!" << endl;
        return * this;
    }
    if (n == 2)
    {
        double ** newmatrix;
        newmatrix = new double*[2];
        for(int i = 0; i < 2; i++)
            newmatrix[i] = new double[2];
        newmatrix[0][0] = a[1][1];
        newmatrix[1][1] = a[0][0];
        newmatrix[1][0] = (-1)*a[1][0];
        newmatrix[0][1] = (-1)*a[0][1];
        Matrix newm(2,2,newmatrix);
        return newm.Scale(1 / mDeterminant(a, n));
    }
    else if (n < 2)
    {
        cout << "Matrix must be at least 2x2!" << endl;
        return * this;
    }
    return Cofactor().Transpose().Scale(1 / mDeterminant(a, n));
}


double Matrix::mDeterminant(double **b, int size)
{
    if (square == 0)
    {
        cout << "Matrix needs to be square!" << endl;
        return NULL;
    }
    
    if(size == 2)
    {
        return ((b[0][0])*(b[1][1])-(b[0][1])*(b[1][0]));
    }
    else if (size < 2)
        cout << "Matrix must be at least 2x2!" << endl;
    
    double ** newmatrix;
    newmatrix = new double*[size-1];
    int x = 0;
    double det_val = 0;
    
    for(int i = 0; i < size-1; i++)
    {
        newmatrix[i] = new double[size-1];
    }
    
    for(int first = 0; first < size; first++)
    {
        x = 0;
        for(int i = 0; i < size-1; i++)
        {
            if (i == first)
                x = 1;
            if (i + x < size)
            {
                for (int j = 0; j < size-1; j++)
                {
                    newmatrix[i][j] = b[i+x][j+1];
                }
            }
        }
        if (first % 2 == 0)
            det_val += b[first][0]*mDeterminant(newmatrix, size-1); //recursively +/- determinant of sub matrix
        else
            det_val -= b[first][0]*mDeterminant(newmatrix, size-1);
    }
    
    return det_val;
}

