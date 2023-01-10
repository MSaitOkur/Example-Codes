#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "nutility.hpp"

int main()
{
    std::vector<std::string> svec;
    fc(svec, 100000, rname);

    std::unordered_map<std::string, int> mymap;
    for (const auto &s : svec)
        ++mymap[s];

    for (const auto &[name, count] : mymap)
        std::cout << name << "   " << count << "\n";
}