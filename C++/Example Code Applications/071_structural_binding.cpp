#include <iostream>

struct Data
{
    int x;
    int a[10];
};

Data foo();

int main()
{
    auto [i, p] = foo();
    // p pointer degil 10 elemanli dizinin turu, int[10]

    std::cout << std::boolalpha;
    std::cout << "typeid(p) == typeid(int[10]) = " << (typeid(p) == typeid(int[10])) << '\n';
    std::cout << "typeid(p) == typeid(int*)    = " << (typeid(p) == typeid(int *)) << '\n';
}
