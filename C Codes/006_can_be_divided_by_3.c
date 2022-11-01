// This program checks if an integer number can be divided by 3.
#include <stdio.h>

size_t sum_of_digits(size_t number)
{
    size_t sum = number % 10;
    
    while(number /= 10)
        sum += number % 10;
    
    return sum;
}

int is_div_by_3(size_t number)
{
    return !(sum_of_digits(number) % 3);
}

int main(void)
{
    size_t number;
    printf("Enter an integer value: ");
    scanf("%zu", &number);

    printf("sum of digits of this number = %d\n", sum_of_digits(number));
    printf("This number is %s by 3\n",
           is_div_by_3(number) ? "divisible" : "not divisible");
    
}
