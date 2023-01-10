#include <iostream>
#include <unordered_set>
#include "date.hpp"

namespace std
{
    // std::hash sinifinin Date turu icin explicit specialization
    template <>
    struct hash<Date>
    {
        size_t operator()(const Date &date)
        {
            return hash<int>{}(date.get_month_day() + date.get_month() + date.get_year() + date.get_year_day());
        }
    };
}

struct date_hasher
{
    size_t operator()(const Date &date)
    {
        return std::hash<int>{}(date.get_month_day() + date.get_month() + date.get_year() + date.get_year_day());
    }
};

int main()
{
    auto dhasher = [](const Date &date)
    {
        return std::hash<int>{}(date.get_month_day() + date.get_month() + date.get_year() + date.get_year_day());
    };

    std::unordered_set<Date, std::hash<Date>> duset1(100);
    std::unordered_set<Date, date_hasher> duset2(100);

    std::unordered_set<Date, decltype(dhasher)> duset3(100, dhasher); // Before C++20
    std::unordered_set<Date, decltype(dhasher)> duset4(100);          // With C++20

    for (Date d;;)
    {
        std::cout << "tarih giriniz: ";
        std::cin >> d;
        std::cout << "Hash(" << d << ") = " << std::hash<Date>{}(d) << "\n";
        std::cout << "Hash(" << d << ") = " << date_hasher{}(d) << "\n";
        std::cout << "Hash(" << d << ") = " << dhasher(d) << "\n";
    }
}