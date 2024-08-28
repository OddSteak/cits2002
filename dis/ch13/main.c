#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int main()
{
    pid_t pid;

    pid = fork();   /* create a new child process */

    printf("pid = %d\n", pid);  /* both parent and child execute this */

    return 0;
}

