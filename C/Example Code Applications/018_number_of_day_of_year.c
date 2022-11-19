#include <stdio.h>

#define isLeap(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))

int day_of_year(int d, int m, int y)
{
    switch (m - 1)
    {
    case 11:
        d += 30;
    case 10:
        d += 31;
    case 9:
        d += 30;
    case 8:
        d += 31;
    case 7:
        d += 31;
    case 6:
        d += 30;
    case 5:
        d += 31;
    case 4:
        d += 30;
    case 3:
        d += 31;
    case 2:
        d += isLeap(y) ? 29 : 28;
    case 1:
        d += 31;
    }

    return d;
}

int main()
{
    int d, m, y;
    fprintf(stdout, "Enter a date (dd mm yyyy): ");
    scanf("%d%d%d", &d, &m, &y);

    fprintf(stdout, "The date you entered is  %d", day_of_year(d, m, y));
    switch (d)
    {
    case 1:
    case 11:
    case 21:
    case 31:
        fprintf(stdout, "st day of year");
        break;
    case 2:
    case 12:
    case 22:
        fprintf(stdout, "nd day of year");
        break;
    case 3:
    case 13:
    case 23:
        fprintf(stdout, "rd day of year");
        break;
    default:
        fprintf(stdout, "rd day of year");
        break;
    }

    putchar('\n');
}