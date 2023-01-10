#include <iostream>
#include <string>
#include "nutility.hpp"
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> town_vec;
    fc(town_vec, 50, rtown);

    std::sort(town_vec.begin(), town_vec.end());
    pc(town_vec);

    std::string town;
    std::cout << "Aranacak ili girin: ";
    std::cin >> town;

    if(std::binary_search(town_vec.begin(), town_vec.end(), town))
        std::cout << "Bulundu\n";
    else
        std::cout << "Bulunamadi\n";
}