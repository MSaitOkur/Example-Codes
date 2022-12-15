#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
#ifdef _POSIX_CHOWN_RESTRICTED
    printf("chown restricted\n");
#else
    printf("chown not restricted\n");
#endif
    return 0;
}