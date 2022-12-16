//=======================================
class Base
{
};
class Der : public Base
{
}; // Public Inheritance
//=======================================
class Base
{
};
class Der : private Base
{
}; // Private Inheritance
//=======================================
class Base
{
};
class Der : protected Base
{
}; // Protected Inheritance
//=======================================
class Base
{
};
class Der : Base
{
}; // Private Inheritance
//=======================================
class Base
{
};
struct Der : Base
{
}; // Public Inheritance

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Car
{
};

class Audi : public Car
{
};

int main()
{
    Car mycar;
    Audi myaudi;

    Car *cptr = &myaudi; // Legal
    Car &cref = myaudi;  // legal
    Audi &aref = mycar;  // Invalid. Static_cast kullanılması gerek
    mycar = myaudi;      // legal (but not true, object slicing is shouldn't had done)
    myaudi = mycar;
}

//======================== Name Lookup in Public Inheritance ==============================
//======================== Name Lookup in Public Inheritance ==============================
//======================== Name Lookup in Public Inheritance ==============================

/* The derived class objects, can reach the names that declared in
 * public part of base class.
 */

class Base
{
    void private_func();
    int private_member;

public:
    void func();
    void foo();
};

class Der : public Base
{
public:
    void f()
    {
        private_func(); // invalid
        func();         // valid
    }
};
int main()
{
    Der myder;
    myder.foo();  // Valid
    myder.func(); // Valid
    myder.f();    // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Member
{
    int x, y;
};

class Base
{
    int x, y;
};

class A : public Base
{
    Member mx;
    double dval;
};

int main()
{
    std::cout << "sizeof(Member) = " << sizeof(Member) << '\n';
    std::cout << "sizeof(A) = " << sizeof(A) << '\n';
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* - The first control always will be name lookup.
 *
 * - Base class and derived class have different scopes which means the member
 *   functions of base class and derived class, are not overloaded.
 *
 * - When a name was called with derived class object or derived class name and '::' operator:
 *
 *      -- The name will be looked up in derived class scope.
 *          --- If it was found, name lookup will finish.
 *          --- If it wasn't found, the name will be looked up in base class scope.
 *          --- If it wasn't found, there will be error.
 *
 *      -- If the name was found, there will be syntax control.
 *          --- If there is an error, there will be syntax error.
 *
 *      -- If there is no syntax error, there will be access control.
 *         --- If the name is unreachable, there will be access error.
 */

#include <iostream>

struct Base
{
    void func();
    void bar(int);
    void f();
    void foo();

    static void sfoo();
};

class Der : public Base
{
public:
    void func();
    void bar();
    static void sfoo();

private:
    void foo();
};

int main()
{
    Der myder;

    myder.func();       // Der::func
    myder.f();          // Base::f
    myder.foo();        // Der, Access Error
    myder.bar(20);      // Der, Syntax Error
    myder.Der::func();  // Der::func
    myder.Base::func(); // Base::func

    Der::sfoo();        // Der::sfoo
    Der::Base::sfoo();  // Base::sfoo
    myder.sfoo();       // Der::sfoo  (!)
    myder.Base::sfoo(); // Base::sfoo (!)
}

//=======================================

#include <iostream>

struct Base
{
    void func(int);
};

void func();

class Der : public Base
{
public:
    void func()
    {
        func(12);                           // Invalid Der::func, Syntax error
        Base::func(123);                    // Valid
        ::func();                           // Valid
        static_cast<Base *>(this)->func(4); // Base::func
    }
};

//=======================================



