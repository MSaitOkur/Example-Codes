#include <iostream>

int main()
{
    int x = 999;

    if (int x = 10; x == 10) // C++17
        std::cout << "x = 10\n";
    else
        std::cout << "x != 10\n";

    std::cout << "x = " << x << '\n'; // x == 999 here

    switch (int x = 20; x) // C++17
    {
    case 10:
        std::cout << "x = 10\n";
        break;
    case 20:
        std::cout << "x = 20\n";
        break;
    }

    std::cout << "x = " << x << '\n'; // x == 999 here
}