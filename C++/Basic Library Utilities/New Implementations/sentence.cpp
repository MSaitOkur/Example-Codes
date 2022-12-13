#include "sentence.hpp"
#include <cstdlib>
#include <iostream>

Sentence::Sentence(const char *p)
    : mlen{std::strlen(p)}, mptr{static_cast<char *>(std::malloc(mlen + 1))}
{
    std::strcpy(mptr, p);
}

Sentence::Sentence(const Sentence &other)
    : mlen{other.mlen}, mptr{static_cast<char *>(std::malloc(mlen + 1))}
{
    std::strcpy(mptr, other.mptr);
}

Sentence::Sentence(Sentence &&other) : mlen{other.mlen}, mptr{other.mptr}
{
    other.mptr = nullptr;
}

Sentence &Sentence::operator=(const Sentence &other)
{
    if (&other != this) // self assignment control
    {
        std::free(mptr);

        mlen = other.mlen;

        mptr = static_cast<char *>(std::malloc(mlen + 1));
        std::strcpy(mptr, other.mptr);
    }

    return *this;
}

Sentence &Sentence::operator=(Sentence &&other)
{
    if (&other != this) // self assignment control
    {
        mlen = other.mlen;
        mptr = other.mptr;

        other.mptr = nullptr;
    }

    return *this;
}

Sentence::~Sentence()
{
    if (mptr)
        std::free(mptr);
}

size_t Sentence::length() const
{
    return mlen;
}

void Sentence::print() const
{
    std::cout << "[" << mptr << "]\n";
}
