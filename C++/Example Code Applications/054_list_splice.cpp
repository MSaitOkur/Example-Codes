#include <iostream>
#include <string>
#include <list>
#include "nutility.hpp"

template <typename T>
void fill_list(std::list<T> &ls, std::size_t size)
{
    while (ls.size() < size)
        ls.emplace_back(rname());
}

template <typename T>
void print_list(const std::list<T> ls)
{
    for (const auto &s : ls)
        std::cout << s << " ";
    std::cout << sl;
}

int main()
{
    std::list<std::string> ls1;
    std::list<std::string> ls2;
    fill_list(ls1, 5);
    fill_list(ls2, 4);

    print_list(ls1);
    print_list(ls2);

    // ls1.splice(ls1.begin(), ls2);
    // ls1.splice(std::prev(ls1.end()), ls2, ls2.begin());
    ls1.splice(std::next(ls1.begin()), ls2, ls2.begin(), ls2.end());

    print_list(ls1);
    print_list(ls2);
}