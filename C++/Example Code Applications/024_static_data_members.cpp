#include <iostream>

class A
{
    int a, b;

public:
    static int x;
    static int y;
    static int z;
};
int main()
{
    std::cout << "sizeof(A) = " << sizeof(A) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class A
{
public:
    static int ms1;      // valid
    static int ms2 = 20; // invalid (static data member mustn't be initialized inside of class)
                         // static data member's definition must be in implementation file
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// A.hpp
struct A
{
    static int ms1;
    static int ms2;
};

// A.cpp
int A::ms2 = 20;        // valid
static int A::ms1 = 20; // invalid (static keyword just mustn't be on definition, but declaration)

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Neco
{
public:
    static int ms;

private:
    int ma, mb;
};

int Neco::ms = 24;

int main()
{
    std::cout << Neco::ms << "\n";

    Neco::ms = 999;

    std::cout << Neco::ms << "\n";

    ++Neco::ms;

    std::cout << Neco::ms << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* static data member will be created before main.
 * Therefore there is no need to class object to
 * to use static data member.
 */

#include <iostream>

class Neco
{
public:
    static int ms;

private:
    int ma, mb;
};

int foo()
{
    std::cout << "foo called\n";
    return 1;
}

int Neco::ms = foo();

int main()
{
    std::cout << "main started.\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Neco
{
public:
    static int x;
};

int main()
{
    Neco m;
    m.x;     // Valid but it's too risky
    Neco::x; // This is the better way to use static data member of a class
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Name lookup for the initializer expression of a static data member will be
 * first in class scope. If couldn't be found then compiler
 * will check the surrounding scopes.
 */

#include <iostream>

// Neco.h
class Neco
{
public:
    static int ival;
    static int sx;
};

// Neco.cpp
int ival = 450;
int Neco::ival = 999;
int Neco::sx = ival; // Same as (int Neco::sx = Neco::ival)

int main()
{
    std::cout << "Neco::sx = " << Neco::sx << "\n"; // 999
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a static data member is const and integral type, this type static data members
 * aka const integral static data members can be initialized in class. However this initialization
 * doesn't mean this is a definition. It still will be a declaration.
 *
 * If a static data member was declared with "constexpr' keyword, this data member
 * is implicitly inline.(C++11)
 */

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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Static data member cannot be initialized in MIL syntax because it was created before
 * the call of ctor. But it can be used to initialize non-static data members.
 */

class Data
{
public:
    Data() : mx{sx} {}           // invalid
    Data(int x) : mx{}, sx{x} {} // invalid

private:
    int mx;
    static int sx;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
/* const member functions can set the static data members. Because the static
 * data members aren't related with class objects.
 */

class A
{
public:
    void func() const
    {
        x = 20; // Gecerli
    }

private:
    static int x;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <vector>

class Myclass
{
public:
    static int mx;
    const static int cmx = 10; // it is still declaration, not definition
};
int main()
{
    std::vector<int> ivec;
    ivec.push_back(Myclass::cmx); // undefined reference to `Myclass::cmx'
    // There is no compile time error.
    // But when the link time, linker doesn't see the definition of cmx
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <vector>

class Myclass
{
public:
    static int mx;
    constexpr static int cmx = 10; // cmx is always constant expression.
                                   // constexpr static data members are implicitly inline
};
int main()
{
    std::vector<int> ivec;
    ivec.push_back(Myclass::cmx); // undefined reference to `Myclass::cmx'
    // There is no compile time and link time error.
}