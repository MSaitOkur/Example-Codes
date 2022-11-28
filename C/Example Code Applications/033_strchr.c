#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "mystring.h"

#define SIZE 100

char *mystrchr(const char *str, int ch)
{
    const char *ptr;
    for (ptr = str; *ptr != '\0' && *ptr != ch; ++ptr)
        ;
    return *ptr == '\0' ? NULL : (char *)ptr;
}

int main(void)
{
    char str[SIZE];
    fprintf(stdout, "Enter a sentence: ");
    sgets(str, stdin);

    fprintf(stdout, "Which character do you search: ");
    char ch;
    scanf("%c", &ch);

    char *ptr;
    if ((ptr = mystrchr(str, ch)))
        fprintf(stdout, "The first index of first \'%c\' : %zu\n", ch, ptr - str);
    else
        fprintf(stdout, "There is no \'%c\' in the sentence\n", ch);
}