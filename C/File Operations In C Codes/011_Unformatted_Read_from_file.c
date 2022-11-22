#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f;
    if ((f = fopen("primes.dat", "rb")) == NULL)
    {
        fprintf(stderr, "primes.dat couldn't opened!..\n");
        exit(EXIT_FAILURE);
    }

    size_t prime_number;
    fprintf(stdout, "How many prime numbers do you want to get? : ");
    scanf("%zu", &prime_number);

    size_t *prime_array;
    if ((prime_array = (size_t *)malloc(sizeof(size_t) * prime_number)) == NULL)
    {
        fprintf(stderr, "Cannot allocate dynamic memory!...\n");
        exit(EXIT_FAILURE);
    }

    fread(prime_array, sizeof(size_t), prime_number, f);

    for (size_t i = 0; i < prime_number; ++i)
        fprintf(stdout, "%zu\n", prime_array[i]);

    fclose(f);
}
