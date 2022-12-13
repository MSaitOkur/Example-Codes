#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <deque>


template<typename T, typename C = std::deque<T>>
class Stack{
public:

    C::size_type size()const
    {
        return mcon.size();
    }

    bool empty()const
    {
        return mcon.empty();
    }

    void push(const T& tval)
    {
        mcon.push_back(tval);
    }
    template<typename ...Args>
    void emplace(Args&& ...args)
    {
        mcon.emplace(args...);
    }

    void pop(const T& tval)
    {
        mcon.pop_back(tval);
    }
    
    T& top()
    {
        return mcon.back();
    }

private:
    C mcon;
};


#endif