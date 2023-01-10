#include <iostream>

void f() { std::cout << 1; }

template <typename T>
struct B
{
    void f() { std::cout << 2; }
};

template <typename T>
struct D : B<T>
{
    void g() { f(); }
};

int main()
{
    D<int> d;
    d.g();
}

// Burada ekrana 1 yazilmasinin sebebi taban sinifin bir template olmasindan
// dolayi, turemis sinif icerisinde taban sinifa ait isimler nitelenmeden
// kullanilirsa bu durumda bu isimler taban sinif icerisinde aranilmaz.
// Eger taban sinin template olmasaydi ekrana 2 yazilacaktir.
