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

    if (auto iter = myset.find(old_name); iter != myset.end())
    {
        // std::set<std::string>::node_type handle = myset.extract(old_name);
        auto handle = myset.extract(old_name);

        std::cout << old_name << " extract edildi, myset.size() = " << myset.size() << '\n';

        handle.value() = new_name;
        std::cout << old_name << " ismi " << new_name << " ismine degistirildi.\n";

        myset.insert(std::move(handle));
        std::cout << new_name << " insert edildi, myset.size() = " << myset.size() << "\n";
    }
    else
        std::cout << old_name << " bulunamadi\n";

    print_set(myset);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

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
    std::set<std::string> male_names{"ali", "murat", "fatih", "osman", "serdar", "deniz"};
    std::set<std::string> female_names{"aliye", "mevlude", "seda", "sevgi", "esra"};

    print_set(male_names);
    print_set(female_names);


    if (auto handle = male_names.extract("deniz"); !handle.empty())
    {
        female_names.insert(std::move(handle));
        print_set(male_names);
        print_set(female_names);
    }
}
