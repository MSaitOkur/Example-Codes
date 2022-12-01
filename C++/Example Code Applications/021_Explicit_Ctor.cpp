#include <iostream>

class Counter
{
public:
    Counter() = default;
    explicit Counter(int ival) : mx{ival} {}

    void print() const
    {
        std::cout << "(" << mx << ")\n";
    }

private:
    int mx{};
};

int main()
{
    Counter c;
    int ival = 34;
    c = static_cast<Counter>(ival); // valid
    c = ival;                       // invalid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* explicit keyword must be in the declaration of function
 * which means must not be oustside class declaration.
 */

class A
{
public:
    A() = default;

    explicit A(int);
    explicit A(unsigned long);
    A(long double);
};

A::A(int) {}                    // Valid
explicit A::A(unsigned long) {} // Invalid
explicit A::A(long double) {}   // Invalid

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Explicit ctor's aren't added to function overload set. */

#include <iostream>
class A
{
public:
    explicit A(double val)
    {
        std::cout << "explicit A(double), val = " << val << '\n';
    }

    A(int val)
    {
        std::cout << "A(int), val = " << val << '\n';
    }
};

int main()
{
    A ax = 10.5; // Valid
}

//----------------------------

#include <iostream>
class Myclass
{
public:
    explicit Myclass(int);
};
int main()
{
    Myclass m1 = 10; // Copy init. gecersiz. Sebebi 10 icin gecici nesne olusturulmak istenecek,
    // bu gecici nesne icin cagrilacak olan ctor explicit oldugundan dolayi sentaks hatasidir.

    Myclass m2(10); // Direct init. Gecerli. Gecici nesne olusturulmaz.
    Myclass m3{10}; // Direct List init. (C++11) Gecerli. Gecici nesne olusturulmaz.
}