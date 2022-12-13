#ifndef MINT_H
#define MINT_H

#include<iosfwd>

class Mint {
public:
    Mint() = default;
    explicit Mint(int val) : mval{val} {}

    explicit operator int()const {return mval;}
    explicit operator bool()const {return mval != 0;}

    Mint& operator++() // PREFIX
    {
        ++mval;
        return *this;
    }
    Mint operator++(int) // POSTFIX
    {
        Mint temp{*this};
        ++*this;
        return temp;
    }
    Mint& operator--() // PREFIX
    {
        --mval;
        return *this;
    }
    Mint operator--(int) // POSTFIX
    {
        Mint temp{*this};
        --*this;
        return temp;
    }

/*  
    friend Mint& operator++(Mint&);      // PREFIX
    friend Mint operator++(Mint&, int);  // POSTFIX
    friend Mint& operator--(Mint&);      // PREFIX
    friend Mint operator--(Mint&, int);  // POSTFIX
*/

    Mint& operator+=(const Mint& other) 
    {
        mval += other.mval;
        return *this;
    }
    Mint& operator-=(const Mint& other)
    {
        mval -= other.mval;
        return *this;
    }
    Mint& operator*=(const Mint& other)
    {
        mval *= other.mval;
        return *this;
    }

    Mint operator+()const
    {
        return *this;
    }
    Mint operator-()const
    {
        return Mint{-mval};
    }

    friend bool operator<(const Mint& mx, const Mint& my)
    {
        return mx.mval < my.mval;
    }
    friend bool operator==(const Mint& mx, const Mint& my)
    {
        return mx.mval == my.mval;
    }

    friend std::ostream& operator<<(std::ostream&, const Mint&);
    friend std::istream& operator>>(std::istream&, Mint&);


private:
    int mval{};
};

inline Mint operator+(const Mint& x, const Mint& y)
{
    return Mint{x} += y;
}
inline Mint operator-(const Mint& x, const Mint& y)
{
    return Mint{x} -= y;
}
inline Mint operator*(const Mint& x, const Mint& y)
{
    return Mint{x} *= y;
}


inline bool operator>(const Mint& x, const Mint& y)
{
    return y < x;
}
inline bool operator>=(const Mint& x, const Mint& y)
{
    return !(x < y);
}
inline bool operator<=(const Mint& x, const Mint& y)
{
    return !(y < x);
}
inline bool operator!=(const Mint& x, const Mint& y)
{
    return !( x == y );
}

/*
Mint& operator++(Mint& mx) // PREFIX
{
    ++mx.mval;
    return mx;
}
Mint operator++(Mint& mx, int) // POSTFIX
{
    Mint temp{mx};
    ++mx;
    return temp;
}
Mint& operator--(Mint& mx) // PREFIX
{
    --mx.mval;
    return mx;
}
Mint operator--(Mint& mx, int) // POSTFIX
{
    Mint temp{mx};
    --mx;
    return temp;
}
*/


#endif // MINT_H