#include "3Vector.h"
#include <cmath>
#include <vector>

using namespace std;

class Pointnode
{
private:
    vector<Pointnode *> connects;
    int x;
    int y;
    int z;
    int numconnect;
public:
    Pointnode(int xc = 0, int yc = 0, int zc = 0);
    void printcoords();
    void Insert(Pointnode * p);
    int getx();
    int gety();
    int getz();
    int setx(int n);
    int sety(int n);
    int setz(int n);
    int getnumconnect();
    void setcoord(int xc, int yc, int zc);
    Pointnode * adjnode(int x);
};

Pointnode::Pointnode(int xc, int yc, int zc)
{
    x = xc;
    y = yc;
    z = zc;
    numconnect = 0;
}

void Pointnode::Insert(Pointnode * p)
{
    connects.push_back(p);
    numconnect++;
}

void Pointnode::setcoord(int xc, int yc, int zc)
{
    x = xc;
    y = yc;
    z = zc;
}

int Pointnode::getnumconnect()
{
    return numconnect;
}

Pointnode * Pointnode::adjnode(int n)
{
    return connects[n];
}

void Pointnode::printcoords()
{
    cout << x << "\t" << y << "\t" << z <<endl;
}

int Pointnode::getx()
{
    return x;
}
int Pointnode::gety()
{
    return y;
}
int Pointnode::getz()
{
    return z;
}


int Pointnode::setx(int n)
{
    x = n;
}
int Pointnode::sety(int n)
{
    y = n;
}
int Pointnode::setz(int n)
{
    z = n;
}

