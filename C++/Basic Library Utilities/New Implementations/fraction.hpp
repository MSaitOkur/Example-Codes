#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>
#include <iosfwd>
#include <limits>
#include <cstdlib>
#include <iostream>

class Fraction
{
public:
    explicit Fraction(int num = 0, int denom = 1)
        : m_num{num / Fraction::get_lcm(num, denom)},
          m_denom{denom / Fraction::get_lcm(num, denom)}
    {
        Fraction::correct_sign(this);
    }
    explicit Fraction(double dval)
        : m_num{Fraction::float_to_rational(dval).m_num},
          m_denom{Fraction::float_to_rational(dval).m_denom} {}
    // explicit Fraction(const std::string &s);
    Fraction &operator+=(const Fraction &f)
    {
        m_num = m_num * f.m_denom + f.m_num * m_denom;
        m_denom *= f.m_denom;

        int lcm = Fraction::get_lcm(m_num, m_denom);
        m_num /= lcm;
        m_denom /= lcm;

        return *this;
    }
    Fraction &operator-=(const Fraction &f)
    {
        m_num = m_num * f.m_denom - f.m_num * m_denom;
        m_denom *= f.m_denom;

        int lcm = Fraction::get_lcm(m_num, m_denom);
        m_num /= lcm;
        m_denom /= lcm;

        return *this;
    }
    Fraction &operator*=(const Fraction &f)
    {
        m_num *= f.m_num;
        m_denom *= f.m_denom;

        int lcm = Fraction::get_lcm(m_num, m_denom);
        m_num /= lcm;
        m_denom /= lcm;

        return *this;
    }
    Fraction &operator/=(const Fraction &f)
    {
        m_num *= f.m_denom;
        m_denom *= f.m_num;

        int lcm = Fraction::get_lcm(m_num, m_denom);
        m_num /= lcm;
        m_denom /= lcm;

        return *this;
    }

    Fraction &operator++()
    {
        *this += Fraction{1, 1};
        return *this;
    }
    Fraction operator++(int)
    {
        Fraction temp{*this};
        ++*this;
        return temp;
    }
    Fraction &operator--()
    {
        *this -= Fraction{1, 1};
        return *this;
    }
    Fraction operator--(int)
    {
        Fraction temp{*this};
        --*this;
        return temp;
    }

    constexpr int Num() const
    {
        return m_num;
    }
    constexpr int Denom() const
    {
        return m_denom;
    }

    constexpr explicit operator bool() const
    {
        return m_num != 0;
    }
    constexpr bool operator!() const
    {
        return m_num == 0;
    }
    constexpr double to_double() const
    {
        return static_cast<double>(m_num) / m_denom;
    }
    // std::string to_string() const; // 16

public: // Public Static Functions
    static Fraction Random(int rand_min = -10000, int rand_max = 10001)
    {
        int num = std::rand() % (rand_max - rand_min + 1) + rand_min;
        int denom;
        while ((denom = std::rand() % (rand_max - rand_min + 1) + rand_min) == 0)
            ;

        return Fraction{num, denom};
    }
    static int get_lcm(int num, int denom)
    {
        if (num < 0)
            num *= -1;
        if (denom < 0)
            denom *= -1;

        int min = num <= denom ? num : denom;
        int lcm = 1;

        for (int i = 2; i <= min; ++i)
            if (num % i == 0 && denom % i == 0)
                lcm = i;

        return lcm;
    }

public: // Friend Functions
    friend inline std::istream &operator>>(std::istream &is, Fraction &f);

private: // Private Static Functions
    static void correct_sign(Fraction *f)
    {
        if (f->m_num * f->m_denom > 0 && f->m_num < 0)
        {
            f->m_num *= -1;
            f->m_denom *= -1;
        }
        else if (f->m_num * f->m_denom < 0 && f->m_num > 0)
        {
            f->m_num *= -1;
            f->m_denom *= -1;
        }
    }
    static Fraction float_to_rational(double dval)
    {
        int num = static_cast<int>(dval * 1000000.);
        int denom = 1000000;

        int lcm = Fraction::get_lcm(num, denom);

        return Fraction{num / lcm, denom / lcm};
    }
    static void simplify(Fraction &f)
    {
        int lcm = Fraction::get_lcm(f.m_num, f.m_denom);

        f.m_num /= lcm;
        f.m_denom /= lcm;
    }

private:
    int m_num{};
    int m_denom{1};
};

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    int num = f1.Num() * f2.Denom() + f1.Denom() * f2.Num();
    int denom = f1.Denom() * f2.Denom();

    int lcm = Fraction::get_lcm(num, denom);

    return Fraction{num / lcm, denom / lcm};
}
Fraction operator-(const Fraction &f1, const Fraction &f2)
{
    int num = f1.Num() * f2.Denom() - f1.Denom() * f2.Num();
    int denom = f1.Denom() * f2.Denom();

    int lcm = Fraction::get_lcm(num, denom);

    return Fraction{num / lcm, denom / lcm};
}
Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    int num = f1.Num() * f2.Num();
    int denom = f1.Denom() * f2.Denom();

    int lcm = Fraction::get_lcm(num, denom);

    return Fraction{num / lcm, denom / lcm};
}
Fraction operator/(const Fraction &f1, const Fraction &f2)
{
    int num = f1.Num() * f2.Denom();
    int denom = f1.Denom() * f2.Num();

    int lcm = Fraction::get_lcm(num, denom);

    return Fraction{num / lcm, denom / lcm};
}

constexpr bool operator==(const Fraction &f1, const Fraction &f2)
{
    return f1.Num() == f2.Num() && f1.Denom() == f2.Denom();
}
bool operator!=(const Fraction &f1, const Fraction &f2)
{
    return !(f1 == f2);
}
bool operator<(const Fraction &f1, const Fraction &f2)
{
    return f1.Denom() == f2.Denom() ? f1.Num() < f2.Num()
                                    : (f1.Num() * f2.Denom()) < (f2.Num() * f1.Denom());
}
bool operator<=(const Fraction &f1, const Fraction &f2)
{
    return f1 < f2 || f1 == f2;
}
bool operator>(const Fraction &f1, const Fraction &f2)
{
    return f2 < f1;
}
bool operator>=(const Fraction &f1, const Fraction &f2)
{
    return f2 < f1 || f2 == f1;
}

inline std::ostream &operator<<(std::ostream &os, const Fraction &f)
{
    os << "(";

    if (f.Denom() != 1)
        os << f.Num() << "/" << f.Denom();
    else
        os << f.Num();

    return os << ")";
}
inline std::istream &operator>>(std::istream &is, Fraction &f)
{
    std::getchar();
    std::cin >> f.m_num;
    std::getchar();
    std::cin >> f.m_denom;
    std::getchar();

    Fraction::simplify(f);

    return is;
}
// constexpr Fraction operator""_f(const char *, size_t); // 30

#endif
