//?????????????????????????
#include <iostream>

struct S
{
};

template <typename T>
void adl(T t)
{
    std::cout << "T";
}

template <typename T>
void call_adl(T t)
{
    adl(S());
    adl(t);
}

void adl(S)
{
    std::cout << "S";
}

int main()
{
    call_adl(S());
}
