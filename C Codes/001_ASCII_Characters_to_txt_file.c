// This program writes the elements of the ASCII character set to a file which ends with ".txt" extension

#include <stdio.h>
#include <ctype.h>

int main()
{
    FILE *f = fopen("characters.txt", "w");
    if (f == NULL)
    {
        fprintf(stderr, "File couldn't created!\n");
        return 1;
    }

    for (int i = 0; i < 128; ++i)
    {
        if (iscntrl(i))
            fprintf(f, "%-3d  0x%x  Control Character\n", i, i);
        else
            fprintf(f, "%-3d  0x%x  %c\n", i, i, i);
    }

    fclose(f);
}
