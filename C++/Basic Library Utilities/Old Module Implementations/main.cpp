#include <string>
#include <iostream>
#include <cctype>

int main()
{
    std::string name{"Mehmet Aksu"};

    for (auto c : name)
    {
        std::cout << c << " ";
        c = std::toupper(c); // nesne değişmez
    }

    std::cout << "[" << name.length() << "] [" << name << "]\n";

    for (auto &c : name)
    {
        std::cout << c << " ";
        c = std::toupper(c); // nesne değişir
    }

    std::cout << "[" << name.length() << "] [" << name << "]\n";

    // for (const auto &c : name)
    // {
    //     std::cout << c << " ";
    //     c = std::toupper(c); // nesneyi set etme geçersiz
    // }

    // std::cout << "[" << name.length() << "] [" << name << "]\n";
}