#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define min(a, b) ((a) > (b) ? (b) : (a))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define is_leap(y) ((y) % 4 == 0 && ((y) % 100 || (y) % 400 == 0))
#define is_lower(ch) ((ch) >= 'a' && (ch) <= 'z')
#define is_upper(ch) ((ch) >= 'A' && (ch) <= 'Z')
#define to_lower(ch) (is_upper((ch)) ? (ch) - 'A' + 'a' : (ch))
#define to_upper(ch) (is_lower((ch)) ? (ch) - 'a' + 'A' : (ch))
#define randomize() (srand((unsigned int)time(NULL)))

#define swap(a, b)    \
    {                 \
        int temp = a; \
        a = b;        \
        b = temp;     \
    }

void clear_input_buffer(void)
{
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n')
        ;
}

int main()
{
    /*
        int ival1, ival2;
        printf("Enter 2 integer values: ");
        scanf("%d%d", &ival1, &ival2);

        printf("min(%d,%d) = %d\n", ival1, ival2, min(ival1, ival2));
        printf("max(%d,%d) = %d\n", ival1, ival2, max(ival1, ival2));
    */

    /*
        printf("Enter a year: ");
        size_t year;
        scanf("%zu", &year);
        printf("%zu is %s leap year\n", year, is_leap(year) ? "" : "not");
    */

    /*
        clear_input_buffer();
        char sentence[SIZE] = "";
        printf("Enter a sentence: ");
        fgets(sentence, SIZE, stdin);

        size_t len = 0;
        while (sentence[len] != '\0')
            ++len;

        for (size_t i = 0; i < len; ++i)
            sentence[i] = to_upper(sentence[i]);
        puts(sentence);
    */

    /*
        int ival3, ival4;
        printf("Enter 2 integer values: ");
        scanf("%d%d", &ival3, &ival4);

        printf("Before swap num1 = %d, num2 = %d\n", ival3, ival4);
        swap(ival3, ival4);
        printf("After  swap num1 = %d, num2 = %d\n", ival3, ival4);
    */
}
