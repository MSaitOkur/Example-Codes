// Perfect Numbers

/*
    6 = 1 + 2 + 3
    28 = 1 + 2 + 4 + 7 + 14
*/
#include <stdio.h>

int is_perfect(size_t number)
{
    size_t sum_of_dividers = 0;
    for (size_t i = 1; i <= number / 2; ++i)
        if (number % i == 0)
            sum_of_dividers += i;

    return sum_of_dividers == number ? 1 : 0;
}

int main()
{
    // size_t number;
    // printf("enter an integer value: ");
    // scanf("%zu", &number);
    // printf("%zu : %s perfect\n", number, is_perfect(number) ? "is" : "is not");

    for (size_t i = 1; i < 10000; ++i)
        if (is_perfect(i))
            printf("%zu ", i);
}
