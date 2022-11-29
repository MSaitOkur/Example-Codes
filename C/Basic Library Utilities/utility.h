#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#undef RANDOM_VALUE_MAX
#define RANDOM_VALUE_MAX 1000

#define randomize() (srand((unsigned int)time(NULL)))

void swap_int(int *i1, int *i2);

void set_array_random_int(int *ar, size_t ar_size);
void display_array_int(int *ar, size_t ar_size);
int *bubble_sort_int(int *arr, size_t size);
int *bubble_sort_int_odds_evens(int *arr, size_t size);
int *reverse_array_int(int *ar, size_t size);
int *merge_sorted_int(int *ar1, size_t size1, int *ar2, size_t size2, int *ar_merged);

size_t bin_search_int(int *arr, size_t size, int sval);

char *sgets(char *buffer, FILE *stream);
char *sgets_secure(char *buffer, size_t buffer_size, FILE *stream);


#endif // UTILITY_HEADER
