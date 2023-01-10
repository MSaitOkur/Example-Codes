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

    std::multiset<int> mymset{myvec.begin(), myvec.end()};
    pc(mymset);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <set>
#include "nutility.hpp"
#include "date.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t size, Func f)
{
    for (std::size_t i = 0; i < size; ++i)
        c.insert(f());
}

int main()
{
    auto f = [](const Date &d1, const Date &d2)
    { return d1.get_month_day() < d2.get_month_day(); };

    std::set<Date, decltype(f)> dset{f};
    fill_set(dset, 1000, Date::random_date);
    for (const auto &val : dset)
        std::cout << val << "\n";
    std::cout << "dset.size() = " << dset.size() << '\n';

    std::cout << sl;

    std::multiset<Date, decltype(f)> dmultiset{f};
    fill_set(dmultiset, 1000, Date::random_date);
    for (const auto &val : dmultiset)
        std::cout << val << "\n";
    std::cout << "dmultiset.size() = " << dmultiset.size() << '\n';
    std::cout << sl;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <set>
#include "nutility.hpp"
#include "date.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t size, Func f)
{
    for (std::size_t i = 0; i < size; ++i)
        c.insert(f());
}

int main()
{
    std::set<Date> dset;
    fill_set(dset, 100000, Date::random_date);
    std::cout << "dset.size() = " << dset.size() << '\n';

    std::cout << sl;

    std::multiset<Date> dmultiset;
    fill_set(dmultiset, 100000, Date::random_date);
    std::cout << "dmultiset.size() = " << dmultiset.size() << '\n';
    std::cout << sl;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
