#include <iostream>
#include <string>
#include "nutility.hpp"
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> svec;

    // for icinde vectore isim eklenecek ama vectorun sirasi bozulmayacak
    for (char c; (c = std::getchar()) != 'e';)
    {
        std::string name{rname()};
        std::cout << "Eklenecek isim : " << name << "\n";

        svec.insert(std::lower_bound(svec.begin(), svec.end(), name), name);
        pc(svec);
    }
}