#include <iostream>
#include <set>
#include "nutility.hpp"
#include "date.hpp"

template <typename Container, typename Func>
void fill_set(Container &c, std::size_t n, Func f)
{
    while (c.size() < n)
        c.insert(f());
}

template <typename Container>
void print_set(const Container &c, const char *delim = " ")
{
    for (const auto &val : c)
        std::cout << val << delim;

    std::cout << "\n---------------------------------------------------\n";
}

int main()
{
    std::set<std::string> myset;
    fill_set(myset, 20, rname);
    print_set(myset);

    std::string old_name, new_name;
    std::cout << "Eski ve yeni anahtarlari giriniz: ";
    std::cin >> old_name >> new_name;

    // C++17 oncesi yontem
    if (auto iter = myset.find(old_name); iter != myset.end())
    {
        myset.erase(iter);
        myset.insert(new_name);
        std::cout << old_name << " ismi " << new_name << " ismine degistirildi.\n";
        print_set(myset);
    }
    else 
        std::cout << "anahtar bulunamadi.\n";


}