#include <iostream>
#include <vector>
#include "nutility.hpp"
#include <algorithm>
#include <functional>
#include <iterator>

int main()
{
    std::vector<int> ivec1;
    std::vector<int> ivec2;

    fc(ivec1, 10, Irand{0, 10});
    fc(ivec2, 10, Irand{0, 10});

    std::vector<int> ivec3(ivec1.size());
    std::transform(ivec1.begin(), ivec1.end(), ivec2.begin(), ivec3.begin(), std::multiplies{});
    
    std::vector<int> ivec4(ivec1.size());
    std::transform(ivec1.begin(), ivec1.end(), ivec2.begin(), ivec4.begin(), [](int i1, int i2)
                   { return i1 * i2; });

    pc(ivec1, " ");
    pc(ivec2, " ");
    pc(ivec3, " ");
    pc(ivec4, " ");
}
