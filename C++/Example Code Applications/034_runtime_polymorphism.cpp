/* If a class has at least one virtual function, such these classes are called as polymorphic class.
 * If a class has at least one pure virtual function, such these classes are called as abstract class.
 * Abstract classes are defaultly polymorphic classes.
 */

class airplane1
{
public:
    void takeoff();
};

// airplane2 is polymorphic class
class airplane2
{
public:
    void takeoff();
    virtual void fly(); // virtual function
};

class airplane3
{
public:
    void takeoff();
    virtual void fly();      // virtual function
    virtual void land() = 0; // pure virtual function, " = 0 " means land has no implementation
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Runtime polymorphism is not a compile time tool. As seems from the name, runtime polymorhism
 * is a tool for runtime of program.
 */

#include <iostream>

class Base
{
public:
    virtual void func()
    {
        std::cout << "Base::func()\n";
    }
};

class Der : public Base
{
public:
    void func()
    {
        std::cout << "Der::func()\n";
    }
};

class Nec : public Base
{
public:
    void func()
    {
        std::cout << "Nec::func()\n";
    }
};

int main()
{
    Der myder;
    Nec mynec;

    Base *baseptr{&myder};
    baseptr->func(); // Der::func();

    baseptr = &mynec;
    baseptr->func(); // Nec::func();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Base
{
public:
    virtual void bar(int);
    void foo();
    virtual void func();
};

class Der : public Base
{
public:
    void bar(int); // Valid (override)
    int foo();     // Valid (Function Overloading)
    int func();    // error (For overriding, return type and function sign must be same)
};
//===========================
class Base
{
public:
    virtual void bar(int);
    virtual int f();
    virtual void func();
};
class Der : public Base
{
public:
    void bar(int); // Valid, override
    int f(int);    // Valid, neither override nor overload
    int func();    // error (For overriding, return type and function sign must be same)
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class Base
{
public:
    virtual void vfunc()
    {
        std::cout << "Base::vfunc()\n";
    }
};
class Der : public Base
{
public:
    void vfunc()
    {
        std::cout << "Der::vfunc()\n";
    }
};
int main()
{
    Der d;
    Base *b = &d;
    b->vfunc();
}

//=================================

#include <iostream>

class Base
{
public:
    virtual void vfunc()
    {
        std::cout << "Base::vfunc()\n";
    }
};

class Der : public Base
{
public:
    void vfunc()
    {
        std::cout << "Der::vfunc()\n";
    }
};

int main()
{
    Der d;
    Base &b = d;
    b.vfunc();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Base
{
public:
    virtual void vfunc()
    {
        std::cout << "Base::vfunc()\n";
    }
};

class Der : public Base
{
public:
    void vfunc()
    {
        std::cout << "Der::vfunc()\n";
    }
};

int main()
{
    Der d;
    //.....
    //.....
    Base b = d; // object slicing
    b.vfunc();  // There is no virtual dispatch
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include "Car.h"

void car_game(Car *carptr)
{
    carptr->start();
    carptr->run();
    carptr->stop();
}

int main()
{
    for (;;)
    {
        Car *ptr = create_random_car();
        car_game(ptr);
        static_cast<void>(std::getchar());
    }
}

//=======================================

#include <iostream>
#include "Car.h"

void car_game(Car &car)
{
    car.start();
    car.run();
    car.stop();
}

int main()
{
    for (;;)
    {
        Car *ptr = create_random_car();
        car_game(*ptr);
        static_cast<void>(std::getchar());
    }
}

//=======================================

#include <iostream>
#include "Car.h"

void car_game(Car car) // Abstract classes' objects cannot be created
{
    car.start();
    car.run();
    car.stop();
}

int main()
{
    for (;;)
    {
        Car *ptr = create_random_car();
        car_game(*ptr); // To dereference of absract classes's objects are error
        static_cast<void>(std::getchar());
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Base
{
public:
    virtual void func(int);
    void foo(int);
};
class Der : public Base
{
public:
    void func(long); // not override, no diagnostic
    void foo(int);   // not override, no diagnostic
};

//=======================================

class Base
{
public:
    virtual void func(int);
    void foo(int);
};
class Der : public Base
{
public:
    void func(long) override; // error (not override)
    void foo(int) override;   // error (not override)
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class A
{
public:
    virtual void func(int) = 0;
};
int main()
{
    A a; // cannot instantiate abstract class
}

//=======================================

class Base // Base is an abstract class
{
public:
    virtual void func(int) = 0;
};

class Der : public Base
{
public:
    void func(int) override {}
};

int main()
{
    Der d; // Der is not abstract class (concrete)
}

//=======================================

class Base
{
public:
    virtual void func(int) = 0;
    virtual void foo() = 0;
};

class Der : public Base // Der is an abstract class. foo is not overrided
{
public:
    void func(int) override {}
};

int main()
{
    Der d; // Invalid. If this code line is wanted to be valid,
           // all of the pure virtual functions must be overrided.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

struct Base
{
    virtual void func()
    {
        std::cout << "Base::func();\n";
    }
};

struct Der : Base
{
    void func() override
    {
        std::cout << "Der::func();\n";
    }
};

int main()
{
    Base b1;
    b1.func(); // no virtual dispatch

    Der d1;
    Base b2 = d1; // Object slicing
    b2.func();    // no virtual dispatch

    Der d2;
    Base *bptr = &d2;
    bptr->func(); // virtual dispatch

    Der d3;
    Base &bref = d3;
    bref.func(); // Virtual Dispatch

    Base b3;
    Der d4 = b3;                          // Error
    Der *dptr1 = &b3;                     // Error
    Der *dptr2 = static_cast<Der *>(&b3); // Valid
    Der &dref1 = b3;                      // Error
    Der &dptr2 = static_cast<Der &>(b3);  // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class ICar
{
public:
    virtual void start() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;

    void maintain()
    {
        this->start();
        this->run();
        this->stop();
    }
};

class Bmw : public ICar
{
public:
    void start() override
    {
        std::cout << "Bmw has started\n";
    }
    void run() override
    {
        std::cout << "Bmw is running\n";
    }
    void stop() override
    {
        std::cout << "Bmw has just stopped\n";
    }
};

int main()
{
    Bmw b;
    ICar *ptr = &b;
    ptr->maintain(); // virtual dispatch
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class Base
{
public:
    Base()
    {
        vfunc(); // no virtual dispatch
                 // Because at this point, there is no derived class object
                 // it hasn't been born yet
    }

    virtual void vfunc()
    {
        std::cout << "Base::vfunc()\n";
    }

    void foo()
    {
        vfunc(); // virtual dispatch
    }

    ~Base()
    {
        vfunc(); // no virtual dispatch
                 // Because at this point, the derived class object is dead, destructed
    }
};

class Der : public Base
{
public:
    void vfunc() override
    {
        std::cout << "Der::vfunc()\n";
    }
};

int main()
{
    Der d; // Base::vfunc
    Base *bptr = &d;
    d.foo();       // Der::vfunc
    bptr->vfunc(); // Der::vfunc
}