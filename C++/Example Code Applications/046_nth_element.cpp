#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "nutility.hpp"
#include <fstream>
#include <cstdlib>

int main()
{
    std::vector<std::string> myvec;
    while (myvec.size() < 1000)
        myvec.push_back(rname() + " " + rfname());

    std::size_t n;
    std::cout << "kac indexli oge oge: ";
    std::cin >> n;

    std::nth_element(myvec.begin(), myvec.begin() + n, myvec.end());
    std::cout << *(myvec.begin() + n) << "\n";

    std::sort(myvec.begin(), myvec.end());

    std::ofstream ofs{"out.txt"};
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        std::exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < myvec.size(); ++i)
        ofs << "[ " << i << "] : " << *(myvec.begin() + i) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

template <typename Iter, typename UnPred>
auto get_median(Iter beg, Iter end, UnPred f)
{
    std::size_t median_idx = std::distance(beg, end) / 2;
    std::nth_element(beg, median_idx, end, f);
    return std::next(beg, median_idx);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
