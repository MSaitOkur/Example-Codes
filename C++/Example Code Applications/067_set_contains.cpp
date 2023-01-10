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
    std::set<int> iset;
    fill_set(iset, 100, Irand{0, 150});
    print_set(iset);

    std::cout << std::boolalpha;

    std::cout << "iset.contains(10) = " << iset.contains(10) << '\n';   // C++20
    std::cout << "iset.contains(140) = " << iset.contains(140) << '\n'; // C++20
}