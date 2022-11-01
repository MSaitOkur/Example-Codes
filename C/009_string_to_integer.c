// This program converts number from a string to integer
#include <stdio.h>

int string_to_number(char *str, int base)
{
    int number = 0;

    if (base != 16)
    {
        for (size_t i = 0; str[i] != '\0'; ++i)
        {
            number *= base;
            number += str[i] - '0';
        }
    }
    else
    {
        for (size_t i = 0; str[i] != '\0'; ++i)
        {
            if ( str[i] >= '0' && str[i] <= '9')
            {
                number *= base;
                number += str[i] - '0';
            }
            else if ( str[i] >= 'a' && str[i] <= 'f')
            {
                number *= base;
                number += str[i] - 'a' + 10;
            }
            else if ( str[i] >= 'A' && str[i] <= 'F')
            {
                number *= base;
                number += str[i] - 'A' + 10;
            }
        }
    }

    return number;
}

int main(void)
{
    char str[100] = "";
    printf("Enter an integer value: ");
    scanf("%s", str);

    int base;
    printf("Enter the base: ");
    scanf("%d", &base);

    printf("Number is : %d\n", string_to_number(str, base));
}
