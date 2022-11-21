/* This program counts a character in a text file which was entered from command line
 * ccount <file name> <character>
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stdout, "Usage: <ccount> <file name> <character>\n");
        exit(EXIT_FAILURE);
    }

    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "File couldn't open!...\n");
        exit(EXIT_FAILURE);
    }

    size_t c_count = 0;
    int c;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == argv[2][0])
            ++c_count;
    }

    fclose(f);

    fprintf(stdout, "Number of %c = %zu\n", *argv[2], c_count);
}