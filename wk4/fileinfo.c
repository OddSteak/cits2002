#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void print_info(char *path);

int main()
{
    char *filenames[5] = { "./safe.c", "./rando.c", "./Makefile", "./replace.c", "./mystrlen.c" };

    for (int i = 0; i < 5; i++) {
        print_info(filenames[i]);
    }
    return 0;
}

void print_info(char *path)
{
    struct stat buf;

    stat(path, &buf);

    printf("name: %s\n", path);
    printf("modtime: %s", ctime(&buf.st_mtime));
    printf("size (in B): %lu\n", buf.st_size);
    printf("\n");
}
