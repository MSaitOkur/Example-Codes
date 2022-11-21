/* This program prints all text of the file to stdout
 * pfile <file name>
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stdout, "Usage: <pfile> <file name>\n");
        exit(EXIT_FAILURE);
    }

    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "File couldn't open!...\n");
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(f)) != EOF)
        fputc(c, stdout);

    fclose(f);
}