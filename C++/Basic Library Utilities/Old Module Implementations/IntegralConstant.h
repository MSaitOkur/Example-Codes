#ifndef INTEGRAL_CONSTANT
#define INTEGRAL_CONSTANT

template <typename T, T v>
struct IntegralConstant
{
    static constexpr T value = v;
    using value_type = T;
    using type = IntegralConstant;
    constexpr operator value_type() const noexcept
    {
        return value;
    }
    constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

template <bool B>
using BoolConstant = IntegralConstant<bool, B>;

using TrueType = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;


#endif