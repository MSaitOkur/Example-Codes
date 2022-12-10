#if !defined UNIQUEPTR_HPP
#define UNIQUEPTR_HPP

template <typename T>
class UniquePtr
{
public:
    UniquePtr() = default;
    explicit UniquePtr(T *p) : mptr{p} {}

    UniquePtr(UniquePtr &&oth) : mptr{oth.mptr}
    {
        oth.mptr = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&oth)
    {
        if (mptr)
            delete mptr;

        mptr = oth.mptr;

        oth.mptr = nullptr;

        return *this;
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    ~UniquePtr()
    {
        if (mptr)
            delete mptr;
    }

    T &operator*()
    {
        return *mptr;
    }

    T *operator->()
    {
        return mptr;
    }

private:
    T *mptr{};
};

#endif