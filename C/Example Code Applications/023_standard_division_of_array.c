#include <stdio.h>
#include "utility.h"
#include  <math.h>

/*
standard division:
    sqrt((sum((eachelementofarray - meanofarray)^2))/sizeofarray)
*/

#define SIZE 5

int sum_array_int(int *arr, size_t size);
double std_division_array_int(int *arr, size_t size);

int main(int argc, char **argv)
{
    int arr[SIZE];
    set_array_random_int(arr, SIZE);
    display_array_int(arr, SIZE);

    fprintf(stdout, "Standard div = %f\n", std_division_array_int(arr, SIZE));
}

int sum_array_int(int *arr, size_t size)
{
    int sum = 0;

    for (size_t i = 0; i < size; ++i)
        sum += arr[i];

    return sum;
}

double std_division_array_int(int *arr, size_t size)
{
    double mean = (double)sum_array_int(arr, size) / size;

    double sum_square = 0.;
    for (size_t i = 0; i < size; ++i)
        sum_square += (arr[i] - mean) * (arr[i] - mean);

    return sqrt(sum_square / size);
}