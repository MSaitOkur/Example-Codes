#include <iostream>

//--------------------------------------------------------------------
//--------------------------------------------------------------------

template <unsigned int n>
struct Fibonacci
{
    static unsigned const value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
};
template <>
struct Fibonacci<0>
{
    static unsigned const value = 0;
};
template <>
struct Fibonacci<1>
{
    static unsigned const value = 1;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

constexpr unsigned int fibonacci(unsigned int n)
{
    return n == 0   ? 0
           : n == 1 ? 1
                    : (fibonacci(n - 1) + fibonacci(n - 2));
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

constexpr unsigned int fibonacci2(unsigned int n)
{

    unsigned int result = 0;
    for (unsigned int first = 0, second = 1, step = 0; step < n; ++step)
    {
        if (step <= 1)
            result += step;
        else
        {
            result = first + second;
            first = second;
            second = result;
        }
    }

    return result;
}

int main()
{
    std::size_t n;
    std::cout << "Please give an input upto you want to print series : ";
    std::cin >> n;

    std::cout << "Fibonacci Series is: ";
    for (std::size_t i = 0; i < n; ++i)
        std::cout << fibonacci(i) << " ";

    std::cout << "\n";

    return 0;
}
