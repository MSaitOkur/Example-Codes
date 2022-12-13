#ifndef MyClass_H
#define MyClass_H

#include <iosfwd>

class Dynamic_Static
{
public:
    void *operator new(std::size_t);
    void operator delete(void *);
    constexpr static std::size_t omax = 100;

private:
    static unsigned char buffer[];
    static bool flags[];
    char str[256]{};
};

#endif
