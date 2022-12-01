/* There is no implicit conversion from primitive types to class types.
 *
 * Some of ctors of classes which has one parameter
 * are used to be as type cast operator function. Compiler creates a temporary object
 * for this type conversion with using this conversion ctor. Then the assignment operator
 * function will be called for this temporary object.
 */

#include <iostream>

class Myclass
{
public:
    Myclass() = default;
    Myclass(int);
};

int main()
{
    Myclass mx;
    mx = 34; // Valid (mx = Myclass{34});
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Myclass
{
public:
    Myclass(int x);
};

void f1(Myclass);
void f2(const Myclass &);
void f3(Myclass &);

Myclass foo()
{
    return 1; // Valid
}

int main()
{
    Myclass m{12};
    int ival = 123;

    m = ival; // m.operator=(Myclass{ival});

    f1(ival); // Valid
    f2(43);   // Valid
    f3(90);   // Invalid (Parameter of f3 needs Lvalue Reference, but argument is Rvalue Reference)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Myclass
{
public:
    Myclass();
    Myclass(int x);
};

int main()
{
    Myclass mx;
    double dval{2.3};
    bool flag{};

    mx = dval; // Valid
    mx = flag; // Valid
}