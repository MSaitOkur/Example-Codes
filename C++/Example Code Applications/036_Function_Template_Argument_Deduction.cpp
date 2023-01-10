//--------------------------------------------------------------------
//--------------------------------------------------------------------
// T x is like (auto x = expr;)

#include <iostream>

template <typename T>
class TypeTeller;

template <typename T>
void func(T x)
{
    TypeTeller<T> t; // An object cannot be created from incomplete type.
                     // Type of T will be in error message.
}

int main()
{

    func(12);   // argument type: int, T ==> int
    func(12.5); // argument type: double, T ==> double

    const int ci = 2;
    func(ci); // argument type: const int, T ==> int (constness will go)

    int x = 12;
    int &rx = x;
    func(rx); // argument type: int&, T ==> int (referencenes will go)

    int x = 12;
    const int &crx = x;
    func(crx); // argument type: const int&, T ==> int

    int a[]{1, 2, 3, 4};
    func(a); // argument type: int*, T ==> int* (array to pointer conversion)

    const int ca[]{1, 2, 3, 4};
    func(ca); // argument type: const int*, T ==> const int* (array to pointer conversion)

    int x = 12;
    int *const ptr = &x;
    func(ptr); // argument type: int * const, T ==> int*
               //(constness will go if a pointer is top level const)

    func("str"); // argument type: const char *, T ==> const char * (array to pointer conversion)

    int f(int);
    func(f); // argument type: int(*)(int), T ==> int(*)(int)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// T& x is (like auto& x = expr;) except one exception

#include <iostream>

template <typename T>
class TypeTeller;

template <typename T>
void func(T &x)
{
    TypeTeller<T> t; // An object cannot be created from incomplete type.
                     // Type of T will be in error message.
}

int main()
{
    // func(12); // Invalid Call, LValue expr. must be sent to T& parameter

    int x;
    func(x); // argument type: int, T ==> int, Function parameter's type: int&

    int x = 12;
    int &rx = x;
    func(rx); // argument type: int&, T ==> int, Function parameter's type: int&

    const int x = 12;
    func(x); // argument type: const int, T ==> const int, Function parameter's type: const int&

    int x = 12;
    int *ptr = &x;
    func(ptr); // argument type: int*, T ==> int*, Function parameter's type: int*&,
               // Function parameter is not reference to x, but ptr

    int x = 12;
    const int *cptr = &x;
    func(cptr); // argument type: const int*, T ==> const int *, Function parameter's type: const int*&
                // Function parameter is not reference to x, but cptr

    int x = 12;
    int *const ptrc = &x;
    func(ptrc); // argument type: int*const, T ==> int*const, Function parameter's type: int*const&

    int x = 12;
    const int &crx = x;
    func(crx); // argument type: const int&, T ==> const int, Function parameter's type: const int&

    int a[5]{1, 2, 3, 4};
    func(a); // argument type: int[5], T ==> int[5], Function parameter's type: int&[5] (There is not array to pointer conversion)
             // Function parameter is not reference to *a, but whole array's itself

    const int ca[5]{1, 2, 3, 4};
    func(ca); // argument type: const int[5], T ==> const int[5], Function parameter's type: const int&[5] (There is not array to pointer conversion)

    func("str"); // argument type: const char[4], T ==> const char[4], Function parameter's type: const char(&)[4] (There is not array to pointer conversion)

    int f(int);
    func(f); // argument type: int(int), T ==> int(int), Function parameter's type: int(&)(int)
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// T&& x is (like auto&& x = expr;)

#include <iostream>

template <typename T>
class TypeTeller;

template <typename T>
void func(T &&x)
{
    TypeTeller<T> t;
}

int main()
{
    int y = 124;
    func(y); // argument type: int, argument value cat: Lvalue, T ==> int&, Function parameter's type: int& && ==> int&

    func(10); // argument type: int, argument value cat: Rvalue, T ==> int, Function parameter's type: int && ==> int&&

    int &&foo();
    func(foo()); // argument type: int&&, argument value cat: Xvalue, T ==> int, Function parameter's type: int&& && ==> int&&

    int &&x = 1;
    func(x); // argument type: int&&, argument value cat: Lvalue, T ==> int&, Function parameter's type: int& && ==> int&
    func(x + 3); // argument type: int, argument value cat: Rvalue, T ==> int, Function parameter's type: int&& ==> int&&
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Difference between auto Type Deduction and Template Argument Deduction

#include <iostream>

template <typename T>
class TypeTeller;

template <typename T>
void func(T &&x)
{
    TypeTeller<T> t;
}

int main()
{
    auto x = {1, 2, 3, 4, 5, 6}; // auto ===> std::initializer_list<int>
    func({1, 2, 3, 4, 5, 6});    // error
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
/* Tur cikarimi aslinda su sekilde yapilmaktadir.
 * Template'a gonderilen argumanin fonksiyonun parametre degiskenine kopyalanmasi icin
 * template tur parametresinin ne olmasi gerekir.
 *
 * The way of type deduction is the answer of this question:
 * What should the template type parameter be to copy the argument of the function to
 * parameter of the function?
 */

#include <iostream>
template <typename T>
class TypeTeller;

template <typename T>
void func(T **x)
{
    TypeTeller<T> t;
}

int main()
{
    int x{};
    int *p{&x};
    int **pp{&p};

    func(pp);  // T** x : int** x  ===> T : int
    func(&pp); // T** x : int*** x ===> T : int*
}

//========================

#include <iostream>
template <typename T>
class TypeTeller;

template <typename T>
void func(T x)
{
    TypeTeller<T> t;
}

int main()
{
    int x{};
    int *p{&x};
    int **pp{&p};
    func(pp);  // T x : int** x  ===> T : int**
    func(&pp); // T x : int*** x ===> T : int***
}

//========================

#include <iostream>

template <typename T>
class TypeTeller;

template <typename T, typename U>
void func(T (*)(U))
{
    TypeTeller<T> t;
    TypeTeller<U> u;
}

int f(double) { return 1; }

int main()
{
    func(f); // T(*)(U) : int(*)(double)  ===> T : int, U : double
}   

//========================

#include <iostream>

template <typename T, std::size_t n>
constexpr std::size_t asize(T (&r)[n])
{
    return n;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};

    std::size_t size_arr = sizeof(a) / sizeof(*a);
    std::cout << "size_arr = " << size_arr << '\n';

    constexpr auto n1 = asize(a);
    constexpr auto n2 = std::size(a); // since C++17 (size function template)

    std::cout << "n1 = " << n1 << ", n2 = " << n2 << "\n";
}

//========================

#include <iostream>

class Functor
{
public:
    void operator()() const
    {
        std::cout << "void Functor::operator()()const called\n";
    }
};

template <typename F>
void func(F f)
{
    // codes...
    f(); // F'nin türü olursa olsun bu ifadenin legal olması lazım
    // codes...
}

void foo()
{
    std::cout << "foo called\n";
}

int main()
{
    Functor fn;
    func(foo);
    func(fn);
    func(Functor{});
}

//========================

#include <iostream>

template <typename T>
void func(T)
{
    std::cout << "template<T> func(T)\n";
}

template <typename T>
void func(T *)
{
    std::cout << "template<T> func(T*)\n";
}

int main()
{
    int x{};
    func(&x); // T*, T'den daha spesifiktir.
}
//========================

#include <iostream>

template <typename T>
void func(T)
{
    std::cout << "template<T> func(T)\n";
}

template <typename T>
void func(T *)
{
    std::cout << "template<T> func(T*)\n";
}

template <typename T>
void func(T **)
{
    std::cout << "template<T> func(T**)\n";
}

int main()
{
    int x{};
    int *p = &x;

    func(x);  // Doğrudan türün kendisi gönderilmiştir.
    func(p);  // T*, T'den daha spesifiktir.
    func(&p); // T**, T*'dan daha spesifiktir.
}
//========================
#include <iostream>

template <typename T>
void func(T)
{
    std::cout << "template<T> func(T)\n";
}

template <typename T, std::size_t n>
void func(T (&r)[n])
{
    std::cout << "template<T> func(T(&r)[n])\n";
}

int main()
{
    int a[10]{};
    func(a); // func(T(&r)[n]), func(T)'den daha spesifiktir.
}
