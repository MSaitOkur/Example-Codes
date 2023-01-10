#include <iostream>
#include <initializer_list>

class C
{
public:
    C() = default;
    C(const C &) { std::cout << 1; }
};

void f(std::initializer_list<C>) {}

int main()
{
    C c;
    std::initializer_list<C> i{c};
    f(i);
    f(i);
}

// Burada ekrana yazilan 1 16. satirdan.
// Fonksiyon cagrilarinda ekrana birsey yazilmamasinin sebebi ise
// initializer_list icin derleyici arka planda bir const dizi olusturuyor.
// parametreye gonderilen arguman ise call by value gibi gorunse de call
// by reference oluyor. Dolayisiyla burada kopyalama islemi yok.
// parametreler icin nesneler hayata getirilmiyor.
