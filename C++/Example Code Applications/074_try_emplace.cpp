#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include "nutility.hpp"

using name = std::string;
using count = int;

template <typename Container, typename Func>
void fill_map(Container &c, std::size_t sz, Func f)
{
    while (c.size() < sz)
        c.insert(c.end(), f());
}

template <typename Container>
void print_map(const Container &c, const char *delim = "\n")
{
    std::cout << "\n------------------------------------------------------\n";
    for (const auto &[f, s] : c)
        std::cout << std::setw(12) << f << "  " << std::setw(12) << s << delim;
    std::cout << "------------------------------------------------------\n";
}

int main()
{
    std::map<name, count> mymap;
    fill_map(mymap, 10, []
             { return std::make_pair(rname(), Irand{0, 100}()); });
    print_map(mymap);

    std::string name;
    int val;
    std::cout << "Eklenecek ismi ve numarayi giriniz: ";
    std::cin >> name >> val;

    if (auto result = mymap.try_emplace(name, val); result.second)
    {
        std::cout << "Ekleme islemi basarili oldu.\n";
        std::cout << "Ekleme yapilan konum : " << std::distance(mymap.begin(), result.first) << "\n";
        std::cout << "Eklenen ogenin degeri : " << val << "\n";
    }
    else
    {
        std::cout << "Ekleme islemi basarisiz oldu.\n";
        std::cout << "Mapdeki ogenin konumu : " << std::distance(mymap.begin(), result.first) << "\n";
        std::cout << "Mapdeki ogenin degeri : " << result.first.operator*().second << "\n";
    }
    print_map(mymap);
}
