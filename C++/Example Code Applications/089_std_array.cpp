#include <iostream>
#include <array>

int main()
{
    std::array<int, 5> arx;
    std::array<int, 4> ary;

    std::cout << std::boolalpha << (typeid(arx) == typeid(ary)) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <array>
#include <string>

template <typename T, std::size_t n>
std::ostream &operator<<(std::ostream &os, const std::array<T, n> &ar)
{
    os << "[";
    for (std::size_t i = 0; i < n - 1; ++i)
        os << ar[i] << ", ";

    return os << ar.back() << "]";
}

int main()
{
    std::array<int, 5> ari{0, 1, 2, 3, 4};
    std::array<std::string, 5> arstr{"ali", "serdar", "murat", "mustafa", "hamdi"};

    std::cout << ari << "\n"
              << arstr << "\n";
}