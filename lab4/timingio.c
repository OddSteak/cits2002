#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_COPIES 1000

void append_file(char* src, char* dst);
void clearfile(char* file);
void readintomem(char* file, int bufsize);

int main(int ac, char** av)
{
    if (ac < 3) {
        printf("idiot\n");
        exit(EXIT_FAILURE);
    }

    char* dst = av[1];
    char* src = "/bin/bash";

    int bufsize = atoi(av[2]);

    if (bufsize == 0) {
        printf("idiot\n");
        exit(EXIT_FAILURE);
    }

    clearfile(dst);
    for (int i = 0; i < NUM_COPIES; i++) {
        append_file(src, dst);
    }

    struct timespec before;
    clock_gettime(CLOCK_REALTIME, &before);

    readintomem(dst, bufsize);

    struct timespec after;
    clock_gettime(CLOCK_REALTIME, &after);

    printf("time taken %lu\n", after.tv_sec - before.tv_sec);
}

void append_file(char* src, char* dst)
{
    int fd_in = open(src, O_RDONLY);
    int fd_out = open(dst, O_APPEND | O_WRONLY, 0777);

    if (fd_out < 0 || fd_in < 0) {
        fprintf(stderr, "failed to open files for appending\n");
        fprintf(stderr, "errno: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int got;
    char buf[90000];

    while ((got = read(fd_in, buf, sizeof buf)) > 0) {
        if (write(fd_out, buf, got) != got) {
            printf("something went wrong while appending to file\n");
            fprintf(stderr, "errno: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    close(fd_out);
    close(fd_in);
}

void clearfile(char* file)
{
    FILE* fd = fopen(file, "w");
    fclose(fd);
}

void readintomem(char* file, int bufsize)
{
    char buf[bufsize];

    int fd = open(file, O_RDONLY);

    while (read(fd, buf, bufsize) != 0)
        ;

    close(fd);
}
