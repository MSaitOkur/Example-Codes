#include <iostream>
#include <cstdlib>

class A
{
public:
    A()
    {
        std::cout << "A() was called.\n";
    }

    ~A()
    {
        std::cout << "~A() was called.\n";
    }
};

void *operator new(size_t new_size)
{
    std::cout << "operator new(size_t) was called.\n";

    if (void *ptr = malloc(new_size); ptr)
        return ptr;

    return nullptr;
}

void operator delete(void *ptr)
{
    std::cout << "operator delete(void *) was called.\n";

    if (ptr)
        free(ptr);
}

int main()
{
    A *a = new A;
    // A *a = static_cast<A *>(operator new(sizeof(A)));

    delete a;
    // operator delete(a);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <cstdlib>

class A
{
public:
    A()
    {
        std::cout << "A() was called. this = " << this << "\n";
    }

    ~A()
    {
        std::cout << "~A() was called. this = " << this << "\n";
    }
};

void *operator new(size_t new_size)
{
    std::cout << "operator new(size_t)\n";

    void *ptr = std::malloc(new_size);
    if (!ptr)
        throw std::bad_alloc{};

    std::cout << "The address of allocated block = " << ptr << '\n';
    return ptr;
}

void operator delete(void *ptr)
{
    std::cout << "operator delete(void *) address: " << ptr << "\n";

    if (ptr)
        free(ptr);
}

int main()
{
    std::cout << "main started.\n";
    A *a = new A;
    // A *a = static_cast<A *>(operator new(sizeof(A)));

    std::cout << "main continues. 1\n";

    delete a;
    // operator delete(a);

    std::cout << "main continues. 2\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

class Neco
{
public:
    Neco();
    Neco(int x, int y);
};

int main()
{
    Neco *p1 = new Neco;   // default initialization -> default ctor
    Neco *p2 = new Neco(); // value initialization -> default ctor
    Neco *p3 = new Neco{}; // C++11 -> default ctor

    Neco *p4(new Neco);
    Neco *p5(new Neco(12, 56));
    Neco *p6(new Neco{2, 5});

    auto p7{new Neco};
    auto p8{new const Neco()};
    auto p9{new const Neco{}};
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
#include <iostream>
#include <cstdlib>

class A
{
    char buffer[1];

public:
    A()
    {
        std::cout << "A::A() this = " << this << "\n";
    }
    ~A()
    {
        std::cout << "A::~A() this = " << this << "\n";
    }
};

void *operator new[](size_t size)
{
    std::cout << "operator new[](size_t), size = " << size << "\n";
    void *ptr = std::malloc(size);

    if (!ptr)
        throw std::bad_alloc{};

    std::cout << "Address allocated block = " << ptr << '\n';
    return ptr;
}

void operator delete[](void *ptr)
{
    std::cout << "operator delete[](void*), address = " << ptr << '\n';

    if (ptr)
        std::free(ptr);
}

int main()
{
    std::cout << "sizeof(A)  = " << sizeof(A) << '\n';
    std::cout << "sizeof(A*) = " << sizeof(A *) << '\n';

    auto p = new A[5]; // array new operator ( operator new[] )
    delete[] p;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

int main()
{
    size_t n;
    std::cout << "kac tamsayi : ";
    std::cin >> n;

    auto p = static_cast<int *>(operator new(n * sizeof(int)));

    for (size_t i = 0; i < n; i++)
        p[i] = i;

    for (size_t i = 0; i < n; i++)
        std::cout << p[i] << " ";

    std::cout << "\n";

    operator delete(p);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>

int main()
{
    size_t n;
    std::cout << "kac tamsayi : ";
    std::cin >> n;

    auto p = new int[n];

    for (size_t i = 0; i < n; i++)
        p[i] = i;

    for (size_t i = 0; i < n; i++)
        std::cout << p[i] << " ";

    std::cout << "\n";

    operator delete[](p);
}