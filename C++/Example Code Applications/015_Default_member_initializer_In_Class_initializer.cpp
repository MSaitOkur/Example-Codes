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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

struct A
{
};

struct B;

struct C
{
    static int ival1;                // Valid
    static int ival2 = 20;           // Invalid (ISO C++ forbids in-class initialization of non-const static member)
    static const int ival3;          // Valid
    static const int ival4 = 10;     // Valid
    constexpr int ival5 = 10;        // Invalid (non-static data member cannot be declared with ‘constexpr’ keyword)
    constexpr static int ival6 = 10; // Valid (constexpr static data members are implicitly inline)

    static double dval1;                 // Valid
    static double dval2 = 20.234;        // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    static const double dval3;           // Valid
    static const double dval4 = 1.3;     // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    constexpr double dval5 = 1.3;        // Invalid (non-static data member cannot be declared with ‘constexpr’ keyword)
    constexpr static double dval5 = 1.3; // Valid

    static A aval1;             // Valid
    static A aval2{};           // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    static const A aval3;       // Valid
    static const A aval4{};     // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    constexpr A aval5;          // Invalid (non-static data member cannot be declared with ‘constexpr’ keyword)
    constexpr static A aval6{}; // Valid

    static B *bval1;             // Valid
    static B *bval2{};           // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    static const B *bval3;       // Valid
    static const B *bval4{};     // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    constexpr B *bval5;          // Invalid (non-static data member cannot be declared with ‘constexpr’ keyword)
    constexpr static B *bval6{}; // Valid

    static C *pcval1;             // Valid
    static C *pcval2{};           // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    static const C *pcval3;       // Valid
    static const C *pcval4{};     // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    constexpr C *pcval5;          // Invalid (non-static data member cannot be declared with ‘constexpr’ keyword)
    constexpr static C *pcval6{}; // Valid

    static C cval1;             // Valid
    static C cval2{};           // Invalid (incomplete type static data member's inclass initialization is not allowed)
    static const C cval3;       // Valid
    static const C cval4{};     // Invalid (incomplete type static data member's inclass initialization is not allowed)
    constexpr C cval5;          // Invalid (non-static data member cannot be declared with ‘constexpr’ keyword)
    constexpr static C cval6{}; // Invalid (Incomplete type initialization)

    int a1[5]{1, 2, 3, 4, 5};                  // Valid
    const int a2[5]{1, 2, 3, 4, 5};            // Valid
    static int a3[5]{1, 2, 3, 4, 5};           // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    static const int a4[5]{1, 2, 3, 4, 5};     // Invalid (non-integral type static data member cannot be initialized without "constexpr" keyword)
    constexpr static int a5[5]{1, 2, 3, 4, 5}; // Valid

    int b1[]{1, 2, 3, 4, 5};                  // Invalid (an initializer cannot be specified for a flexible array member)
    const int b2[]{1, 2, 3, 4, 5};            // Invalid (an initializer cannot be specified for a flexible array member)
    static int b3[]{1, 2, 3, 4, 5};           // Invalid (an initializer cannot be specified for a flexible array member)
    static const int b4[]{1, 2, 3, 4, 5};     // Invalid (an initializer cannot be specified for a flexible array member)
    constexpr static int b5[]{1, 2, 3, 4, 5}; // Valid
};
