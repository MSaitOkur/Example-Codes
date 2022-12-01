class Myclass
{
public:
    Myclass &operator=(const Myclass &);
};

int main()
{
    Myclass x, y;

    x = y;
    // x.operator=(y);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class Myclass
{
public:
    Myclass &operator=(const Myclass &other)
    {
        ax = other.ax;
        ay = other.ay;
        az = other.az;
 
        return *this;
    }

private:
    int ax, ay, az;
};
int main()
{
    Myclass x, y, z;
 
    x = y;
    // x.operator=(y);
 
    x = y = z;
    // x.operator=(y.operator=(z));
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

