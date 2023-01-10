#include <iostream>
#include <set>
#include "nutility.hpp"
#include "date.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t n, Func f)
{
    while (c.size() < n)
        c.insert(f());
}

template <typename Container>
void print_set(const Container &c, const char *delim = " ")
{
    for (const auto &val : c)
        std::cout << val << delim;

    std::cout << "\n---------------------------------------------------\n";
}

int main()
{
    std::multiset<int> myset;
    fill_set(myset, 100, []
             { return rand() % 40; });
    print_set(myset);

    int ival;
    std::cout << "deger giriniz: ";
    std::cin >> ival;

    auto iter_lower = myset.lower_bound(ival);
    auto iter_upper = myset.upper_bound(ival);
    std::cout << "distance for lower_bound : " << std::distance(myset.begin(), iter_lower) << "\n";
    std::cout << "distance for upper_bound : " << std::distance(myset.begin(), iter_upper) << "\n";
    std::cout << "distance for equal range: " << std::distance(iter_lower, iter_upper) << "\n";
    std::cout << "equal range: ";
    for (auto iter = iter_lower; iter != iter_upper; ++iter)
        std::cout << *iter << " ";
    std::cout << '\n';
}