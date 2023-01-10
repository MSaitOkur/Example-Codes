#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include "nutility.hpp"
#include <fstream>
#include <cstdlib>
#include <iomanip>

int main()
{
    std::vector<std::pair<int, std::string>> myvec;
    while (myvec.size() < 20000)
        myvec.push_back(std::make_pair(Irand{0, 100}(), rname()));

    std::ofstream ofs{"out.txt"};
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi acilamadi.\n";
        std::exit(EXIT_FAILURE);
    }

    auto fc = [](const auto &p1, const auto &p2)
    { return p1.second < p2.second; };

    std::sort(myvec.begin(), myvec.end());
    std::sort(myvec.begin(), myvec.end(), fc);

    ofs << std::left;
    for (const auto &[no, name] : myvec)
        ofs << std::setw(3) << no << "    " << name << "\n";
}