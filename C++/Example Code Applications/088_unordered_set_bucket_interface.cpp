#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "nutility.hpp"
#include <iomanip>

int main()
{
    std::unordered_set<std::string> myset(100);
    fc(myset, 200, rname);

    std::ofstream ofs{"out.txt"};
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        std::exit(EXIT_FAILURE);
    }

    pc(myset, " ", ofs);

    ofs << "myset.size()                    = " << myset.size() << '\n';
    ofs << "myset.bucket_count()            = " << myset.bucket_count() << '\n';
    ofs << "myset.load_factor()             = " << myset.load_factor() << '\n';
    ofs << "myset.size / myset.bucket_count = " << static_cast<float>(myset.size()) / myset.bucket_count() << '\n';
    ofs << "myset.max_load_factor()         = " << myset.max_load_factor() << '\n';
    myset.max_load_factor(0.75);
    ofs << "myset.max_load_factor()         = " << myset.max_load_factor() << '\n';

    for (std::size_t i{}; i < myset.bucket_count(); ++i)
    {
        ofs << "[" << std::setw(3) << i << "]";
        ofs << " (" << std::setw(2) << myset.bucket_size(i) << ") ";
        for (auto bucket_elems_iter = myset.cbegin(i); bucket_elems_iter != myset.cend(i); ++bucket_elems_iter)
            ofs << *bucket_elems_iter << " - ";
        ofs << "\n";
    }
}