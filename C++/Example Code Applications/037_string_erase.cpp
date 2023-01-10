#include <string>
#include <iostream>
#include <algorithm>

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

    // Yazının ilk karakterini silin.
    // s.erase(s.begin());
    // s.erase(0, 1);

    // Yazının son karakterini silin.
    // s.erase(s.end() - 1);
    // s.erase(s.size() - 1, 1);

    // Yazının ilk ve son karakterleri dışında tüm karakterlerini silin.
    // s.erase(s.begin() + 1, s.end() - 1);

    // Yazının ikinci karakterini silin.
    // s.erase(s.begin() + 1);

    // Yazının sondan ikinci karakterini silin.
    // s.erase(s.end() - 2);

    // idx yazının geçerli bir indeksi olmak üzere yazının idx indisli karakterini silin.
    // s.erase(s.begin() + 5);

    // Yazıdaki ilk a karakterini silin.
    // s.erase(s.begin() + s.find('a'));

    // Yazıdaki son a karakterini silin.
    // s.erase(s.begin() + s.rfind('a'));

    // Yazıdaki tüm a karakterlerini silin.
    // std::size_t pos;
    // while ((pos = s.find('a')) != std::string::npos)
    //     s.erase(s.begin() + pos);

    // Yazıdaki ilk a karakteri ile başlayan ve son a karakteri ile biten yazıyı silin.
    // s.erase(s.begin() + s.find('a'), s.begin() + s.rfind('a') + 1);

    // Yazıdaki ilk a karakterinden önce gelen ve sonra gelen 2 karakteri silin.
    // s.erase(s.erase(s.begin() + s.find('a') - 1) + 1);

    // Yazıda bulunan ilk "kan" yazısını silin
    // s.erase(s.find("kan"), 3);

    // Yazıda bulunan son "kan" yazısını silin
    // s.erase(s.rfind("kan"), 3);

    // Yazıda bulunan tüm "kan" yazılarını silin
    // for (std::size_t pos; (pos = s.find("kan")) != std::string::npos;)
    //     s.erase(pos, 3);

    // Yazıda bulunan ilk rakam karakterini silin
    // s.erase(s.find_first_of("0123456789"), 1);

    // Yazıda bulunan son rakam karakterini silin
    // s.erase(s.find_last_of("0123456789"), 1);

    // Yazıdaki tüm rakam karakterlerini silin.
    // for(std::size_t pos; (pos = s.find_first_of("0123456789")) != std::string::npos;)
    //     s.erase(pos,1);

    // Yazının uzunluğu 1'den büyükse ve yazının ilk karakteri ile son
    // karakteri aynı ise bunları silin.
    // if (s.size() > 1 && s[0] == s[s.size() - 1])
    // {
    //     s.erase(s.begin());
    //     s.erase(s.end() - 1);
    // }

    // Yazının uzunluğu 5'ten büyükse ve yazının ilk 3 karakteri ile
    // son 3 karakteri aynı ise bunları silin.
    // if (s.size() > 5 && s.substr(0, 3) == s.substr(s.size() - 3, 3))
    // {
    //     s.erase(0, 3);
    //     s.erase(s.size() - 3);
    // }

    // Yazıdaki ardışık eşit karakterlerden sadece bir tane kalacak
    // şekilde silme işlemi yapın. (unique)
    // s.erase(std::unique(s.begin(), s.end()), s.end());

    // Yazıdaki tüm boşluk (whitespace) karakterlerini silin.
    // for (std::size_t pos; (pos = s.find_first_of(" \t\f\n\r\v")) != std::string::npos;)
    //     s.erase(pos, 1);

    print(s);
}
