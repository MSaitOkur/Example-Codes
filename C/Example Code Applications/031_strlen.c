#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

#define SIZE 100

size_t mystrlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;

    return len;
}

int main(void)
{
    char str[SIZE];
    fprintf(stdout, "Enter a sentence: ");
    sgets(str, stdin);

    fprintf(stdout, "%zu\n", mystrlen(str));
}
