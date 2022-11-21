#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// combine <filename> <partsize>
// part files: part%03d.par
// combine <newfilename>

#define MAX_LEN 100

int main(int argc, char **argv)
{
    char new_file_name[MAX_LEN];
    if (argc != 2)
    {
        fprintf(stdout, "Enter the new file name: ");
        scanf("%s", new_file_name);
    }
    else
        strcpy(new_file_name, argv[1]);

    FILE *dest_file;
    if ((dest_file = fopen(new_file_name, "wb")) == NULL)
    {
        fprintf(stdout, "%s couldn't created!\n", new_file_name);
        exit(EXIT_FAILURE);
    }

    size_t part_file_count = 0;
    size_t total_byte_count = 0;
    char part_file_name[MAX_LEN];
    while (1)
    {
        sprintf(part_file_name, "part%03zu.par", part_file_count + 1);
        FILE *file_part;
        if ((file_part = fopen(part_file_name, "rb")) == NULL)
            break;
        ++part_file_count;

        int c;
        while ((c = fgetc(file_part)) != EOF)
        {
            fputc(c, dest_file);
            ++total_byte_count;
        }

        fclose(file_part);
    }

    fprintf(stdout, "Totally %zu byte and %zu part files combined to create %s file.\n",
            total_byte_count, part_file_count, new_file_name);

    for (size_t i = 1; i <= part_file_count; ++i)
    {
        sprintf(part_file_name, "part%03zu.par", i);

        if (remove(part_file_name))
        {
            fprintf(stderr, "File couldn't delete!...: \n");
            puts(strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}
