#include <iostream>
#include "ReferenceWrapper.hpp"

int main()
{
    int a, b;

    ReferenceWrapper r = a;
    auto x = Ref(a);

    x.get() = 231;

    std::cout << x << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>

int main()
{
    int x{123}, y{46};

    std::reference_wrapper r = x;

    std::cout << "r = " << r << ", x = " << x << "\n";

    ++r; // ++r.operator int&();

    std::cout << "r = " << r << ", x = " << x << "\n";

    r = y; // r rebinds to y now

    std::cout << "r = " << r << ", y = " << y << "\n";

    r.get() = 245;

    std::cout << "r = " << r << ", y = " << y << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>

template <typename T>
void func(T x)
{
    ++x;
}

int main()
{
    int a{10};

    func(a);
    std::cout << "a = " << a << '\n';

    func(std::ref(a));
    std::cout << "a = " << a << '\n';
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
#include <iostream>
#include <functional>
#include <utility>

int main()
{
    int x = 10;
    double d = 2.13;

    auto p1 = std::make_pair(x, d);
    p1.first++;
    p1.second--;

    std::cout << "x = " << x << ", d = " << d << "\n";

    auto p2 = std::make_pair(std::ref(x), std::ref(d));
    p2.first++;
    p2.second--;

    std::cout << "x = " << x << ", d = " << d << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>

int main()
{
    int x = 10;
 
    auto r1 = std::ref(x);
    ++r1; // valid

    auto r2 = std::cref(x);
    ++r2; // invalid
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <vector>

struct Biggie
{
    bool operator()(int i) const
    {
        //...
        return true;
    }

    // very big data member
};

int main()
{
    const Biggie cbig;

    std::vector<int> ivec;
    std::vector<int> destvec;
    
    // Burada copy_if'in sonunda predicate ifade icin copy ctor. cagrilacaktir.
    // Referans ile gonderilemez cunku fonksiyon parametresi T& degil T dir.
    std::copy_if(ivec.begin(), ivec.end(), std::back_inserter(destvec), cbig);

    // Yukaridaki kopyalama maliyetinden kurtulmak icin reference_wrapper kullanilmalidir.
    std::copy_if(ivec.begin(), ivec.end(), std::back_inserter(destvec), std::ref(cbig));

}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <vector>

int main()
{
    int a, b, c, d;

    // Containerlar referans tutamazlar. Elemanlari object type olmalidirlar.
    // Ancak burada da reference_wrapper ile nesnelerin referanslarinin containerda
    // tutulmasi saglanmaktadir.

    std::vector<int &> rvec{a, b, c, d}; // gecersiz
    std::vector<std::reference_wrapper<int>> rvec{a, b, c, d}; // gecerli
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <vector>

int main()
{
    int a{}, b{}, c{}, d{};

    std::vector<std::reference_wrapper<int>> rvec{a, b, c, d};

    ++rvec[0];
    ++rvec[1];
    ++rvec[2];
    ++rvec[3];

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "c = " << c << '\n';
    std::cout << "d = " << d << '\n';
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include "nutility.hpp"
#include <random>
#include <algorithm>

int main()
{
    std::list<std::string> slist;
    fc(slist, 20, rname);
    pc(slist);

    std::vector<std::reference_wrapper<std::string>> svec{slist.begin(), slist.end()};
    std::shuffle(svec.begin(), svec.end(), std::mt19937{std::random_device{}()});

    for (auto r : svec)
        r.get() += "_tr";

    for (auto r : svec)
        std::cout << r.get() << " ";
    std::cout << "\n";
}