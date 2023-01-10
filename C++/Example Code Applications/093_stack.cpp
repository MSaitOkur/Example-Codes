#include <iostream>
#include <stack>
#include "date.hpp"

int main()
{
    std::stack<Date> mystack;

    for (size_t i = 0; i < 5; ++i)
    {
        auto d = Date::random_date();
        std::cout << d << " was inserted to stack.\n";
        mystack.push(d);
    }

    std::cout << "Yiginda " << mystack.size() << " tane oge var\n";
    std::cout << "Yigindan degerler aliniyor.\n";

    while (!mystack.empty())
    {
        std::cout << mystack.top() << " ogesi stackden cikarildi\n";
        mystack.pop();
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

