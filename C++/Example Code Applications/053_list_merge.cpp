#include <iostream>
#include <string>
#include <list>
#include "nutility.hpp"

int main()
{
    std::list<std::string> male_list{"ali", "berk", "cetin", "efe"};
    std::list<std::string> female_list{"cansu", "derya", "gulden", "nagehan"};

    std::cout << sl;

    male_list.merge(female_list);

    std::cout << "female_list.size() = " << female_list.size() << '\n';
    for (const auto &s : female_list)
        std::cout << s << " ";
    std::cout << sl;

    std::cout << "male_list.size()   = " << male_list.size() << '\n';
    for (const auto &s : male_list)
        std::cout << s << " ";
    std::cout << sl;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

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
    fill_list(ls1, 20);
    fill_list(ls2, 20);

    std::cout << "ls1.size() = " << ls1.size() << '\n';
    std::cout << "ls2.size() = " << ls2.size() << '\n';

    auto f = [](const auto &s1, const auto &s2)
    { return s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2); };

    ls1.sort(f);
    ls2.sort(f);

    print_list(ls1);
    print_list(ls2);

    ls1.merge(ls2, f);

    print_list(ls1);
    print_list(ls2);
}