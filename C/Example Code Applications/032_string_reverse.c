#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "mystring.h"

#define SIZE 100

char *mystrrev(char *str)
{
    size_t len = mystrlen(str);

    for (size_t i = 0; i < len / 2; ++i)
    {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }

    return str;
}

int main(void)
{
    char str[SIZE];
    fprintf(stdout, "Enter a sentence: ");
    sgets(str, stdin);

    puts(mystrrev(str));
}