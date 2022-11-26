#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void set_array_random_int(int *ar, size_t ar_size)
{
    randomize();

    for (size_t i = 0; i < ar_size; ++i)
        ar[i] = rand() % RANDOM_VALUE_MAX;
}

void display_array_int(int *ar, size_t ar_size)
{
    putchar('\n');
    for (size_t i = 0; i < ar_size; ++i)
        printf("%03d ", ar[i]);
    putchar('\n');

}
