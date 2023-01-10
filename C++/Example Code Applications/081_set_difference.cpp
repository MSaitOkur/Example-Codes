#include <iostream>
#include "nutility.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> ivec1, ivec2;
    auto myrand = Irand{0, 100};
    fc(ivec1, 20, myrand);
    fc(ivec2, 20, myrand);

    std::sort(ivec1.begin(), ivec1.end());
    std::sort(ivec2.begin(), ivec2.end());

    pc(ivec1);
    pc(ivec2);

    std::vector<int> ivec3(40), ivec4(40), ivec5(40);
    
    std::set_difference(ivec1.begin(), ivec1.end(), ivec2.begin(), ivec2.end(), ivec3.begin());
    std::set_difference(ivec2.begin(), ivec2.end(), ivec1.begin(), ivec1.end(), ivec4.begin());

    std::set_symmetric_difference(ivec2.begin(), ivec2.end(), ivec1.begin(), ivec1.end(), ivec5.begin());

    pc(ivec3);
    pc(ivec4);
    pc(ivec5);
}
