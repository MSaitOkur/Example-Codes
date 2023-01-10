
#include <iostream>
#include <vector>
#include "nutility.hpp"
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <iterator>

int main()
{
    std::vector<std::string> svec;
    while (svec.size() < 100000)
        svec.push_back(rname() + " " + rfname());

    std::sort(svec.begin(), svec.end());

    std::ofstream ofs{"out.txt"};
    if (!ofs.is_open())
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        std::exit(EXIT_FAILURE);
    }

    std::copy(svec.begin(), svec.end(), std::ostream_iterator<std::string>(ofs, "\n"));
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <vector>
#include "nutility.hpp"
#include <algorithm>
#include <functional>
#include <fstream>
#include <iterator>
#include "date.hpp"

int main()
{
    std::vector<Date> dvec;
    while (dvec.size() < 100000)
        dvec.push_back(Date::random_date());

    std::sort(dvec.begin(), dvec.end());
    // std::sort(dvec.begin(), dvec.end(), std::greater{});
    // std::sort(dvec.rbegin(), dvec.rend());

    std::ofstream ofs{"out.txt"};
    if (!ofs.is_open())
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        std::exit(EXIT_FAILURE);
    }

    std::copy(dvec.begin(), dvec.end(), std::ostream_iterator<Date>(ofs, "\n"));
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <vector>
#include "nutility.hpp"
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <iterator>

int main()
{
    std::vector<std::string> svec;
    while (svec.size() < 10000)
        svec.push_back(rname() + " " + rfname());

    std::sort(svec.begin(), svec.end(), [](const std::string &s1, const std::string &s2)
              { return s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2); });

    std::ofstream ofs{"out.txt"};
    if (!ofs.is_open())
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        std::exit(EXIT_FAILURE);
    }

    std::copy(svec.begin(), svec.end(), std::ostream_iterator<std::string>(ofs, "\n"));
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// std::sort algoritmasi stable sort degildir.

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
    std::sort(myvec.begin(), myvec.end(), fc); // stable sort kalmayacak

    ofs << std::left;
    for (const auto &[no, name] : myvec)
        ofs << std::setw(3) << no << "    " << name << "\n";
}