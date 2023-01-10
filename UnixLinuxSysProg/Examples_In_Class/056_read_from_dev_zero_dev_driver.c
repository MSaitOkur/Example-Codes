#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *f;
    int ch;

    if ((f = fopen("/dev/zero", "rb")) == NULL)
    {
        fprintf(stderr, "cannot open file!..\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; ++i)
    {
        if ((ch = fgetc(f)) == EOF)
        {
            fprintf(stderr, "cannot read from file!..\n");
            exit(EXIT_FAILURE);
        }
        printf("%d ", ch);
        fflush(stdout);
    }
    printf("\n");

    fclose(f);

    return 0;
}