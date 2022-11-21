/* This program counts the all alphabetic characters in a text file
 * ccount <file name>
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stdout, "Usage: <ccount> <file name>\n");
        exit(EXIT_FAILURE);
    }

    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "File couldn't open!...\n");
        exit(EXIT_FAILURE);
    }

    size_t c_count[26] = {0};
    int c;
    while ((c = fgetc(f)) != EOF)
        for (size_t i = 0; i < 26; ++i)
            if (c == 'a' + i || c == 'A' + i)
                ++c_count[i];

    fclose(f);

    for (size_t i = 0; i < 26; ++i)
        fprintf(stdout, "%c = %zu\n", 'A' + (char)i, c_count[i]);
}