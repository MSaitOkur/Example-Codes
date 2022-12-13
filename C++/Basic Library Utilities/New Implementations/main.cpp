#include "date.hpp"
#include <iostream>

int main()
{
    Date d1{1, 12, 2022};
    Date d2{31, 12, 2022};
    Date d3{1, 1, 2022};
    Date d4{1, 1, 2023};

    std::cout << "d1 - d2 = " << d1 - d2 << ", d2 - d1 = " << d2 - d1 << "\n";
    std::cout << "d1 - d3 = " << d1 - d3 << ", d3 - d1 = " << d3 - d1 << "\n";
    std::cout << "d2 - d4 = " << d2 - d4 << ", d4 - d2 = " << d4 - d2 << "\n";
    std::cout << "d1 - d4 = " << d1 - d4 << ", d4 - d1 = " << d4 - d1 << "\n";
    std::cout << "d3 - d4 = " << d3 - d4 << ", d4 - d3 = " << d4 - d3 << "\n";
    
    
}