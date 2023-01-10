
#include <iostream>
#include <string>
#include <map>
#include "nutility.hpp"
#include <iomanip>
#include "date.hpp"

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

template <typename T1, typename T2>
void print_multimap(const std::multimap<T1, T2> &s, const char *delim = "\n")
{
    for (const auto &[t1, t2] : s)
        std::cout << std::setw(15) << t1 << " " << std::setw(15) << t2 << delim;
}

int main()
{
    std::multimap<std::string, Date> mymap;
    fill_map(mymap, 100, []
             { return std::make_pair(rname(), Date::random_date()); });
    print_multimap(mymap);

    std::string name;
    std::cout << "aranan ismi giriniz: ";
    std::cin >> name;

    auto [iter_lower, iter_upper] = mymap.equal_range(name);

    while (iter_lower != iter_upper)
    {
        std::cout << iter_lower->first << " " << iter_lower->second << "\n";
        ++iter_lower;
    }

}