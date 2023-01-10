#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "nutility.hpp"
#include <fstream>
#include <cstdlib>
#include <functional>

int main()
{
    std::vector<std::string> myvec;
    while (myvec.size() < 20000)
        myvec.push_back(rname() + " " + rfname());

    std::size_t n;
    std::cout << "ilk kac oge siralansin: ";
    std::cin >> n;

    std::ofstream ofs{"out.txt"};
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi acilamadi.\n";
        std::exit(EXIT_FAILURE);
    }

    std::partial_sort(myvec.begin(), myvec.begin() + n, myvec.end());
    // std::partial_sort(myvec.begin(), myvec.begin() + n, myvec.end(), std::greater{});

    ofs << std::left;
    for (const auto &name : myvec)
        ofs << name << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "nutility.hpp"
#include <fstream>
#include <cstdlib>
#include <functional>

int main()
{
    std::vector<std::string> myvec;
    while (myvec.size() < 20000)
        myvec.push_back(rname() + " " + rfname());

    std::size_t n;
    std::cout << "ilk kac oge siralansin: ";
    std::cin >> n;

    std::ofstream ofs{"out.txt"};
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi acilamadi.\n";
        std::exit(EXIT_FAILURE);
    }

    std::vector<std::string> destvec(n);

    std::partial_sort_copy(myvec.begin(), myvec.end(), destvec.begin(), destvec.end());

    ofs << std::left;
    for (const auto &name : destvec)
        ofs << name << "\n";
}