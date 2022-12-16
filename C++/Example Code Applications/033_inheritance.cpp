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

#include <iostream>

class Base
{
public:
    void func(int)
    {
        std::cout << "Base::func(int) \n";
    }
};

class Der : public Base
{
public:
    void func()
    {
        std::cout << "Der::func() \n";
    }
    void func(int x) // Forwarding Function
    {
        Base::func(x);
    }
};

int main()
{
    Der mder;
    mder.func(12); // Forwarding Function Call
    mder.func();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* For the public inheritance, derived classes can reach the private part of base class.
 * Other codes than the derived class cannot reach protected part of base class.
 * Protected part of base classes is an interface for derived classes.
 */

#include <iostream>

class Base
{
protected:
    void func(int)
    {
        std::cout << "Base::func(int) \n";
    }
};

class Der : public Base
{
public:
    void foo(int x)
    {
        func(x); // Valid,  Base::func(int)
    }
};

int main()
{
    Der mder;
    mder.func(12); // Base::func(int), Access Error
}

// ====================== Inclass Using Declaration ============================
// ====================== Inclass Using Declaration ============================
// ====================== Inclass Using Declaration ============================

/* If a name which belongs to base class is declared with "using" keyword inside of derived class,
 * this name will be injected to derived class which means it can be used without '::' operator.
 * This name will also be visible for client codes of derived class.
 */

#include <iostream>

class Base
{
public:
    void func(int)
    {
        std::cout << "Base::func(int) \n";
    }
    void func(int, int)
    {
        std::cout << "Base::func(int, int ) \n";
    }
    void func(double, double)
    {
        std::cout << "Base::func(double, double) \n";
    }
};

class Der : public Base
{
public:
    using Base::func;
    void func(int)
    {
        std::cout << "Der::func(int) \n";
    }
    void func(double)
    {
        std::cout << "Der::func(double) \n";
    }
};
int main()
{
    Der myder;
    myder.func(13);       // Der::func(int), ("this" is Der*)
    myder.func(13, 23);   // Base::func(int,int)
    myder.func(1.3);      // Base::func(double)
    myder.func(1.3, 2.3); // Base::func(double, double)
}

//==================================

#include <iostream>
class Base
{
public:
    void func(int)
    {
        std::cout << "Base::func(int) \n";
    }

    void foo()
    {
        std::cout << "Base::foo()\n";
    }

    void bar()
    {
        std::cout << "Base::bar()\n";
    }
};

class Der : public Base
{
public:
    using Base::func;

protected:
    using Base::foo;

private:
    using Base::bar;
};

int main()
{
    Der myder;
    myder.func(13); // Base::func(int)
    myder.foo();    // Access error
    myder.bar();    // Access error
}

//==================================

#include <iostream>

class Base
{
protected:
    void func(int)
    {
        std::cout << "Base::func(int) \n";
    }

    void foo()
    {
        std::cout << "Base::foo()\n";
    }

    void bar()
    {
        std::cout << "Base::bar()\n";
    }
};

class Der : public Base
{
public:
    using Base::func;

protected:
    using Base::foo;

private:
    using Base::bar;
};

int main()
{
    Der myder;
    myder.func(13); // Base::func(int)
    myder.foo();    // Access error
    myder.bar();    // Access error
}

//==================================

#include <iostream>

class Base
{
    void func(int)
    {
        std::cout << "Base::func(int) \n";
    }

    void foo()
    {
        std::cout << "Base::foo()\n";
    }

    void bar()
    {
        std::cout << "Base::bar()\n";
    }
};

class Der : public Base
{
public:
    using Base::func; // Access error

protected:
    using Base::foo; // Access error

private:
    using Base::bar; // Access error
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a derived class has class type member object:
 *  - Firstly base class object will be created.
 *  - Then, member objects will be created.
 *  - The derived class object will be created lastly.
 *
 * When the life of this derived class object;
 *  - Firstly derived class object will be destructed.
 *  - Then, member objects will be destructed.
 *  - Lastly, the base class object will be destructed.
 */
#include <iostream>
class Base
{
public:
    Base() { std::cout << "Base() this: " << this << "\n"; }
    Base(int) { std::cout << "Base(int) this: " << this << "\n"; }
    Base(int, int) { std::cout << "Base(int, int) this: " << this << "\n"; }
    Base(double) { std::cout << "Base(double) this: " << this << "\n"; }
    ~Base() { std::cout << "~Base() this: " << this << "\n"; }
};

struct A : public Base
{
    ~A() { std::cout << "~A() this: " << this << "\n"; }
};

struct B : public Base
{
    B(int) : Base{12} {}
    ~B() { std::cout << "~B() this: " << this << "\n"; }
};

struct C : public Base
{
    C(int, int) : Base{44, 5} {}
    ~C() { std::cout << "~C() this: " << this << "\n"; }
};

struct D : public Base
{
    D(double) : Base{5.2} {}
    ~D() { std::cout << "~D() this: " << this << "\n"; }
};

int main()
{
    A ax;
    B bx(1);
    C cx(1, 2);
    D dx(1.);
}

//==========================================

#include <iostream>
class Member
{
public:
    Member() { std::cout << "Member() this: " << this << "\n"; }
    ~Member() { std::cout << "~Member() this: " << this << "\n"; }
};

class Base
{
public:
    Base() { std::cout << "Base() this: " << this << "\n"; }
    ~Base() { std::cout << "~Base() this: " << this << "\n"; }
};

class Der : public Base
{
public:
    Der() { std::cout << "Der() this : " << this << "\n"; }
    ~Der() { std::cout << "~Der() this : " << this << "\n"; }

private:
    Member mx;
};
int main()
{
    Der mder;
}

//=========================================

#include <iostream>
class Base
{
public:
    Base() { std::cout << "Base() this : " << this << "\n"; }
    Base(const Base &other) { std::cout << "Base(const Base& other) this : " << this << "\n"; }
};

class Der : public Base
{
public:
    Der() { std::cout << "Der() this : " << this << "\n"; }
    Der(const Der &other) { std::cout << "Der(const Der& other) this : " << this << "\n"; }
};
int main()
{
    Der dx;
    Der mder{dx}; // base of mder default constructed

    Der mder2{Der{}}; // Copy elision, base of mder2 default constructed
}

#include <iostream>
class Base
{
public:
    Base() { std::cout << "Base() this : " << this << "\n"; }
    Base(const Base &other) { std::cout << "Base(const Base& other) this : " << this << "\n"; }
};

class Der : public Base
{
public:
    Der() { std::cout << "Der() this : " << this << "\n"; }
    Der(const Der &other) : Base{other} // (!)
    {
        std::cout << "Der(const Der& other) this : " << this << "\n";
    }
};
int main()
{
    Der dx;
    Der mder{dx}; // Base of mder was copy constructed
}

//===========================================

#include <iostream>

class Base
{
public:
    Base() = default;
    Base &operator=(const Base &other)
    {
        std::cout << "Base operator= this : " << this << "\n";
        return *this;
    }
};

class Der : public Base
{
public:
    Der() = default;
    Der &operator=(const Der &other)
    {
        std::cout << "Der operator= this : " << this << "\n";
        return *this;
    }
};

int main()
{
    Der dx{}, dy{};
    dx = dy; // Base of dy were not assigned to Base of dx
}

//==================================

#include <iostream>

class Base
{
public:
    Base() = default;
    Base &operator=(const Base &other)
    {
        std::cout << "Base& operator=(const Base& other) this : " << this << "\n";
        return *this;
    }
    Base &operator=(Base &&other)
    {
        std::cout << "Base& operator=(Base&& other) this : " << this << "\n";
        return *this;
    }
};

class Der : public Base
{
public:
    Der() = default;
    Der &operator=(const Der &other)
    {
        Base::operator=(other);
        std::cout << "Der& operator=(const Der& other) this : " << this << "\n";
        return *this;
    }
    Der &operator=(Der &&other)
    {
        Base::operator=(std::move(other));
        std::cout << "Der& operator=(Der&& other) this : " << this << "\n";
        return *this;
    }
};

int main()
{
    Der dx{}, dy{};
    dx = dy;            // Copy
    dx = std::move(dy); // Move
}