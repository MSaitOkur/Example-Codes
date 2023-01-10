#include <iostream>
#include <string>
#include <map>
#include "nutility.hpp"
#include <iomanip>

template <typename Container, typename Func>
void fill_map(Container &c, std::size_t n, Func f)
{
    while (c.size() < n)
        c.insert(c.end(), f());
}

template <typename T1, typename T2>
void print_map(const std::map<T1, T2> &s, const char *delim = "\n")
{
    for (const auto &[t1, t2] : s)
        std::cout << std::setw(15) << t1 << " " << std::setw(15) << t2 << delim;
}

int main()
{
    std::map<std::string, int> mymap;
    fill_map(mymap, 100, []
             { return std::make_pair(rname(), Irand{0, 100}()); });
    print_map(mymap);

    std::string name;
    std::cout << "aranan ismi giriniz: ";
    std::cin >> name;

    if (auto iter = mymap.find(name); iter != mymap.end())
        std::cout << name << " isimli kisinin numarasi = " << iter->second << "\n";
    else
        std::cout << "bulunamadi\n";
}