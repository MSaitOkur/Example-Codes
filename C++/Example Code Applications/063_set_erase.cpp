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
    std::set<std::string> myset;
    fill_set(myset, 10, rtown);
    print_set(myset);

    // myset.erase(myset.begin()); // Containerdaki ilk ogeyi sildi.
    // myset.erase(myset.begin(), std::prev(myset.end(), 3)); // Range'deki ogeler silindi

    std::string town;
    std::cout << "ili girin: ";
    std::cin >> town;

    if (auto iter = myset.find(town); iter != myset.end())
    {
        // myset.erase(town); // ilgili sehir silindi
        myset.erase(iter); // bulunan konumdaki oge silindi
    }

    print_set(myset);
}

