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

    ls.reverse(); 

    for (auto citer = ls.begin(); citer != ls.end(); ++citer)
        std::cout << *citer << " ";
    std::cout << sl;
}