// ===================================================

int main()
{
    // int &ri1; // Invalid (Init. of LValue Ref. Mandatory)

    int ival = 10;
    // int &ri2 = 20; // Invalid (Initializer must be Lvalue Expr.)
    int &ri3 = ival; // Valid

    double dval = 2.5;
    // int &ri4 = dval; // Ivalid (Initializer's type must be exact match)
}

// ===================================================

#include <iostream>

int main()
{
    int x = 10;
    int y = 20;

    int &r = x; // r is reference to x as long as its life lasts.
    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << '\n';
    std::cout << "r = " << r << "\n";

    r = y; // y's value was copied to x. r is still reference to x not to y
    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << '\n';
    std::cout << "r = " << r << "\n";
}

// ===================================================

#include <iostream>

int main()
{
    int x = 10;
    int y = 34;

    int *ptr = &x;    // ptr points to x's address
    int *&rptr = ptr; // rptr is reference to ptr

    rptr = &y; // now ptr points to y
    ++*ptr;

    std::cout << "y = " << y << "\n";
}

// ===================================================

#include <iostream>

int main()
{
    int a[5]{0, 1, 2, 3, 4};

    int *ptr = a;    // First elment's address
    int(*p)[5] = &a; // Array's address

    for (int i = 0; i < 5; ++i)
        std::cout << (*p)[i] << " ";
}

// ===================================================

#include <iostream>

int main()
{
    int a[5]{0, 1, 2, 3, 4};

    int(&ra)[5] = a; // ra reference to array a

    for (int i = 0; i < 5; ++i)
        std::cout << ra[i] << " ";
}
// ===================================================

#include <iostream>

int main()
{
    int a[]{10, 20, 30, 40};

    int *p{a};  // p points first element's address
    int *&r{p}; // r is reference to array a

    ++r;  // p points to second element of array a
    ++*r; // second element of a increased by 1

    for (auto i : a) // range based for loop
        std::cout << i << " ";
}
// ===================================================

int main()
{
    int a[]{1, 2, 4};

    int *&r14 = a; // Invalid. There is no array to pointer conv. because of '&' declarator
    int *r14 = a;  // Valid. There is array to pointer conversion.

    int *ptr = &a[0];
    int *&r14 = ptr; // Valid.
}

// ===================================================

#include <iostream>

struct Data
{
    int a[20];
};

int main()
{
    Data mydata;
    Data &rd{mydata};
    Data *pd{&mydata};

    std::cout << sizeof(Data) << "\n";   // sizeof(int) * 20
    std::cout << sizeof(mydata) << "\n"; // sizeof(int) * 20
    std::cout << sizeof(rd) << "\n";     // sizeof(int) * 20
    std::cout << sizeof(pd) << "\n";     // sizeof(Data*)
}
// ===================================================

#include <iostream>

void func(int &a)
{
    a = 123;
}

int main()
{
    int z = 4;
    func(z);
    std::cout << "z = " << z << '\n'; // 123
}

// ===================================================

#include <iostream>

void Swap(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main()
{
    int x = 10;
    int y = 20;

    Swap(&x, &y);

    std::cout << "x = " << x << " y = " << y << "\n ";
}

// ===================================================

#include <iostream>

void Swap(int &p1, int &p2)
{
    int temp = p1;
    p1 = p2;
    p2 = temp;
}

int main()
{
    int x = 10;
    int y = 20;

    Swap(x, y);

    std::cout << "x = " << x << " y = " << y << "\n ";
}

// ===================================================

int &func();

int main()
{
    int &rf = func();
}

// ===================================================

int a = 20;
int &const x = a; // redundant, same as {int &x = a;}

// ===================================================

#include <iostream>

int main()
{
    int x{};
    int y{};

    int &r{x};
    const int &cr{y};

    r = y; // Valid
    // cr = x; // Invalid
}

// ===================================================

const int &r = 10;
/*
 * Same as:
 * const int temp{10};
 * const int &r = temp;
 */

// ===================================================

void func(const int &);
void foo(int &);

int main()
{
    int x = 10;

    func(x);  // Valid
    func(10); // Valid
    foo(x);   // Valid
    // foo(10);  // Invalid
}

// ===================================================

#include <iostream>

void set(int &r1, const int &r2)
{
    r1 = r2;
}

int main()
{
    int x = 125;

    std::cout << "x = " << x << '\n';

    set(x, 25);

    std::cout << "x = " << x << '\n';
}

//=========================================================

int main()
{
    int x = 123;
    const int y = 35;

    int &r1{x};       // Valid
    const int &r2{y}; // Valid
    const int &r3{x}; // Valid
    // int &r4{y};       // Invalid (y must not be const)
}

//=========================================================

int main()
{
    int x = 1214;

    int &r1 = x;   // Valid
    int &&r2 = 10; // Valid
    // int &&r3 = x;  // Invalid (rvalue ref. must have rvalue expr. initializer)
}

// ============

int &func();

int main()
{
    int &r = func(); // Valid
    // int &&r2 = func(); // Invalid
}

// ============

int f();

int main()
{
    // int &r1 = f();  // Invalid
    int &&r2 = f(); // Valid
}

//=========================================================
//=========================================================
//=========================================================
//=========================================================
//=========================================================
//=========================================================
//=========================================================