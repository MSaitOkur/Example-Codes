// Copy a file using unformatted input and output
// copyfile sourcefile newfile

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: <copyfile> <sourcefile> <destfile>\n");
        exit(EXIT_FAILURE);
    }

    FILE *fsource;
    if ((fsource = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "Cannot open the %s file!...\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *fdest;
    if ((fdest = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "Cannot create the %s file!...\n", argv[2]);
        fclose(fsource);
        exit(EXIT_FAILURE);
    }

    char buffer[SIZE];
    size_t total_byte_count = 0;
    size_t read_bytes;
    while ((read_bytes = fread(buffer, 1, SIZE, fsource)))
    {
        fwrite(buffer, 1, read_bytes, fdest);
        total_byte_count += read_bytes;
    }

    fclose(fdest);
    fclose(fsource);

    fprintf(stdout, "Total bytes: %zu\n", total_byte_count);
}