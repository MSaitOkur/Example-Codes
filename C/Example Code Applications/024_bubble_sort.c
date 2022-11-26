#include <stdio.h>
#include "utility.h"

#define SIZE 100

void swap(int *i1, int *i2)
{
    int temp = *i1;
    *i1 = *i2;
    *i2 = temp;
}

int *bubble_sort(int *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t j = 0; j < size - 1 - i; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + j + 1);

    return arr;
}

int main(void)
{
    int arr[SIZE];
    set_array_random_int(arr, SIZE);
    display_array_int(arr, SIZE);

    display_array_int(bubble_sort(arr, SIZE), SIZE);
}
