#ifndef ISTACK_H_INCLUDED
#define ISTACK_H_INCLUDED

#include<vector>

class Istack {
public:

    bool empty()const
    {
        return mvec.empty();
    }
    std::size_t size()const
    {
        return mvec.size();
    }

    int& top()
    {
        return mvec.back();
    }

    Istack& push(int val)
    {
        mvec.push_back(val);
        return *this;
    }

    void pop()
    {
        mvec.pop_back();
    }

    void clear()
    {
        mvec.clear();
    }

private:
    std::vector<int> mvec;
};

#endif // ISTACK_H_INCLUDED