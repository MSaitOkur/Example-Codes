#include <iostream>
#include <string>
#include <forward_list>
#include "nutility.hpp"
#include <iterator>
#include <algorithm>

template <typename T>
void print_forward_list(const std::forward_list<T> &flist)
{
    for (const auto &fl : flist)
        std::cout << fl << " ";
    std::cout << sl;
}

int main()
{
    std::forward_list<std::string> flist;
    while (std::distance(flist.begin(), flist.end()) < 8)
        flist.push_front(rname());

    print_forward_list(flist);

    std::cout << "Silinecek ismi giriniz: ";
    std::string name;
    std::cin >> name;

    // Wrong code for specific erase operation at certain element
    // auto iter = std::find(flist.begin(), flist.end(), name);
    // if (iter != flist.end())
    //     flist.erase_after(iter);

    auto iter_before = flist.before_begin();
    auto iter_at = flist.begin();
    for (; iter_at != flist.end(); ++iter_at, ++iter_before)
        if (*iter_at == name)
            break;

    if (iter_at != flist.end())
    {
        std::cout << "bulundu...\n";
        flist.erase_after(iter_before);
    }
    else
        std::cout << "Bulunamadi...\n";

    print_forward_list(flist);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <string>
#include <forward_list>
#include "nutility.hpp"
#include <iterator>
#include <algorithm>

template <typename T>
void print_forward_list(const std::forward_list<T> &flist)
{
    for (const auto &fl : flist)
        std::cout << fl << " ";
    std::cout << sl;
}

int main()
{
    std::forward_list<std::string> flist;
    while (std::distance(flist.begin(), flist.end()) < 8)
        flist.push_front(rname());

    print_forward_list(flist);

    std::cout << "Silinecek ismi giriniz: ";
    std::string name;
    std::cin >> name;

    auto iter = flist.before_begin();
    for (; std::next(iter) != flist.end(); ++iter)
        if (*std::next(iter) == name)
        {
            flist.erase_after(iter);
            break;
        }

    if (std::next(iter) != flist.end())
    {
        std::cout << name << " bulundu ve silindi...\n";
        print_forward_list(flist);
    }
    else
        std::cout << name << " ismi bulunamadi...\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <string>
#include <forward_list>
#include "nutility.hpp"
#include <iterator>
#include <algorithm>

template <typename T>
void print_forward_list(const std::forward_list<T> &flist)
{
    for (const auto &fl : flist)
        std::cout << fl << " ";
    std::cout << sl;
}

template <typename T>
bool remove_value(std::forward_list<T> &flist, const T &val)
{

    for (auto iter = flist.before_begin(); std::next(iter) != flist.end(); ++iter)
        if (*std::next(iter) == val)
        {
            flist.erase_after(iter);
            return true;
        }

    return false;
}

int main()
{
    std::forward_list<std::string> flist;
    while (std::distance(flist.begin(), flist.end()) < 8)
        flist.push_front(rname());

    print_forward_list(flist);

    std::cout << "Silinecek ismi giriniz: ";
    std::string name;
    std::cin >> name;

    if (remove_value(flist, name))
    {
        std::cout << name << " bulundu ve silindi...\n";
        print_forward_list(flist);
    }
    else
        std::cout << name << " ismi bulunamadi...\n";
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <iostream>
#include <string>
#include <forward_list>
#include "nutility.hpp"
#include <iterator>
#include <algorithm>

template <typename T, typename Func>
void fill_forward_list(std::forward_list<T> &flist, std::size_t size, Func f)
{
    for (std::size_t i = 0; i < size; ++i)
        flist.push_front(f());
}

template <typename T>
void print_forward_list(const std::forward_list<T> &flist)
{
    for (const auto &fl : flist)
        std::cout << fl << " ";
    std::cout << sl;
}

template <typename T>
bool remove_value(std::forward_list<T> &flist, const T &val)
{

    for (auto iter = flist.before_begin(); std::next(iter) != flist.end(); ++iter)
        if (*std::next(iter) == val)
        {
            flist.erase_after(iter);
            return true;
        }

    return false;
}

int main()
{
    std::forward_list<std::string> flist;
    fill_forward_list(flist, 10, rname);
    print_forward_list(flist);

    std::cout << "Silinecek ismi giriniz: ";
    std::string name;
    std::cin >> name;

    if (remove_value(flist, name))
    {
        std::cout << name << " bulundu ve silindi...\n";
        print_forward_list(flist);
    }
    else
        std::cout << name << " ismi bulunamadi...\n";
}