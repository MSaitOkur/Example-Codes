#ifndef MYPAIR
#define MYPAIR

#include <istream>
#include <ostream>

template <typename T, typename U>
struct MyPair
{
    MyPair() = default;
    MyPair(const T &t, const U &u) : first{t}, second{u} {}

    template <typename F, typename S>
    MyPair(const MyPair<F, S> &f) : first(f.first), second(f.second) {}

    template <typename F, typename S>
    MyPair &operator=(const MyPair<F, S> &f)
    {
        first = f.first;
        second = f.second;
        return *this;
    }

    T first{};
    U second{};
};

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const MyPair<T, U> &p)
{
    return os << "[" << p.first << ", " << p.second << "]";
}

template <typename T, typename U>
MyPair<T, U> MakeMyPair(const T &t, const U &u)
{
    return MyPair<T, U>(t, u);
}

template <typename T, typename U>
bool operator<(const MyPair<T, U> &p1, const MyPair<T, U> &p2)
{
    return p1.first < p2.first || !(p2.first < p2.first) && p1.second < p2.second;
}

#endif