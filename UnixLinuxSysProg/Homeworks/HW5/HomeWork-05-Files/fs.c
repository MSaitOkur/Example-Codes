/* fs.c */

#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

struct task_struct *current;

void init_task(void)
{
    current = (struct task_struct *)malloc(sizeof(struct task_struct));
    
    if (current == NULL) {
        fprintf(stderr, "Fatal error!\n");
        exit(EXIT_FAILURE);
    }
    
    /* ... */
}
