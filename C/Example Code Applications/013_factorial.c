// This program calculates factorial of an integer value
#include <stdio.h>

size_t factorial1(size_t number)
{
    if (number == 1 || number == 0)
        return 1;

    size_t fact = 1;

    for (size_t i = 2; i <= number; ++i)
        fact *= i;

    return fact;
}

size_t factorial2(size_t number)
{
    return number < 2 ? 1 : number * factorial2(number - 1);
}

size_t factorial3(int number)
{
    size_t fact_array[] =
        {
            1ul,
            1ul,
            2ul,
            6ul,
            24ul,
            120ul,
            720ul,
            5040ul,
            40320ul,
            362880ul,
            3628800ul,
            39916800ul,
            479001600ul,
            6227020800ul,
            87178291200ul,
            1307674368000ul,
            20922789888000ul,
            355687428096000ul,
            6402373705728000ul,
            121645100408832000ul,
            2432902008176640000ul,
            14197454024290336768ul,
            17196083355034583040ul,
        };
    
    return fact_array[number];
}

int main()
{
    size_t ival;
    printf("enter an integer value: ");
    scanf("%zu", &ival);

    for (size_t i = 0; i <= ival; ++i)
        printf("%zu! = %zu\n", i, factorial3(i));
}
