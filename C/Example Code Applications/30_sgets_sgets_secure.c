#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

#define SIZE 100

char *sgets(char *buffer, FILE *stream)
{
    int c;
    size_t buf_idx = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        buffer[buf_idx++] = c;

    return buffer;
}

char *sgets_secure(char *buffer, size_t buffer_size, FILE *stream)
{
    int c;
    for (size_t idx = 0;
         (idx < buffer_size - 1) && (c = getchar()) != '\n' && c != EOF;
         ++idx)
    {
        buffer[idx] = c;
    }

    buffer[buffer_size - 1] = '\0';

    return buffer;
}

int main(void)
{
    char str[SIZE];
    fprintf(stdout, "Enter a sentence: ");
    sgets_secure(str, SIZE, stdin);
    puts(str);
}
