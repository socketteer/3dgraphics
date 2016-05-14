using namespace std;

class Lightsource
{
private:
    double i, j, k;
public:
    Lightsource(double u1 = 0,double u2 = 0,double u3 = 0){i=u1;j=u2;k=u3;}
    double get_i()
    {return i;}
    double get_j()
    {return j;}
    double get_k()
    {return k;}
};

