#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }   

    if (access(argv[1], F_OK) == 0)
        printf("file exists...\n");
    else {
        printf("file doesn't exist!..\n"); 
        exit(EXIT_SUCCESS);
    }
    if (access(argv[1], R_OK) == 0)
        printf("read access ok...\n");
    else
        printf("can't read...\n");

    if (access(argv[1], W_OK) == 0)
        printf("write access ok...\n");
    else 
        printf("can't write...\n");
    
    if (access(argv[1], X_OK) == 0)
        printf("execute access ok\n..");
    else 
        printf("can't execute..\n");

	return 0;
} 

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}