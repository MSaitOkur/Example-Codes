#ifndef WEEKDAY_HPP
#define WEEKDAY_HPP

#include <iostream>

enum class Weekday
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};

std::ostream &operator<<(std::ostream &os, Weekday wd)
{
    static const char *pdays[]{
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
    };

    return os << pdays[static_cast<int>(wd)];
}

Weekday &operator++(Weekday &wd)
{
    return wd = wd == Weekday::Saturday ? Weekday::Sunday : static_cast<Weekday>(static_cast<int>(wd) + 1);
}

Weekday operator++(Weekday &wd, int)
{
    Weekday wd_temp{wd};

    ++wd;

    return wd_temp;
}

#endif