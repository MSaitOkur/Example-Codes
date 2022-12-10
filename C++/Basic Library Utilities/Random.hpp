#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>
#include <limits>

class Random
{
public:
    Random() = default;
    Random(int min, int max) : m_min{min}, m_max{max} {}

    int operator()()
    {
        ++m_cnt;
        return std::rand() % (m_max - m_min + 1) + m_min;
    }

    int get_count() const
    {
        return m_cnt;
    }

    operator int()
    {
        return (*this)();
    }

private:
    int m_min{};
    int m_max{std::numeric_limits<int>::max()};
    int m_cnt{};
};

#endif