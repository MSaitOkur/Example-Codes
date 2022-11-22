#include <stdio.h>
#include <stdlib.h>

int isprime(size_t number)
{
    for (size_t i = 2; i <= number / 2; ++i)
        if (number % i == 0)
            return 0;

    return 1;
}

int main()
{
    FILE *f;
    if ((f = fopen("primes.dat", "wb")) == NULL)
    {
        fprintf(stderr, "primes.dat couldn't opened!..\n");
        exit(EXIT_FAILURE);
    }

    size_t prime_number;
    fprintf(stdout, "How many prime numbers do you want to find? : ");
    scanf("%zu", &prime_number);

    for (size_t prm_cnt = 0, val = 2; prm_cnt < prime_number; ++val)
        if (isprime(val))
        {
            fwrite(&val, sizeof val, 1, f);
            ++prm_cnt;
        }

    fclose(f);
}