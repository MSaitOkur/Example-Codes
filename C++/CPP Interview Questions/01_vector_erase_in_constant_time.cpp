#include <iostream>
#include <vector>
#include <string>
#include "nutility.hpp"

using svector = std::vector<std::string>;

int main()
{
    svector svec;
    fc(svec, 10, rname);
    pc(svec);

    std::size_t pos;
    std::cout << "silinecek ogenin konumunu giriniz: ";
    std::cin >> pos;

    // svec'teki pos konumundaki ogeyi sabit zamanda siliniz.

    // solution :
    // vectorde ogelere index ile erisim sabit zamandadir.
    // vectorde ilk ve son konumdaki ogeleri silmek sabit zamandadir.
    std::swap(svec[pos], svec.back());
    svec.pop_back();

    pc(svec);
}
