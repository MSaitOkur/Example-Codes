#include <stdio.h>
#include "utility.h"

#define SIZE 100

// Bubble sort algoritmasını öyle bir düzenleyinki dizi aşağıdaki örnekte olduğu gibi
// tekler başta çiftler sonda ve küçükten büyüğe sıralansın.
// 3 7 21 97 123 137 167 891 1235 2 4 18 90 122 456 ...
int *bubble_sort_int_odds_evens(int *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t j = 0; j < size - 1 - i; ++j)
            if ((arr[j] % 2 == 0 && arr[j + 1] % 2) ||
                (arr[j] % 2 == arr[j + 1] % 2 && arr[j] > arr[j + 1]))
                swap_int(arr + j, arr + j + 1);

    return arr;
}

int main(void)
{
    int arr[SIZE];
    set_array_random_int(arr, SIZE);
    display_array_int(arr, SIZE);

    display_array_int(bubble_sort_int_odds_evens(arr, SIZE), SIZE);
}
