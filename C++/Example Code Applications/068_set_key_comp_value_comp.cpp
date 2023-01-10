#include <iostream>
#include <set>

int main()
{
    std::set<int> iset{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "typeid(iset.key_comp()).name()   = " << typeid(iset.key_comp()).name() << '\n';
    std::cout << "typeid(iset.value_comp()).name() = " << typeid(iset.value_comp()).name() << '\n';

    std::cout << "iset.key_comp()(3,4) = " << iset.key_comp()(3,4) << '\n';

}