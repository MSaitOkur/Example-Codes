// This program checks if a year is leap year
#include <stdio.h>

// leap year: year that not be divisible by 100 or be divisible
// by 400 but always be divisible by 4

int isleap(int year)
{
    return !(year % 4) && (year % 100 || !(year % 400)) ? 1 : 0;
}

int main(void)
{
    int year;
    printf("Enter a year to check for leap year test: ");
    scanf("%d", &year);

    printf("%d %s leap year\n", year, isleap(year) ? "is" : "is not");
}
