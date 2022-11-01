// This program sums up the digits of the interger number.

#include <stdio.h>

size_t sum_digit(size_t num)
{
    size_t sum = num % 10;

    while(num /= 10)
        sum += num % 10;

    return sum;
}

int main()
{
    size_t val;
    printf("Enter an integer value: ");
    scanf("%zu", &val);

    printf("sum of digits of [%zu] = %zu\n", val, sum_digit(val));
}
