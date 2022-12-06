#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>

//--------------------------------------------------------------------
//--------------------------------------------------------------------
/* Meyer's Singleton */

class singleton
{
    singleton()
    {
        std::cout << "singleton() this = " << this << "\n";
    }

    singleton(const singleton &) = delete;            // move members were deleted implicitly
    singleton &operator=(const singleton &) = delete; // move members were deleted implicitly

public:
    static singleton &makeobject()
    {
        static singleton s;

        return s;
    }

    void foo()
    {
        std::cout << "singleton::foo(), this = " << this << "\n";
    }

    ~singleton()
    {
        std::cout << "~singleton() this = " << this << "\n";
    }
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/*
class singleton
{
    singleton()
    {
        std::cout << "singleton() this = " << this << "\n";
    }

    singleton(const singleton &) = delete;            // move members were deleted implicitly
    singleton &operator=(const singleton &) = delete; // move members were deleted implicitly

public:
    static singleton &makeobject()
    {
        if (s_object == nullptr)
        {
            // s_object = static_cast<singleton *>(malloc(sizeof(singleton)));
            s_object = new singleton;
        }

        return *s_object;
    }

    void foo()
    {
        std::cout << "singleton::foo(), this = " << this << "\n";
    }

    ~singleton()
    {
        std::cout << "~singleton() this = " << this << "\n";
    }

private:
    inline static singleton *s_object = nullptr;
};
*/
#endif // SINGLETON_HPP