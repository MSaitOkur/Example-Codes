#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "nutility.hpp"
#include <iterator>

int main()
{
    std::vector<std::string> svec;
    while (svec.size() < 10)
        svec.insert(svec.end(), rname());

    for (const auto &s : svec)
        std::cout << s << " ";
    std::cout << "\n\n\n";

    std::cout << "Icinde hangi karakter olanlar basa gelsin: ";
    char c{};
    std::cin >> c;

    auto par_point = std::stable_partition(svec.begin(), svec.end(), [c](const std::string &s)
                                    { return s.find(c) != std::string::npos; });

    std::cout << "distance of partition point = " << std::distance(svec.begin(), par_point) << "\n";

    if (par_point != svec.end())
        std::cout << "Kosulu saglamayan ilk isim : " << *par_point << "\n";

    std::cout << "Kosulu saglayanlar: \n";
    std::copy(svec.begin(), par_point, std::ostream_iterator<std::string>{std::cout, " "});

    std::cout << "\n\n\n";
    std::cout << "Kosulu saglamayanlar: \n";
    std::copy(par_point, svec.end(), std::ostream_iterator<std::string>{std::cout, " "});
 }