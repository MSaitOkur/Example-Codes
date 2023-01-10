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
    std::set<std::string> tset;
    fill_set(tset, 20, rtown);

    print_set(tset);

    std::string town;
    std::cout << "Aranacak sehri giriniz: ";
    std::cin >> town;

    // Containerda bu ogeden varmi sorusunu sormak icin en kullunisli yontem.
    if (tset.count(town))
        std::cout << "Evet var.\n";
    else
        std::cout << "Hayir yok\n";
}