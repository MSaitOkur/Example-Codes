#include <iostream>
#include <list>
#include <string>
#include "nutility.hpp"
#include <functional>

int main()
{
    std::list<std::string> ls;
    while (ls.size() < 10)
        ls.push_back(rname());

    for (auto citer = ls.begin(); citer != ls.end(); ++citer)
        std::cout << *citer << " ";
    std::cout << sl;

    ls.sort();

    for (auto citer = ls.begin(); citer != ls.end(); ++citer)
        std::cout << *citer << " ";
    std::cout << sl;

    ls.sort(std::greater{});

    for (auto citer = ls.begin(); citer != ls.end(); ++citer)
        std::cout << *citer << " ";
    std::cout << sl;

    ls.sort([](const std::string &s1, const std::string &s2)
            { return s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2); });

    for (auto citer = ls.begin(); citer != ls.end(); ++citer)
        std::cout << *citer << " ";
    std::cout << sl;
}