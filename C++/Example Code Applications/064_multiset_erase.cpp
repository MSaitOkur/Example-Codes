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
    std::multiset<std::string> myset;
    fill_set(myset, 500, rtown);
    print_set(myset);

    std::string town;
    std::cout << "silinecek ili girin: ";
    std::cin >> town;

    auto n = myset.erase(town);
    std::cout << n << " adet il silindi.\n";

    print_set(myset);
}