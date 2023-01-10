#include <iostream>
#include <tuple>
#include <string>
#include "date.hpp"

int main()
{
    std::tuple<int, Date, std::string> tx; // Default initialization
    // class turleri default initialize edilirler
    // primitive turler ise 0 degeri ile hayata baslarlar.
    // bu garanti altindadir.

    std::cout << std::get<0>(tx) << "\n";
    std::cout << std::get<1>(tx) << "\n";
    std::cout << std::get<2>(tx).size() << "\n";
    std::cout << std::get<3>(tx) << "\n"; // invalid, 3 indisli oge yok, compile time error
    
    // get interface'inde elemanlara erisim icin kullanilacak index degeri sabit ifadesi olmalidir.
    int x = 2;
    std::cout << std::get<x>(tx) << "\n"; // error

}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include "date.hpp"

int main()
{
    std::tuple<int, Date, std::string> tx;

    // get interface'i elemanlari referans olarak dondurmektedir.
    std::get<0>(tx) = 45;
    ++std::get<1>(tx);
    std::get<2>(tx) = "Murat";

    std::cout << std::get<0>(tx) << "\n";
    std::cout << std::get<1>(tx) << "\n";
    std::cout << std::get<2>(tx)  << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------


#include <iostream>
#include <tuple>
#include <string>
#include "date.hpp"

int main()
{
    std::tuple<int, Date, std::string, std::string> tx;

    // C++2017 ile get interface'inde tur ismi ile elemana erisim imkanida vardir.
    // Bu sentaks ile kullanimda ayni turden birden fazla varsa sentaks hatasi olur.
    std::get<int>(tx) = 45;
    ++std::get<Date>(tx);
    std::get<std::string>(tx) = "Murat"; // error
    std::get<3>(tx) = "Murat"; // valid

    std::cout << std::get<0>(tx) << "\n";
    std::cout << std::get<1>(tx) << "\n";
    std::cout << std::get<2>(tx) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>

using age = int;
using wage = double;
using name = std::string;

int main()
{

    // tur esisim bildirimleri ile kod okumasi, yazmasi kolaylastirilmaktadir.
    std::tuple<age, wage, name> tx{35, 324, "Mustafa"};

    std::cout << std::get<name>(tx) << "\n";
    std::cout << std::get<age>(tx) << "\n";
    std::cout << std::get<wage>(tx) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>

using age = int;
using wage = double;
using name = std::string;

int main()
{
    auto tx{std::make_tuple(45, 1000., std::string{"Ahmet"})};

    std::cout << std::get<name>(tx) << "\n";
    std::cout << std::get<age>(tx) << "\n";
    std::cout << std::get<wage>(tx) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include <functional>

using age = int;
using wage = double;
using name = std::string;

int main()
{
    std::string s{"Ahmet"};
    int x = 23;
    double dval = 2.56;

    auto tx{std::make_tuple(x, dval, s)};

    std::get<0>(tx) += 10;
    std::get<2>(tx) += "can";

    std::cout << std::get<name>(tx) << "\n";
    std::cout << std::get<age>(tx) << "\n";
    std::cout << std::get<wage>(tx) << "\n";

    // reference_wrapper sinifi ile kullanimi da yaygindir.
    auto reftx = std::make_tuple(std::ref(x), std::ref(dval), std::ref(s));

    std::get<0>(reftx) += 10;
    std::get<2>(reftx) += "can";

    std::cout << std::get<0>(reftx) << "\n";
    std::cout << std::get<1>(reftx) << "\n";
    std::cout << std::get<2>(reftx) << "\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include <functional>

std::tuple<int, std::string, double> func()
{
    //...
    return {12, "Ali", 23.4};
}

int main()
{
    auto tx = func();
    int a1 = std::get<int>(tx);
    std::string str1 = std::get<std::string>(tx);
    double dval1 = std::get<double>(tx);

    //----------------------------

    int a2;
    std::string str2;
    double dval2;

    // tie fonksiyonu bind edilen nesnelerin referanslari ile bir tuple olusturur.
    // Ancak bu da verimsiz bir yontemdir. Cunku once nesnelerin olusturulmasi gerekmektedir.
    std::tie(a2, str2, dval2) = func();
    // std::tuple<int &, std::string &, double &>{a2, str2, dval2} = func();

    //----------------------------

    // return degeri tuple olan fonksiyonlar icin en kullanisli yontem 
    // structural binding isimli aractir. Burada nesneler hayata tuple nesnesinin
    // karsilikli elemanlari ile ilk deger verilerek hayata getiriliyorlar
    auto [age, name, wage] = func();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include <functional>

std::tuple<int, std::string, double> func()
{
    //...
    return {12, "Ali", 23.4};
}

int main()
{
    int a;
    std::string str;
    double dval;

    auto t{std::tie(a, str, dval) = func()};

    ++std::get<0>(t);
    std::get<1>(t) += "can";
    std::get<2>(t) *= 2.54;

    std::cout << "a = " << a << '\n';
    std::cout << "str = " << str << '\n';
    std::cout << "dval = " << dval << '\n';
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include <functional>

std::tuple<int, std::string, double> func()
{
    //...
    return {12, "Ali", 23.4};
}

int main()
{
    /* tie fonksiyonunun structural binding'ten daha avantajli oldugu bir nokta vardir.
     * Eger bir tuple nesnesinin butun elemanlari kullanilmak istenmiyorsa sadece ihtiyac
     * olunan kismi kullanilmak isteniliyorsa bu dogrudan structural binding ile olmaz. Cunku
     * tuple'nin butun elemanlari [] icindeki elemanlara atanmalidir.
     * Yani [] icinde her eleman icin bir nesne bulunmalidir.
     * Ancak bu durumda tie bu imkani bize saglar.
     * ignore_t turunden olan ve her turlu nesne ile kendisine atama yapilabilen ignore nesnesi tie
     * icinde kullanildiginda ilgili tuple elemani ignore edilebilmektedir.
     */

    std::string name;

    // auto [name] = func();                           // error
    // auto [, name, ] = func();                       // error
    // auto [std::ignore, name, std::ignore] = func(); // error

    auto t{std::tie(std::ignore, name, std::ignore) = func()}; // valid

    std::get<1>(t) += "can";

    std::cout << "name = " << name << '\n';
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include <functional>

class Data
{
public:
    bool operator<(const Data &d) const
    {
        // return mi < d.mi || (mi == d.mi && md < d.md) ||
        //        (mi == d.mi && md == d.md && ms < d.ms);

        // yukaridaki cok kod yazmak yerine asagidaki yontem daha kullanislidir ve
        // ayni amaci implemente etmektedir.
        return std::tie(mi, md, ms) < std::tie(d.mi, d.md, d.ms);
    }

private:
    int mi;
    double md;
    std::string ms;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>
#include <functional>
#include <vector>
#include "date.hpp"
#include "nutility.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>

using age = int;
using name = std::string;
using surname = std::string;
using town = std::string;
using bdate = Date;
using info = std::tuple<age, name, surname, town, bdate>;

int main()
{
    std::vector<info> vec;
    for (std::size_t i = 0; i < 500000; ++i)
        vec.emplace_back(rand() % 120 + 1, rname(), rfname(), rtown(), Date::random_date());

    std::sort(vec.begin(), vec.end());

    std::ofstream ofs{"out.txt"};
    if (!ofs)
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        std::exit(EXIT_FAILURE);
    }

    ofs << std::left;
    for (const auto &[age_, name_, surname_, town_, bdate_] : vec)
    {
        using namespace std;
        ofs << setw(4) << age_ << setw(16) << name_ << setw(16) << surname_
            << setw(16) << town_ <<  bdate_ << '\n';
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
