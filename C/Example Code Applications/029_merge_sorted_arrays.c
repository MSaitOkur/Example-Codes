#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

#define SIZE 100

int *merge_sorted_int(int *ar1, size_t size1, int *ar2, size_t size2, int *ar_merged)
{
    size_t idx1 = 0, idx2 = 0, idx3 = 0;
    while (1)
    {
        if (idx1 < size1 && idx2 < size2)
        {
            if (ar1[idx1] <= ar2[idx2])
                ar_merged[idx3++] = ar1[idx1++];
            else if (ar2[idx2] <= ar1[idx1])
                ar_merged[idx3++] = ar2[idx2++];
        }
        else if (idx1 < size1)
            ar_merged[idx3++] = ar1[idx1++];
        else if (idx2 < size2)
            ar_merged[idx3++] = ar2[idx2++];
        else
            break;
    }

    return ar_merged;
}

int main(void)
{
    randomize();

    int ar1[SIZE];
    int ar2[SIZE];

    set_array_random_int(ar1, SIZE);
    set_array_random_int(ar2, SIZE);

    bubble_sort_int(ar1, SIZE);
    bubble_sort_int(ar2, SIZE);

    display_array_int(ar1, SIZE);
    display_array_int(ar2, SIZE);

    int ar3[2 * SIZE];
    display_array_int(merge_sorted_int(ar1, SIZE, ar2, SIZE, ar3), 2 * SIZE);
}
