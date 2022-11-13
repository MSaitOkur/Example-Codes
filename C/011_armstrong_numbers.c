// This program tests if an integer number is armstron number
/*
    Armstrong Numbers
    abcde = pow (a, n) + pow (b, n) + pow (c, n) + pow (d, n) + ...
        ... + pow (e, n)
    n : digit number
*/

#include <stdio.h>
#include <math.h>

size_t digit_number(size_t number)
{
    if (number == 0)
        return 1;

    size_t dig_cnt = 0;
    while (number)
    {
        ++dig_cnt;
        number /= 10;
    }

    return dig_cnt;
}

int is_armstrong(size_t number)
{
    size_t temp_num = number;
    size_t powers_sum = 0;
    size_t num_of_digits = digit_number(number);

    // while(number)
    for (size_t i = 0; i < num_of_digits; ++i)
    {
        powers_sum += pow(number % 10, num_of_digits);
        number /= 10;
    }

    return temp_num == powers_sum ? 1 : 0;
}

int main()
{
    size_t ival;
    printf("Enter a number for search max limit: ");
    scanf("%zu", &ival);

    for(size_t i = 0; i < ival; ++i)
        if(is_armstrong(i))
            printf("%zu ", i);

    putchar('\n');
}
