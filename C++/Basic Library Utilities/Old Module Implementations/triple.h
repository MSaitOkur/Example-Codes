#include <iostream>
#include <sstream>

class Triple
{
public:
    Triple()
    {
        // std::cout << *this << " Triple()\n";
    }
    Triple(int x, int y, int z) : mx{x}, my{y}, mz{z}
    {
        // std::cout << *this << " Triple(int, int, int)\n";
    }
    ~Triple()
    {
        // std::cout << *this << " ~Triple()\n";
    }

    void set(int a, int b, int c)
    {
        mx = a;
        my = b;
        mz = c;
    }
    friend std::ostream &operator<<(std::ostream &os, const Triple &t)
    {
        std::ostringstream ostr;

        ostr << "(" << t.mx << ", " << t.my << ", " << t.mz << ")";

        os << ostr.str();

        return os;
    }

private:
    int mx{}, my{}, mz{};
};
