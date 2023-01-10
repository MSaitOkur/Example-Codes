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

    auto p = myset.equal_range(ival);
    std::cout << "Equal range: ";
    for (auto iter = p.first; iter != p.second; ++iter)
        std::cout << *iter << " ";
    std::cout << '\n';
}