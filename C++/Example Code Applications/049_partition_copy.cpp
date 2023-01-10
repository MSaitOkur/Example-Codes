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

    std::cout << "\n\n";

    std::cout << "Icinde hangi karakter olanlar basa gelsin: ";
    char c;
    std::cin >> c;

    std::vector<std::string> ok_vec;
    std::vector<std::string> not_ok_vec;

    std::partition_copy(svec.begin(), svec.end(), std::back_inserter(ok_vec), std::back_inserter(not_ok_vec),
                        [c](const std::string &s)
                        { return s.find(c) != std::string::npos; });

    std::cout << "Kosulu saglayanlar: \n";
    std::copy(ok_vec.begin(), ok_vec.end(), std::ostream_iterator<std::string>{std::cout, " "});

    std::cout << "\n\n";

    std::cout << "Kosulu saglamayanlar: \n";
    std::copy(not_ok_vec.begin(), not_ok_vec.end(), std::ostream_iterator<std::string>{std::cout, " "});

    std::cout << "\n";
}