#include <functional>
template <typename KEY, typename comp = std::less<KEY>, typename A = std::allocator<KEY>>
class myset;

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <set>
#include <string>
#include <functional>
#include "date.hpp"
#include "nutility.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t n, Func f)
{
    while (c.size() < n)
        c.insert(f());
}

template <typename Container>
void print_set(const Container &c, const char *delim = " ")
{
    for (auto val : c)
        std::cout << val << delim;
    std::cout << sl;
}

int main()
{
    std::set<int> myset;
    fill_set(myset, 20, Irand{0, 100});
    print_set(myset);

    std::set<std::string, std::greater<std::string>> sset;
    fill_set(sset, 10, rname);
    print_set(sset);

    std::set<Date, std::greater<Date>> dateset;
    fill_set(dateset, 100, Date::random_date);
    print_set(dateset, "\n");
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------


#include <iostream>
#include <set>
#include <string>
#include <functional>
#include "date.hpp"
#include "nutility.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t n, Func f)
{
    while (c.size() < n)
        c.insert(f());
}

template <typename Container>
void print_set(const Container &c, const char *delim = " ")
{
    for (auto val : c)
        std::cout << val << delim;
    std::cout << sl;
}

template <typename T>
struct Comp
{
    bool operator()(const T &a, const T &b) const
    {
        return a > b;
    }
};

template <typename T>
constexpr bool my_cmp(const T &t1, const T &t2)
{
    return t1 > t2;
}

int main()
{
    std::set<int, Comp<int>> myset1;
    fill_set(myset1, 20, Irand{0, 10000});
    print_set(myset1);

    std::set<int, decltype(&my_cmp<int>)> myset2(my_cmp);
    fill_set(myset2, 20, Irand{0, 10000});
    print_set(myset2);

    std::set<int, bool (*)(const int &, const int &)> myset3(my_cmp);
    fill_set(myset3, 20, Irand{0, 10000});
    print_set(myset3);

    auto f = [](int a, int b)
    { return a > b; };

    std::set<int, decltype(f)> myset4(f);
    fill_set(myset4, 20, Irand{0, 10000});
    print_set(myset4);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <set>
#include "nutility.hpp"
#include <vector>

int main()
{
    std::vector<int> myvec;
    fc(myvec, 10, Irand{0, 3});
    pc(myvec);

    std::set<int> myset{myvec.begin(), myvec.end()};
    pc(myset);

}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
