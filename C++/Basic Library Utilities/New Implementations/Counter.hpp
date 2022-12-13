#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <ostream>
#include <istream>

class Counter
{
public:
    Counter()
    {
        std::cout << "Counter() this = " << this << "\n";
    }

    explicit Counter(int val) : mval{val}
    {
        std::cout << "explicit Counter() this = " << this << "\n";
    }

    ~Counter()
    {
        std::cout << "~Counter() this = " << this << "\n";
    }

    Counter &operator++() // prefix
    {
        ++mval;
        return *this;
    }

    Counter operator++(int) // postfix
    {
        Counter tempCnt{*this};
        ++*this;
        return tempCnt;
    }
    Counter &operator--() // prefix
    {
        --mval;
        return *this;
    }

    Counter operator--(int) // postfix
    {
        Counter tempCnt{*this};
        --*this;
        return tempCnt;
    }

    int get() const
    {
        return mval;
    }

    void set(int val)
    {
        mval = val;
    }

    explicit operator int() const
    {
        return mval;
    }

    explicit operator bool() const
    {
        return mval != 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Counter &cnt)
    {
        return os << cnt.mval;
    }

    friend std::istream &operator>>(std::istream &is, Counter &cnt)
    {
        return is >> cnt.mval;
    }

private:
    int mval{};
};

class CounterPtr
{
public:
    CounterPtr() = default;

    explicit CounterPtr(Counter *p) : mptr{p} {}

    ~CounterPtr()
    {
        if (mptr)
            delete mptr;
    }

    Counter &operator*() { return *mptr; }
    Counter *operator->() { return mptr; }

private:
    Counter *mptr{};
};

#endif