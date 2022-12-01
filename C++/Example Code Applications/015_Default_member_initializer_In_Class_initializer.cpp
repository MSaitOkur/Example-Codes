#include <iostream>
class Myclass
{
public:
    void print() const
    {
        std::cout << "x = " << x << "\n";
    }

private:
    int x;
};
int main()
{
    Myclass mx;

    mx.print(); // x has garbage value
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Myclass
{
public:
    void print() const
    {
        std::cout << "x = " << x << "\n";
    }

private:
    int x = 10;
};

int main()
{
    Myclass mx;
    mx.print(); // 10
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Myclass
{
public:
private:
    int x = 10; // valid
    int y{20};  // valid
    int z(10);  // invalid
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a data member both initialized with inclass initializer and MIL,
 * MIL syntax has higher priority.
 */

#include <iostream>
class Myclass
{
private:
    int x = 10;

public:
    Myclass() {}
    Myclass(int val) : x{val} {}

    void print() const
    {
        std::cout << "x = " << x << "\n";
    }
};
int main()
{
    Myclass mx; // in class initializer
    mx.print(); // 10

    Myclass my{214}; // member initializer list
    my.print();      // 214
}