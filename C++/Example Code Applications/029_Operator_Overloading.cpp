struct x
{
};

int main()
{
    int y;

    x @y; // There is no operator like '@', in CPP.
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Some operators cannot be overloaded in C++.
 *      => " ?: "
 *      => sizeof
 *      => scope resolution operator '::'
 *      => member access operator '.'
 *      => member access through pointer to member operator '.*'
 *      => typeid operator
 */

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Some operator functions cannot be global operator function.
 * If they wanted to overloaded, it should has been written as a member
 * operator function.
 *
 * subscript operator '[]'
 * pointer member selection operator
 * assignment special member functions (copy and move assignment
 * type cast operator functions
 */

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Neco
{
};

bool operator<(Neco, Neco); // Valid
bool operator<(Neco);       // Invalid (global operator< must have 2 operands)

bool operator!(Neco);       // Valid
bool operator!();           // Invalid (global operator! must have 1 operands)
bool operator!(Neco, Neco); // Invalid (global operator! must have 1 operands)

//--------------------------------------------------------------------
//--------------------------------------------------------------------

class Neco
{
    bool operator!();     // Valid
    bool operator!(Neco); // Invalid (Member operator! must have no operand)

    bool operator<(Neco);       // Valid
    bool operator<();           // Invalid (Member operator< must have one operand)
    bool operator<(Neco, Neco); // Invalid (Member operator< must have one operand)
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// if '*' , '+' , '>' operator functions are global operator functions
// m = x * y + z > t
m.operator=(operator>(operator+(operator*(x, y), z), t));

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// if '*' , '%' , '/' operator functions are global operator functions
// x % y * z / t
operator/(operator*(operator%(x, y), z), t);

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class counter
{
public:
    counter operator+(int) const;
};
int main()
{
    counter c;
    c + 5; // Valid
    5 + c; // Invalid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class counter
{
public:
    counter operator+(int) const;
};

counter operator+(int, counter);

int main()
{
    counter c;
    c + 5; // Valid
    5 + c; // Valid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
class counter
{
};

std::ostream &operator<<(std::ostream &, counter);

int main()
{
    counter c1, c2, c3;
    std::cout << c1 << c2 << c3;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include "Darray.hpp"

int main()
{
    Darray da{10};
    const Darray cda{10};

    std::cout << da << '\n';

    for (size_t i = 0; i < 10; ++i)
        da[i] = i * 1.1;

    std::cout << da << '\n';

    cda[5] = 23; // Invalid, const member function was called
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include "Myclass_Myclassptr.hpp"

int main()
{
    std::cout << "main started.\n";

    MyclassPtr mptr1{new Myclass};
    MyclassPtr mptr2{new Myclass};

    // MyclassPtr mptr3 = mptr1; // error
    MyclassPtr mptr3 = std::move(mptr1); // valid

    // MyclassPtr mptr4{mptr2};  // error
    MyclassPtr mptr4{std::move(mptr2)}; // valid

    // mptr3 = mptr4;         // Invalid
    mptr3 = std::move(mptr4); // Valid

    Myclass m;

    *mptr3 = m;
    mptr3->foo();
    mptr3->func();

    std::cout << "main continues.\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include "Counter.hpp"
#include "UniquePtr.hpp"

int main()
{
    std::cout << "main started.\n";

    UniquePtr<Counter> uptr1{new Counter};
    UniquePtr<Counter> uptr2 = static_cast<UniquePtr<Counter>>(new Counter);

    std::cout << *uptr1 << '\n';
    std::cout << *uptr2 << '\n';

    uptr1->set(213);
    uptr2->set(1);

    --*uptr1;
    ++*uptr2;

    std::cout << *uptr1 << '\n';
    std::cout << *uptr2 << '\n';

    std::cout << "main continues.\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
#include <iostream>
#include "Random.hpp"

int main()
{
    std::cout << "main started.\n";

    Random r1{5, 20};

    for (std::size_t i = 0; i < 10; ++i)
        std::cout << r1() << " ";

    std::cout << '\n';

    std::cout << r1.get_count() << " times random number was generated.\n";

    int rand_val = r1; // type cast operator function is called

    std::cout << "rand_val = " << rand_val << '\n';

    std::cout << "main continues.\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
