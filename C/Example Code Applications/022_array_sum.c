#include <stdio.h>
#include "utility.h"

#define SIZE 100

#define fmfsa(T)                         \
    T sum_array##T(T *ar, size_t sz)     \
    {                                    \
        T sum = 0;                       \
        for (size_t i = 0; i < sz; ++i) \
            sum += ar[i];                 \
                                         \
        return sum;                      \
    }

fmfsa(int);

int main(int argc, char **argv)
{
    int a[SIZE];
    set_array_random_int(a, SIZE);
    display_array_int(a, SIZE);

    fprintf(stdout, "sum of array = %d\n", sum_arrayint(a, SIZE));
}