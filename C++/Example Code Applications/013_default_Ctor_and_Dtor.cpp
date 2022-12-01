/* If compiler defaults a default. ctor, the def. ctor. will be nonstatic, public,
 * inline member function. And all the data members of class will bedefault initialized.
 */

class A
{
};
class B
{
};

class C
{
    A ax;
    B bx;
    int ival;
};

int main()
{
    C c;
    // Compiler wrote the def. ctor of the C and also ax,
    // bx and ival was default initialized.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* When the compiler defaults a special member function, if any error would occurs
 * compiler deletes the defaulted member function.
 */

class A
{
public:
    const int x; // cannot be default initialize
};

class B
{
public:
    int &r; // cannot be default initialize
};

class C
{
public:
    C(int);
};

class D
{
    D();

public:
};

class E
{
public:
    E() = delete;
};

class F
{
public:
    A a; // invalid, the default constructor of "A" cannot be referenced (it is a deleted function)
    B b; // invalid, the default constructor of "B" cannot be referenced (it is a deleted function)
    C c; // invalid, there is no def. ctor. of "C" class.
    D d; // invalid, the def. ctor. of "D" is private
    E e; // invalid, the def. ctor. of "E" was deleted
};

int main()
{
    F f; // Invalid, The def. ctor. of "F" is deleted.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class Data
{
public:
    Data()
    {
        std::cout << "Data default Ctor Called, this = " << this << "\n";
    }
    ~Data()
    {
        std::cout << "Data destructor Called, this = " << this << "\n";
    }
};
int main()
{
    Data mydata1;   // default ctor
    Data mydata2{}; // default ctor

    Data mydata3(); // default ctor cannot be called.
                    // "mydata3" is not an object. It is function declaration.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Data
{
public:
    Data()
    {
        std::cout << "Data default Ctor Called, this = " << this << "\n";
    }
    ~Data()
    {
        std::cout << "Data destructor Called, this = " << this << "\n";
    }
};

void func()
{
    static int cnt = 0;
    std::cout << "func islevine yapilan " << ++cnt << ". cagri\n";
    static Data mydata;
}

Data g_mydata;

int main()
{
    for (int i = 0; i < 10; ++i)
        func();
    std::cout << "main sona eriyor\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

