#include <string>
#include <iostream>

void print(const std::string &s)
{
    std::cout << "'" << s << "' [" << s.length() << "]\n";
}

int main()
{
    std::string s;

    std::cout << "bir yazi giriniz: ";
    std::getline(std::cin, s);
    print(s);

    // Yazının başına 'X' karakterini ekleyin.
    s.insert(s.begin(), 'X');

    // Yazının sonuna 'X' karakterini ekleyin.
    s.push_back('X');

    // Yazıya 'W' karakterini yazının 3 indeksli karakteri olacak biçimde ekleyin.
    s.insert(s.begin() + 3, 'W');

    // Yazının başına "kendi isminizi" ekleyin.
    s.insert(0, "SAIT");

    // Yazının sonuna "kendi isminizi" ekleyin.
    s.insert(s.size(), "SAIT");

    // Yazının sonuna yazının uzunluğunu ekleyin: necati ----> necati6
    s.insert(s.size(), std::to_string(s.size()));

    // Yazıda bulunan rakam karakterlerinden bir tane daha ekleyin: a4b71p9eak23t ----> a44b7711p99eak2233t
    for (std::size_t i = 0; i < s.size();)
    {
        if (std::isdigit(s[i]))
        {
            s.insert(i, 1, s[i]);
            i += 2;
        }
        else
            ++i;
    }

    print(s);
}