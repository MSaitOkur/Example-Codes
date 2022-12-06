// Myclass.h
class Myclass
{
public:
    static int func();
    static int foo();
    int bar();

    static int ifunc() // implicitly inline
    {
        return 5;
    }

    static int f() const; // Invalid (There is no this pointer in static member function)

private:
};

// Myclass.cpp

int Myclass::func()
{
    return 1;
}

static int Myclass::foo() // static keyword cannot be on definition
{
    return 2;
}

static int Myclass::bar() // invalid
{
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
/* Static member functions cannot use the non-static data members directly with
 * their name. They need a class object to use non-static data members.
 * But static member functions can use static data members directly with their names.
 */

// Myclass.h
class Myclass
{
public:
    static void func(Myclass m);

private:
    int mx, my;
    static int sx;
};

// Myclass.cpp
void Myclass::func(Myclass m1)
{
    Myclass m2;

    auto val = mx; // Invalid
    this;          // Invalid
    m1.mx = 2;     // Valid
    m2.my = 1;     // Valid
    sx = 10;       // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
/* Static member functions cannot use the non-static member functions directly with
 * their name. They need a class object to use non-static member functions.
 * But static member functions can use static member functions directly with their names.
 */

// Myclass.h
class Myclass
{
public:
    static void func(Myclass m);
    static void foo();
    void bar() const;
};

// Myclass.cpp
void Myclass::func(Myclass m1)
{
    Myclass m2;

    bar();    // invalid
    m1.bar(); // valid
    m2.bar(); // valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
// A.h
class A
{
public:
    static int foo()
    {
        return 1;
    }
    static int mx;
};

// A.cpp
int foo()
{
    return 2;
}

int A::mx = foo(); // 1

int main()
{
    std::cout << A::mx << "\n"; // 1
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
// A.h
class A
{
public:
    static int foo(int)
    {
        return 1;
    }
    static int mx;
};

// A.cpp
int foo()
{
    return 2;
}

int A::mx = foo(); // error (less argument sent)

int main()
{
    std::cout << A::mx << "\n"; // 1
}