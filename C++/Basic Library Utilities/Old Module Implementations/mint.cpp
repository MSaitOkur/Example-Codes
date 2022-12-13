#include "mint.h"
#include<istream>
#include<ostream>

std::ostream& operator<<(std::ostream& os, const Mint& mint)
{
    return os << "(" << mint.mval << ")";
}

std::istream& operator>>(std::istream& is, Mint& mint)
{
    return is >> mint.mval;
}

