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

// template <typename Container>
// void print_map(const Container &c, const char *delim = "\n")
// {
//     for (const auto &[f, s] : c)
//         std::cout << std::setw(12) << f << "  " << std::setw(12) << s << delim;
// }

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p)
{
    return os << std::setw(15) << p.first << "   " << std::setw(15) << p.second;
}
template <typename Container>
void print_map(const Container &c, const char *delim = "\n")
{
    std::cout << "\n------------------------------------------------------\n";
    for (const auto &p : c)
        std::cout << p << delim;
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
    std::cout << "isim ve numara giriniz: ";
    std::cin >> name >> val;

    try
    {
        mymap.at(name) = val;
        // name varsa degeri val olarak set edilecek
        // name yoksa exception throw edilecek
    }
    catch (const std::exception &e)
    {
        std::cout << "hata yakalandi: " << e.what() << "\n";
        std::cout << name << "'in degeri map::at ile elde edilemedi.\n";
    }

    mymap[name] = val;
    // name varsa degeri val olarak set edilecek
    // name yoksa map'e eklenecek ve degeri val olacak

    std::cout << name << " [] ile " << val << " degeri set edilerek map'e eklendi\n";

    print_map(mymap);
}
