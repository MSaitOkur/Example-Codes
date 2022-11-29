#include "mystring.h"
#include <stdio.h>


size_t mystrlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;

    return len;
}

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

char *mystrchr(const char *str, int ch)
{
    const char *ptr;
    for (ptr = str; *ptr != '\0' && *ptr != ch; ++ptr)
        ;
    return *ptr == '\0' ? NULL : (char *)ptr;
}
