#ifndef DARRAY_HPP
#define DARRAY_HPP

#include <iostream>

class Darray
{
public:
    Darray() = default;
    Darray(std::size_t size) : msize{size}, mptr{new double[msize]{}} {}
    Darray(const Darray &) = delete;
    Darray &operator=(const Darray &) = delete;
    ~Darray() { delete[] mptr; }

    double &operator[](std::size_t index)
    {
        return mptr[index];
    }

    constexpr const double &operator[](std::size_t index) const
    {
        return mptr[index];
    }

    double &operator*()
    {
        return *mptr;
    }

    constexpr const double &operator*() const
    {
        return *mptr;
    }

    double *operator&()
    {
        return mptr;
    }

    constexpr const double *operator&() const
    {
        return mptr;
    }

    Darray *operator->()
    {
        return this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Darray &d)
    {
        os << "[";

        for (std::size_t i = 0; i < d.msize - 1; ++i)
            os << d.mptr[i] << ", ";

        return os << d.mptr[d.msize - 1] << "]\n";
    }

private:
    std::size_t msize = 0;
    double *mptr{nullptr};
};

#endif