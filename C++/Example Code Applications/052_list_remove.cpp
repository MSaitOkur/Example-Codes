#include <iostream>
#include <list>
#include <string>
#include "nutility.hpp"
#include <functional>
#include <iterator>

int main()
{
    std::list<int> li;
    while (li.size() < 100)
        li.push_back([]()
                     { return rand() % 6; }());

    std::cout << "li.size() = " << li.size() << '\n';

    std::copy(li.begin(), li.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << sl;

    // li.remove(5);
    li.remove_if([](int val)
                 { return val % 5 == 0; });

    std::cout << "li.size() = " << li.size() << '\n';

    std::copy(li.begin(), li.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << sl;
}