#if !defined(TYPE_TRAITS)
#define TYPE_TRAITS

#include "IntegralConstant.h"

//========================
//========================

template <typename T> struct removecv : FalseType { using type = T; };
template <typename T> struct removecv<const T> : TrueType { using type = T; };
template <typename T> struct removecv<volatile T> : TrueType { using type = T; };
template <typename T> struct removecv<const volatile T> : TrueType { typedef T type; };

template <typename T>
using removecv_t = typename removecv<T>::type;

//========================
//========================

template<typename T> struct addcv{using type = const volatile T;};
template<typename T> struct addconst{using type = const T;};
template<typename T> struct addvolatile{using type = volatile T;};

template<typename T> 
using addcv_t = typename addcv<T>::type;
template<typename T> 
using addconst_t = typename addconst<T>::type;
template<typename T> 
using addvolatile_t = typename addvolatile<T>::type;

//========================
//========================

template <typename T> struct IsPointer : FalseType{ };
template <typename T> struct IsPointer<T *> : TrueType { };

//========================
//========================

template <typename T>
struct IsIntegral : IntegralConstant<bool,
    std::is_same_v<char, std::remove_cv_t<T>> ||
    std::is_same_v<signed char, std::remove_cv_t<T>> ||
    std::is_same_v<unsigned char, std::remove_cv_t<T>> ||
    std::is_same_v<int, std::remove_cv_t<T>> ||
    std::is_same_v<unsigned int, std::remove_cv_t<T>> ||
    std::is_same_v<long, std::remove_cv_t<T>> ||
    std::is_same_v<unsigned long, std::remove_cv_t<T>> ||
    std::is_same_v<long long, std::remove_cv_t<T>> ||
    std::is_same_v<unsigned long long, std::remove_cv_t<T>>>
{};
template<typename T>
inline constexpr bool IsIntegral_v = IsIntegral<T>::value;

//========================
//========================

template <typename T>
struct IsFloating : IntegralConstant<bool,
    std::is_same_v<float, typename std::remove_cv_t<T>> ||
    std::is_same_v<double, typename std::remove_cv_t<T>> ||
    std::is_same_v<long double, typename std::remove_cv_t<T>>
>{};
template <typename T>
inline constexpr bool IsFloating_v = IsFloating<T>::value;

//========================
//========================

template<typename T>
struct IsArithmetic : IntegralConstant<bool,
    IsIntegral<T>::value || IsFloating<T>::value
>{};

template<typename T>
inline constexpr bool IsArithmetic_v = IsArithmetic<T>::value;

//========================
//========================
template<typename T, typename U>
struct IsSame : FalseType{};

template<typename T>
struct IsSame<T,T> : TrueType{};

template<typename T, typename U>
inline constexpr bool IsSame_v = IsSame<T,U>::value;

//========================
//========================

#endif // TYPE_TRAITS
