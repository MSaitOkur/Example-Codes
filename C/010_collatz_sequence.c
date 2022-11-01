// This program prints the collatz sequence to the console screen

/*
    Collatz Sequence
    
    The sequence begins with any positive integer, say n
    If the integer n is odd, the next number in sequence would be 3n+1
    If the integer n is even, the next number in sequence would be n/2
    The sequence will continue until digit 1 is encountered
*/

#include <stdio.h>

void print_collatz_sequence(int number)
{
    printf("The collatz sequence of %d:\n", number);

    while (number != 1)
    {
        printf("%d ", number);
        if (number % 2)
            number = number * 3 + 1;
        else
            number /= 2;
    }

    printf("1\n");
}

int main(void)
{
    int ival;
    printf("Enter an integer value: ");
    scanf("%d", &ival);

    print_collatz_sequence(ival);
}
