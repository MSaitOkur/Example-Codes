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

    std::string old_name, new_name;
    std::cout << "eski ve yeni isimleri giriniz: ";
    std::cin >> old_name >> new_name;

    // if (auto iter = mymap.find(old_name); iter != mymap.end())
    // {
    //     std::cout << "bulundu\n";
    //     auto val = iter->second;
    //     mymap.erase(iter);
    //     mymap.insert({new_name, val});
    //     print_map(mymap);
    // }
    // else
    //     std::cout << "bulunamadi\n";

    if (auto node_handle = mymap.extract(old_name); node_handle)
    {
        node_handle.key() = new_name;
        mymap.insert(std::move(node_handle));
        print_map(mymap);
    }
    else
        std::cout << "bulunamadi\n";
}
