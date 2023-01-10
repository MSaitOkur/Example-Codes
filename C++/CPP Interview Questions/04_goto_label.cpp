#include <iostream>

class A
{
public:
    A() { std::cout << "a"; }
    ~A() { std::cout << "A"; }
};

int i{1};

int main()
{
label:
    A a;
    if (i--)
        goto label;
}
// aAaA
// goto ile geriye donuslerde nesnenin scope'u bitmis muamelesi gorulur
