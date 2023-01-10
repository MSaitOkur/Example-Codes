
#include <iostream>

// Bir tam sayının bir tam sayı kuvvetini hesaplayacak Power isimli meta fonksiyonu yazınız.
// constexpr int x = Power<2, 5>::value; //x = 32
template <int base, int pow>
struct Power
{
    constexpr static int value = base * Power<base, pow - 1>::value;
};
template <int base>
struct Power<base, 0>
{
    constexpr static int value = 1;
};

// power_v isimli bir değişken şablonu (variable template) oluşturunuz.
// constexpr int y = power_v<3, 5>;
template <int base, int pow>
constexpr int Power_v = Power<base, pow>::value;

// Bir tam sayının faktöriyel değerini hesaplayacak Factorial isimli meta fonksiyonu yazınız.
// Sınıfın constexpr value isimli öğesi hesaplanacak faktöriyel değeri olacak:
// constexpr int x = Factorial<5>::value; //x = 120
template <int fact>
struct Factorial
{
    constexpr static int value = fact * Factorial<fact - 1>::value;
};
template <>
struct Factorial<1>
{
    constexpr static int value = 1;
};

// factorial_v isimli bir değişken şablonu (variable template) oluşturunuz.
// constexpr int y = factorial_v<7>;
template <int fact>
constexpr int Factorial_v = Factorial<fact>::value;

int main()
{
    constexpr int x1 = Power<2, 5>::value;
    constexpr int x2 = Power_v<2, 5>;

    std::cout << x1 << '\n';
    std::cout << x2 << '\n';

    constexpr int f1 = Factorial<10>::value;
    constexpr int f2 = Factorial_v<5>;

    std::cout << f1 << '\n';
    std::cout << f2 << '\n';
}
