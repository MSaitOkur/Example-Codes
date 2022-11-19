#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 11

// st nd rd th
// Date: day month year
void print_date(int day, int month, int year)
{
    printf("Date: %02d", day);
    switch (day)
    {
    case 1:
    case 11:
    case 21:
    case 31:
        fprintf(stdout, "st ");
        break;
    case 2:
    case 12:
    case 22:
        fprintf(stdout, "nd ");
        break;
    case 3:
    case 13:
    case 23:
        fprintf(stdout, "rd ");
        break;
    default:
        fprintf(stdout, "rd ");
        break;
    }
    switch (month)
    {
        case 1: printf("JAN "); break;
        case 2: printf("FEB "); break;
        case 3: printf("MAR "); break;
        case 4: printf("APR "); break;
        case 5: printf("MAY "); break;
        case 6: printf("JUN "); break;
        case 7: printf("JULY "); break;
        case 8: printf("AUG "); break;
        case 9: printf("SEP "); break;
        case 10: printf("OCT "); break;
        case 11: printf("NOV "); break;
        case 12: printf("DEC "); break;
    }

    printf("%d\n", year);
}

int main()
{
    fprintf(stdout, "Enter a date(dd/mm/yyyy): ");
    char date[SIZE] = "";
    scanf("%s", date);

    int darray[3];
    for (char *str = strtok(date, "/,.: "), idx = 0; str; str = strtok(NULL, "/,.: "))
        darray[idx++] = atoi(str);

    print_date(darray[0], darray[1], darray[2]);
}