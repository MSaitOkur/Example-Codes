#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap_int(int *i1, int *i2)
{
    int temp = *i1;
    *i1 = *i2;
    *i2 = temp;
}

void set_array_random_int(int *ar, size_t ar_size)
{
    for (size_t i = 0; i < ar_size; ++i)
        ar[i] = rand() % RANDOM_VALUE_MAX;
}

void display_array_int(int *ar, size_t ar_size)
{
    fprintf(stdout, "\n-------------------------------------------------------------\n");
    for (size_t i = 0; i < ar_size; ++i)
    {
        if (i && i % 20 == 0)
            putchar('\n');
        printf("%3d ", ar[i]);
    }
    fprintf(stdout, "\n-------------------------------------------------------------\n");
}

int *bubble_sort_int(int *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t j = 0; j < size - 1 - i; ++j)
            if (arr[j] > arr[j + 1])
                swap_int(arr + j, arr + j + 1);

    return arr;
}

int *bubble_sort_int_odds_evens(int *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t j = 0; j < size - 1 - i; ++j)
            if ((arr[j] % 2 == 0 && arr[j + 1] % 2) ||
                (arr[j] % 2 == arr[j + 1] % 2 && arr[j] > arr[j + 1]))
                swap_int(arr + j, arr + j + 1);

    return arr;
}

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

int *reverse_array_int(int *ar, size_t size)
{
    for (size_t i = 0; i < size / 2; ++i)
        swap_int(ar + i, ar + size - 1 - i);

    return ar;
}

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
