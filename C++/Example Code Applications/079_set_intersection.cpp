#include <iostream>
#include <string>
#include "nutility.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> ivec1, ivec2;
    auto myrand = Irand{0, 20};
    fc(ivec1, 20, myrand);
    fc(ivec2, 20, myrand);

    std::sort(ivec1.begin(), ivec1.end());
    std::sort(ivec2.begin(), ivec2.end());

    pc(ivec1);
    pc(ivec2);

    std::set_intersection(ivec1.begin(), ivec1.end(), ivec2.begin(), ivec2.end(),
                          std::ostream_iterator<int>{std::cout, " "});
    std::cout << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// #include <iostream>
// #include <string>
// #include "nutility.hpp"
// #include <vector>
// #include <algorithm>
// #include <iterator>

// int main()
// {
//     std::vector<std::string> svec1, svec2;
//     fc(svec1, 20, rname);
//     fc(svec2, 20, rname);

//     auto f = [](const auto &s1, const auto &s2)
//     { return s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2); };

//     std::sort(svec1.begin(), svec1.end(), f);
//     std::sort(svec2.begin(), svec2.end(), f);

//     pc(svec1);
//     pc(svec2);

//     std::set_intersection(svec1.begin(), svec1.end(), svec2.begin(), svec2.end(),
//                           std::ostream_iterator<std::string>{std::cout, " "}, f);
//     std::cout << "\n";
// }