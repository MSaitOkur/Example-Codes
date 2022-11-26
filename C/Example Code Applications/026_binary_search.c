#include <stdio.h>
#include "utility.h"

#define SIZE 100

size_t bin_search_int(int *arr, size_t size, int sval)
{
    size_t idx_first = 0;
    size_t idx_last = size - 1;
    size_t idx_mid;

    while (idx_first <= idx_last)
    {
        idx_mid = (idx_first + idx_last) / 2;
        if (arr[idx_mid] == sval)
            return idx_mid;
        else if (arr[idx_mid] < sval)
            idx_first = idx_mid + 1;
        else
            idx_last = idx_mid - 1;
    }

    return size;
}

int main(void)
{
    int arr[SIZE];
    set_array_random_int(arr, SIZE);
    display_array_int(arr, SIZE);
    bubble_sort_int(arr, SIZE);
    display_array_int(arr, SIZE);

    int val;
    fprintf(stdout, "Enter the search value: ");
    scanf("%d", &val);
    size_t idx = bin_search_int(arr, SIZE, val);

    if (idx < SIZE)
        fprintf(stdout, "%d was found, idx = %zu\n", val, idx);
    else
        fprintf(stdout, "%d wasn't found\n", val);
}