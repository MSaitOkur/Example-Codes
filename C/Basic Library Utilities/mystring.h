#ifndef MYSTRING_H
#define MYSTRING_H

#include <stddef.h>

size_t mystrlen(const char *str);
char *mystrrev(char *str);
char *mystrchr(const char *str, int ch);

#endif // MYSTRING_H