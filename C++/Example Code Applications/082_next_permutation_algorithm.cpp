#include <iostream>
#include "nutility.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> ivec;
    fc(ivec, 5, Irand{0, 100});
    std::sort(ivec.begin(), ivec.end());

    std::size_t total_perm_cnt{};
    do{
        pc(ivec);
        ++total_perm_cnt;
    }
    while(std::next_permutation(ivec.begin(), ivec.end()));

    std::cout << "ivec.size() = " << ivec.size() << ", total_perm_cnt = " << total_perm_cnt << "\n";
}
