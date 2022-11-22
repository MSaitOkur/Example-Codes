#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f;
    if ((f = fopen("primes.dat", "rb")) == NULL)
        return 1;

    fseek(f, 0L, SEEK_END);

    fprintf(stdout, "The size of the primes.dat is %ld\n", ftell(f));

    fclose(f);
}