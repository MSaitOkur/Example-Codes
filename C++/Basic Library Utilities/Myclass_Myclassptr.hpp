#ifndef MYCLASS_MYCLASSPTR_HPP
#define MYCLASS_MYCLASSPTR_HPP

#include <iostream>

class Myclass
{
public:
    Myclass()
    {
        std::cout << "Myclass() this = " << this;
        std::cout << " Resources were acquired\n";
    }

    ~Myclass()
    {
        std::cout << "~Myclass() this = " << this;
        std::cout << " Resources were destroyed\n";
    }

    void func()
    {
        std::cout << "Myclass::func() this = " << this << "\n";
    }
    void foo()
    {
        std::cout << "Myclass::foo() this = " << this << "\n";
    }

private:
    char buffer[256]{};
};

class MyclassPtr
{
public:
    MyclassPtr() = default;
    MyclassPtr(Myclass *ptr) : mptr{ptr} {}

    MyclassPtr(const MyclassPtr &) = delete;
    MyclassPtr &operator=(const MyclassPtr &) = delete;

    MyclassPtr(MyclassPtr &&other) : mptr{other.mptr}
    {
        other.mptr = nullptr;
    }

    MyclassPtr &operator=(MyclassPtr &&other)
    {
        if (mptr)
            delete mptr;

        mptr = other.mptr;

        other.mptr = nullptr;

        return *this;
    }

    ~MyclassPtr()
    {
        if (mptr)
            delete mptr;
    }

    Myclass &operator*()
    {
        return *mptr;
    }

    Myclass *operator->()
    {
        return mptr;
    }

private:
    Myclass *mptr{};
};

#endif