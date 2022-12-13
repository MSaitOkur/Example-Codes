#include "Dynamic_Static.h"
#include <algorithm>
#include <iostream>

unsigned char Dynamic_Static::buffer[sizeof(Dynamic_Static) * Dynamic_Static::omax];
bool Dynamic_Static::flags[Dynamic_Static::omax]{};

void *Dynamic_Static::operator new(std::size_t n)
{
    auto iter = std::find(std::begin(flags), std::end(flags), false);
    if (iter == std::end(flags))
    {
        std::cout << "Yer kalmadigi icin hata gonderiliyor\n";
        throw std::bad_alloc{};
    }
    auto idx = std::distance(std::begin(flags), iter);
    flags[idx] = true;
    return buffer + idx * sizeof(Dynamic_Static);
}

void Dynamic_Static::operator delete(void *p)
{
    if (!p)
        return;
    auto idx = (static_cast<unsigned char *>(p) - buffer) / sizeof(Dynamic_Static);

    flags[idx] = false;
}
