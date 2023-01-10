#include <iostream>
#include <unordered_set>

int main()
{
    for (int key;;)
    {
        std::cout << "Key degeri giriniz: ";
        std::cin >> key;
        std::cout << "Hash(" << key << ") = " << std::hash<int>{}(key) << "\n";
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <unordered_set>
#include <string>

int main()
{
    for (std::string key;;)
    {
        std::cout << "isim giriniz: ";
        std::cin >> key;
        std::cout << "Hash(" << key << ") = " << std::hash<std::string>{}(key) << "\n";
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

