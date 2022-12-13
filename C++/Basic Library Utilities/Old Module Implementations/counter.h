#ifndef COUNTER
#define COUNTER

#include <istream>
#include <ostream>

template <typename T>
class Counter
{
public:
    Counter() = default;
    Counter(T x) : cnt{x} {}

    void set(T val)
    {
        cnt = val;
    }
    T get() const
    {
        return cnt;
    }

    template<typename U>
    Counter operator=(const Counter<U>& other)
    {
        this->cnt = other.get();
        return *this;
    }

    Counter &operator++()
    {
        ++cnt;
        return *this;
    }

    Counter operator++(int)
    {
        Counter temp{*this};
        ++(*this);
        return temp;
    }

    friend std::ostream &operator<<(std::ostream &os, const Counter &x)
    {
        return os << "[" << x.cnt << "]";
    }

private:
    T cnt{};
};

#endif