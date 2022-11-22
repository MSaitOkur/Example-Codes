#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Encript a file with a key
// enc <file name> <key>
// After encripting a file with a key value, if you reencript the encripted file with same
// key value, the file will be same.

#define SIZE 100

void exit_message(char *err_msg)
{
    fprintf(stderr, "%s\n", err_msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    char dest_file_name[SIZE];
    int key_val;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: <enc> <file name> <key>\n");

        fprintf(stdout, "Enter the file name to encyript: ");
        scanf("%s", dest_file_name);
        fprintf(stdout, "Enter the key value: ");
        scanf("%d", &key_val);
    }
    else
    {
        strcpy(dest_file_name, argv[1]);
        key_val = atoi(argv[2]);
    }

    srand((unsigned int)key_val);

    FILE *dest_file;
    if ((dest_file = fopen(dest_file_name, "rb")) == NULL)
        exit_message("Couldn't open the file");

    char temp_file_name[L_tmpnam];
    tmpnam(temp_file_name);
    FILE *temp_file;
    if ((temp_file = fopen(temp_file_name, "wb")) == NULL)
        exit_message("Temporary file couldn't create!");

    int c;
    while ((c = fgetc(dest_file)) != EOF)
        fputc(c ^ rand(), temp_file);

    fclose(dest_file);
    fclose(temp_file);

    if (remove(dest_file_name))
        exit_message("Cannot delete file");

    if (rename(temp_file_name, dest_file_name))
        exit_message("Couldn't rename file.");
}
