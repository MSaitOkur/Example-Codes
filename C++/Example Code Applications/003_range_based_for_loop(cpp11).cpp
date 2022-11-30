#include <iostream>

int main()
{
    int ar[5] = {0};

    for (int val : ar)
        ++val;

    for (size_t i = 0; i < 5; ++i)
        std::cout << ar[i] << ' ';
    std::cout << "\n";

    for (int &val : ar)
        ++val;

    for (size_t i = 0; i < 5; ++i)
        std::cout << ar[i] << ' ';
    std::cout << "\n";
}