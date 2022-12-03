#include <iostream>

class Myclass
{
public:
    Myclass(int x)
    {
        std::cout << "Myclass(int x) x = " << x << " this = " << this << "\n";
    }
    ~Myclass()
    {
        std::cout << "~Myclass() this = " << this << "\n";
    }
};

int main()
{
    std::cout << "main started\n";

    Myclass{12}; // Temporary object

    std::cout << "main continues\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* If a reference be reference to a temporary object, temp. object's life will last as long as the
 * reference is alive. But this is not as same as for pointers. If a pointer points a temp. object,
 * the pointer doesn't extent the temp. objects life.
 */

#include <iostream>
class Myclass
{
public:
    Myclass(int x)
    {
        std::cout << "Myclass(int x) x = " << x << " this = " << this << "\n";
    }
    ~Myclass()
    {
        std::cout << "~Myclass() this = " << this << "\n";
    }
};
int main()
{
    std::cout << "main started.\n";

    // Myclass &r = Myclass{12}; // Invalid. (Lvalue reference cannot be binded to an rvalue expr.)
    const Myclass &r = Myclass{12}; // Valid

    std::cout << "main continues.\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Myclass
{
public:
    Myclass(int x)
    {
        std::cout << "Myclass(int x) x = " << x << " this = " << this << "\n";
    }
    ~Myclass()
    {
        std::cout << "~Myclass() this = " << this << "\n";
    }
};

int main()
{
    std::cout << "main started.\n";

    if (true)
    {
        std::cout << "main continues 1\n";
        // const Myclass &r = Myclass{12}; // valid
        Myclass *p = &Myclass{12}; // invalid (pointer can't point a temporary object)
        std::cout << "main continues 2\n";
    }

    std::cout << "main continues. 3\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class Myclass
{
public:
    Myclass(int x)
    {
        std::cout << "Myclass(int x) x = " << x << " this = " << this << "\n";
    }
    ~Myclass()
    {
        std::cout << "~Myclass() this = " << this << "\n";
    }
};
void func(const Myclass &r)
{
    std::cout << "func(const Myclass &r)\n";
}
int main()
{
    std::cout << "main started.\n";
    func(Myclass{12});
    std::cout << "main continues.\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/*
 * There are following exceptions to this lifetime rule:
 *      - a temporary bound to a return value of a function in a
 *        return statement is not extended: it is destroyed immediately at the
 *        end of the return expression. Such return statement always returns a
 *        dangling reference.
 *
 *      - a temporary bound to a reference parameter in a function call exists until
 *        the end of the full expression containing that function call: if the function
 *        returns a reference, which outlives the full expression, it becomes
 *        a dangling reference.
 */

#include <iostream>

class A
{
public:
    A() { std::cout << "Ctor this = [" << this << "]\n"; }
    ~A() { std::cout << "Dtor this = [" << this << "]\n"; }

    void f() const { std::cout << "A::f()const this = [" << this << "]\n"; }
};

const A &foo(const A &a)
{
    std::cout << "foo started.\n";
    a.f();
    return a;
}

const A &func(const A &a)
{
    std::cout << "func started.\n";
    a.f();
    return foo(a);
}

int main()
{
    std::cout << "main started.\n";
    const A &a = func(A{}); // The temporary object lives until this code line was executed.
                            // After this code line a will be dangling reference which
                            // means the using of a is undefined behavior.

    a.f(); // UB (Dangling reference)
    std::cout << "main continues.\n";
}
