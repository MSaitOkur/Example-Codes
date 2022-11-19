// This program calculates sum, number and reverse 
// of digits of an integer value
#include <stdio.h>

int sum_digits(int number)
{
    int sum = number % 10;
    while(number /= 10)
        sum += number % 10;
    
    return sum;
}

int num_digits(int number)
{
    if(number == 0)
        return 1;

    int ndigits = 0;
    while(number != 0)
        ++ndigits, number /= 10;
    
    return ndigits;
}

int rev_digits(int number)
{
    int rev = 0;

    while(number)
    {
        rev *= 10;
        rev += number % 10;
        number /= 10;
    }
    return rev;
}

int main(void)
{
    int number;
    printf("Enter an integer value: ");
    scanf("%d", &number);

    printf("Sum of digits of the (%d) = %d\n", number, sum_digits(number));
    printf("Number of digits of the (%d) = %d\n", number, num_digits(number));
    printf("Reverse of digits of the (%d) = %d\n", number, rev_digits(number));

}
