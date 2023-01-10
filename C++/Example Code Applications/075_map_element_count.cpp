#include <iostream>
#include <vector>
#include <map>
#include "nutility.hpp"
#include <iomanip>
#include <algorithm>

template <typename Container, typename Func>
void fill_container(Container &c, std::size_t n, Func f)
{
    for (std::size_t i = 0; i < n; ++i)
        c.insert(c.end(), f());
}

template <typename Container>
void print_container(const Container &c, const char *delim = " ")
{
    std::cout << "\n-----------------------------------------------\n";

    for (const auto &val : c)
        std::cout << val << delim;

    std::cout << "\n-----------------------------------------------\n";
}

using svector = std::vector<std::string>;

int main()
{
    // Vectordeki isimlerin sayisini buyukten kucuge olacak sekilde siralayiniz.
    svector svec;
    fill_container(svec, 10000, rname);
    print_container(svec);

    std::map<std::string, int> scmap;
    for (const auto &name : svec)
        ++scmap[name]; 
    
    // Simdi kucukten buyuge dogru sirali bir sekilde pair olarak vectore kaydettik
    std::vector<std::pair<std::string, int>> pairvec{scmap.begin(), scmap.end()}; 
    
    // Isimlerin sayisini buyukten kucuge dogru siraladik
    std::sort(pairvec.begin(), pairvec.end(),
              [](const auto &p1, const auto &p2)
              { return p1.second > p2.second; });

    print_container(pairvec, "\n");
}