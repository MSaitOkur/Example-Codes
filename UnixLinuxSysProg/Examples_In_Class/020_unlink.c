/*--------------------------------------------------------------------------------------------------------------------------
    Aşağıdaki örnekte komut satırından verilen yol ifadelerine ilişkin dosyalar silinmeye çalışılmıştır. 
---------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "file name(s) must be specified!..\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i)
        if (unlink(argv[i]) == -1) 
            perror("unlink");

    return 0;
}
