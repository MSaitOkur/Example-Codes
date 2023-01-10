#include <iostream>
#include <utility>

struct X
{
    X() { std::cout << "1"; }
    X(X &) { std::cout << "2"; }
    X(const X &) { std::cout << "3"; }
    X(X &&) { std::cout << "24"; }
    ~X() { std::cout << "5"; }
};

struct Y
{
    mutable X x;
    Y() = default;
    Y(const Y &) = default;
};

int main()
{
    Y y1;
    Y y2 = std::move(y1);
}






// oncelikle move ctor yok. dolayisiyla copy ctor cagrilacak.
// 3 yerine 2'nin cagrilma sebebi ise
// Y icindeki X'in mutable olarak belirtilmesidir.