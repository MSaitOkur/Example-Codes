#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <memory>
#include <iostream>
#include "triple.h"

template <class T, class D = std::default_delete<T>>
class UniquePtr
{
public:
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr() = default;
    explicit UniquePtr(T *p) : mp{p} {}
    ~UniquePtr()
    {
        if (mp)
            D{}(mp);
    }

    UniquePtr(UniquePtr &&other)
    {
        D{}(mp);
        mp = other.mp;
        other.mp = nullptr;
    }
    UniquePtr &operator=(UniquePtr &&other)
    {
        D{}(mp);
        mp = other.mp;
        other.mp = nullptr;

        return *this;
    }

    T *release()
    {
        T *ptemp = mp;
        mp = nullptr;
        return ptemp;
    }

    T *get()
    {
        return mp;
    }

    void reset(T *newptr = nullptr)
    {
        D{}(mp);
        mp = newptr;
    }

    T &operator*()
    {
        return *this->mp;
    }
    T *operator->()
    {
        return this->mp;
    }

    operator bool()
    {
        return mp != nullptr;
    }

    friend bool operator==(UniquePtr &uptr, std::nullptr_t)
    {
        return !uptr;
    }

    friend bool operator!=(UniquePtr &uptr, std::nullptr_t)
    {
        return uptr;
    }

private:
    T *mp = nullptr;
};

// template<typename T, typename Deleter>
// class UniquePtr<T[], Deleter>{};

template <typename T, typename... Args>
UniquePtr<T> MakeUnique(Args &&...args)
{
    return UniquePtr<T>{new T{std::forward<Args>(args)...}};
}

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Triple> &t)
{
    return os << t.get();
}

#endif