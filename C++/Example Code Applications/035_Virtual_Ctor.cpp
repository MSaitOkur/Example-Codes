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
    void func() override
    {
        std::cout << "Der::func()\n";
    }
};

void gfoo(Base *ptr)
{
    ptr->func();
    // For the compile time func is Base::func()
    // For the runtime func is Der::func()
    // For dynamic types, there is no accessibility control at the virtual dispatch
    // But for static types, accessibility control will be done at the virtual dispatch
    // For compile time, if Base::func() is private, it is error
    // But in the runtime, Der::func() is private, but there is no error
}

int main()
{
    Der mder;
    gfoo(&mder); // Valid
}

//=====================

#include <iostream>

class Base
{
    virtual void func()
    {
        std::cout << "Base::func()\n";
    }
};

class Der : public Base
{
    void func() override
    {
        std::cout << "Der::func()\n";
    }
};

void gfoo(Base *ptr)
{
    ptr->func(); // error
    // This code will not be compiled
}

int main()
{
    Der mder;
    gfoo(&mder); // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* There is no relation between runtime and default argument.
 * Default argument is a compile time tool not runtime.
 *
 * Name lookup, Access control, Default argument are compile time tool.
 */

#include <iostream>
class Base
{
public:
    virtual void func(int x = 10)
    {
        std::cout << "Base::func() x = " << x << "\n";
    }
};
class Der : public Base
{
public:
    void func(int x = 99)
    {
        std::cout << "Der::func() x = " << x << "\n";
    }
};
void gfoo(Base *ptr)
{
    ptr->func();
}

int main()
{
    Der mder;
    gfoo(&mder); // Der::func x = 10
    // At compile time Base::func will be called with 10.
    // But at runtime Der::func will be called.
    // But the default argument that sent to func will be definitely 10.

    mder.func(); // Der::func x = 99
                 // There is no virtual dispatch
}

//===================================

#include <iostream>

class Base
{
    virtual void func()
    {
        std::cout << "Base::func()\n";
    }
};

class Der : public Base
{
    void func() override
    {
        std::cout << "Der::func()\n";
    }
};

void gfoo(Base *ptr)
{
    ptr->func(); // error
    // This code will not be compiled
}

int main()
{
    Der mder;
    gfoo(&mder); // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
