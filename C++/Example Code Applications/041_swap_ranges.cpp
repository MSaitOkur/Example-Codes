#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "nutility.hpp"
#include <algorithm>

int main()
{
    std::vector<std::string> svec;
    std::list<std::string> slist;

    while (svec.size() < 10)
    {
        svec.insert(svec.end(), rname());
        slist.insert(slist.end(), rtown());
    }

    std::cout << "svec: ";
    for (const std::string &sv : svec)
        std::cout << sv << " ";
    std::cout << "\n";

    std::cout << "list: ";
    for (const std::string &sv : slist)
        std::cout << sv << " ";
    std::cout << "\n";

    std::swap_ranges(svec.begin(), svec.end(), slist.begin());

    std::cout << "\n\n";

    std::cout << "svec: ";
    for (const std::string &sv : svec)
        std::cout << sv << " ";
    std::cout << "\n";

    std::cout << "list: ";
    for (const std::string &sv : slist)
        std::cout << sv << " ";
    std::cout << "\n";
}