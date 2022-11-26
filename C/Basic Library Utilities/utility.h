#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include <stddef.h>
#include <stdlib.h>
#include <time.h>


#undef RANDOM_VALUE_MAX 
#define RANDOM_VALUE_MAX 100

#define randomize() (srand((size_t)time(NULL)))

void set_array_random_int(int *ar, size_t ar_size);
void display_array_int(int *ar, size_t ar_size);

#endif // UTILITY_HEADER
