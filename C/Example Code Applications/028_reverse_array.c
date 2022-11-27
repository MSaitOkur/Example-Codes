#include <stdio.h>
#include "utility.h"

#define SIZE 100

int *reverse_array_int(int *ar, size_t size)
{
    for (size_t i = 0; i < size / 2; ++i)
        swap_int(ar + i, ar + size - 1 - i);

    return ar;
}

int main(void)
{
    randomize();

    int ar[SIZE];
    set_array_random_int(ar, SIZE);
    display_array_int(ar, SIZE);

    display_array_int(reverse_array_int(ar, SIZE), SIZE);
}
