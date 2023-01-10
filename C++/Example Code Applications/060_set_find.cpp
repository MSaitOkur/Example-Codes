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


    // multisette yapilan aramada birden fazla ilkinin konumu dondurulur.
    if (auto iter = tset.find(town); iter != tset.end())
        std::cout << *iter << " bulundu, index: " << std::distance(tset.begin(), iter) << "\n";
    else 
        std::cout << "Bulunamadi.\n";
}