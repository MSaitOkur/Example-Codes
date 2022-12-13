#include "date.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

int Date::dayLookup[2][13] = {[0] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                              [1] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

const char *BadDate::what() const noexcept
{
    return "Invalid Date!...";
}

bool Date::isValidDate(int d, int m, int y)
{
    return (y >= Date::year_base) && (m && m <= 12) &&
           (d && d <= Date::dayLookup[Date::isleap(y)][m]);
}

Date::Date(int d, int m, int y) : m_day{d}, m_mon{m}, m_year{y}
{
    if (!Date::isValidDate(d, m, y))
    {
        throw BadDate{};
    }
}

Date::Date(const char *p) : m_day{std::atoi(p)}, m_mon{std::atoi(p + 3)}, m_year{std::atoi(p + 6)}
{
    if (!Date::isValidDate(m_day, m_mon, m_year))
    {
        throw BadDate{};
    }
}

Date::Date(std::time_t timer) : m_day{std::localtime(&timer)->tm_mday},
                                m_mon{std::localtime(&timer)->tm_mon}, m_year{std::localtime(&timer)->tm_year} {}

Date Date::random_date()
{
    Date d;

    d.m_year = std::rand() % (Date::random_max_year - Date::random_min_year + 1) + Date::random_min_year;
    d.m_mon = std::rand() % 12 + 1;
    d.m_day = std::rand() % Date::dayLookup[Date::isleap(d.m_year)][d.m_mon] + 1;

    return d;
}
bool Date::isleap(int y)
{
    return !(y % 4) && (y % 100 || !(y % 400));
}

int Date::get_month_day() const
{
    return m_day;
}
int Date::get_month() const
{
    return m_mon;
}
int Date::get_year() const
{
    return m_year;
}
int Date::get_year_day() const
{
    int sum{};

    switch (this->m_mon)
    {
    case 12:
        sum += 30;
    case 11:
        sum += 31;
    case 10:
        sum += 30;
    case 9:
        sum += 31;
    case 8:
        sum += 31;
    case 7:
        sum += 30;
    case 6:
        sum += 31;
    case 5:
        sum += 30;
    case 4:
        sum += 31;
    case 3:
        sum += isleap(this->m_year) ? 29 : 28;
    case 2:
        sum += 31;
    case 1:
        sum += this->m_day;
    }

    return sum;
}
Date::Weekday Date::get_week_day() const
{
    static const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    int d = this->m_day;
    int m = this->m_mon;
    int y = this->m_year;

    y -= m < 3;

    return static_cast<Date::Weekday>((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
}

Date &Date::set_month_day(int day)
{
    if (!isValidDate(day, this->m_mon, this->m_year))
    {
        throw BadDate{};
    }

    this->m_day = day;
    return *this;
}
Date &Date::set_month(int month)
{
    if (!isValidDate(this->m_day, month, this->m_year))
    {
        throw BadDate{};
    }

    this->m_mon = month;
    return *this;
}
Date &Date::set_year(int year)
{
    if (!isValidDate(this->m_day, this->m_mon, year))
    {
        throw BadDate{};
    }

    this->m_year = year;
    return *this;
}
Date &Date::set(int day, int mon, int year)
{
    if (!isValidDate(day, mon, year))
    {
        throw BadDate{};
    }
    this->m_day = day;
    this->m_mon = mon;
    this->m_year = year;
    return *this;
}

Date &Date::operator+=(int day)
{
    auto mon_max = Date::dayLookup[Date::isleap(this->m_year)][this->m_mon];

    if (this->m_day + day <= mon_max)
        this->m_day += day;
    else if (this->m_mon <= 11)
    {
        this->m_mon += 1;
        this->m_day = this->m_day + day - mon_max;
    }
    else if (this->m_mon == 12)
    {
        this->m_year += 1;
        this->m_mon = 1;
        this->m_day = this->m_day + day - mon_max;
    }

    return *this;
}
Date &Date::operator-=(int day)
{
    auto prev_mon_max = this->m_mon == 1 ? 31 : Date::dayLookup[Date::isleap(this->m_year)][this->m_mon - 1];

    if (this->m_day > day)
        this->m_day -= day;
    else if (this->m_mon >= 2)
    {
        this->m_mon -= 1;
        this->m_day = this->m_day + prev_mon_max - day;
    }
    else if (this->m_mon == 1)
    {
        this->m_year -= 1;
        this->m_mon = 12;
        this->m_day = this->m_day + prev_mon_max - day;
    }

    return *this;
}
Date Date::operator-(int day) const
{
    auto d{*this};

    d -= day;

    return d;
}

Date &Date::operator++()
{
    return (*this) += 1;
}
Date Date::operator++(int)
{
    auto d = *this;
    ++(*this);
    return d;
}
Date &Date::operator--()
{
    return (*this) -= 1;
}
Date Date::operator--(int)
{
    auto d = *this;
    --(*this);
    return d;
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    static const char *const pdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    static const char *const pmonths[13] = {"", "January", "February", "March", "April", "May", "June", "July",
                                            "August", "September", "October", "November", "December"};

    return os << std::setw(2) << date.m_day << " " << std::setw(10) << pmonths[date.m_mon] << " "
              << std::setw(4) << date.m_year << " " << std::setw(12) << pdays[static_cast<int>(date.get_week_day())];
}
std::istream &operator>>(std::istream &is, Date &date)
{
    is >> date.m_day;
    std::getchar();
    is >> date.m_mon;
    std::getchar();
    return is >> date.m_year;
}

bool operator<(const Date &d1, const Date &d2)
{
    return d1.m_year < d2.m_year ? 1 : (d1.m_year == d2.m_year) && (d1.m_mon < d2.m_mon)                         ? 1
                                   : (d1.m_year == d2.m_year) && (d1.m_mon == d2.m_mon) && (d1.m_day < d2.m_day) ? 1
                                                                                                                 : 0;
}
bool operator<=(const Date &d1, const Date &d2)
{
    return !(d2 < d1);
}
bool operator==(const Date &d1, const Date &d2)
{
    return (d1.m_year == d2.m_year) && (d1.m_mon == d2.m_mon) && (d1.m_day == d2.m_day);
}
bool operator>(const Date &d1, const Date &d2)
{
    return d2 < d1;
}
bool operator>=(const Date &d1, const Date &d2)
{
    return !(d1 < d2);
}
bool operator!=(const Date &d1, const Date &d2)
{
    return d1 < d2 || d2 < d1;
}

int operator-(const Date &d1, const Date &d2)
{
    if (d1.get_year() - d2.get_year() == 0)
        return d1 > d2 ? d1.get_year_day() - d2.get_year_day() : d2.get_year_day() - d1.get_year_day();

    auto leap_count = 0;
    auto no_leap_count = 0;
    auto diffrence = 0;

    if (d1 > d2)
    {
        diffrence = d1.get_year_day() + (Date::isleap(d2.get_year()) ? 366 - d2.get_year_day() : 365 - d2.get_year_day());

        for (auto i = d2.get_year() + 1; i < d1.get_year(); ++i)
            if (Date::isleap(i))
                ++leap_count;
            else
                ++no_leap_count;
        return diffrence += leap_count * 366 + no_leap_count * 365;
    }

    diffrence = d2.get_year_day() + (Date::isleap(d1.get_year()) ? 366 - d1.get_year_day() : 365 - d1.get_year_day());

    for (auto i = d1.get_year() + 1; i < d2.get_year(); ++i)
        if (Date::isleap(i))
            ++leap_count;
        else
            ++no_leap_count;
    return diffrence += leap_count * 366 + no_leap_count * 365;
}

Date operator+(const Date &date, int n)
{
    auto d = date;
    d += n;
    return d;
}
Date operator+(int n, const Date &date)
{
    auto d = date;
    d += n;
    return d;
}

Date::Weekday &operator++(Date::Weekday &r)
{
    return r = r == Date::Weekday::Saturday ? Date::Weekday::Sunday : static_cast<Date::Weekday>(static_cast<int>(r) + 1);
}
Date::Weekday operator++(Date::Weekday &r, int)
{
    auto wd = r;
    ++r;
    return wd;
}
Date::Weekday &operator--(Date::Weekday &r)
{
    return r = r == Date::Weekday::Sunday ? Date::Weekday::Saturday : static_cast<Date::Weekday>(static_cast<int>(r) - 1);
}
Date::Weekday operator--(Date::Weekday &r, int)
{
    auto wd = r;
    --r;
    return wd;
}