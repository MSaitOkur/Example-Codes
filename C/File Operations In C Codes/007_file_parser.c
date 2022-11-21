
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// parsefile <filename> <partsize>
// file 2356byte
// parsefile file 1000
// part001.par --> 1000byte
// part002.par --> 1000byte
// part003.par -->  356byte

#define MAX_LEN 100

int main(int argc, char **argv)
{
    char source_file_name[MAX_LEN + 1];
    size_t partsize;

    if (argc != 3)
    {
        fprintf(stdout, "Enter source file name: ");
        scanf("%s", source_file_name);

        fprintf(stdout, "Enter the part files' size: ");
        scanf("%zu", &partsize);
    }
    else
    {
        strcpy(source_file_name, argv[1]);
        partsize = atoi(argv[2]);
    }

    FILE *fsource;
    if ((fsource = fopen(source_file_name, "r")) == NULL)
    {
        fprintf(stderr, "%s couldn't opened!...\n", source_file_name);
        exit(EXIT_FAILURE);
    }

    int c;
    size_t byte_count = 0;

    char part_file_name[MAX_LEN + 1];
    size_t part_count = 0;
    FILE *fpart = NULL;

    while ((c = fgetc(fsource)) != EOF)
    {
        if (fpart == NULL)
        {
            sprintf(part_file_name, "part%03zu.par", part_count + 1);
            if ((fpart = fopen(part_file_name, "w")) == NULL)
            {
                fprintf(stderr, "%s couldn't opened!...\n", part_file_name);
                fclose(fsource);
                exit(EXIT_FAILURE);
            }
            ++part_count;
        }
        fputc(c, fpart);
        ++byte_count;

        if (byte_count % partsize == 0)
        {
            fclose(fpart);
            fpart = NULL;
        }
    }

    if (fpart)
        fclose(fpart);
    fclose(fsource);

    fprintf(stdout, "%s(%zu Byte) was parsed by %zu files\n", source_file_name, byte_count, part_count);
}