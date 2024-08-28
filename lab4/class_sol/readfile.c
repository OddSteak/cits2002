#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdint.h>
#include <sys/time.h>

//  RETURNS THE CURRENT TIME, AS A NUMBER OF MILLISECONDS, IN A 64-bit INTEGER
int64_t milliseconds(void)
{
    struct timeval  now;

    gettimeofday( &now, NULL );       // timezone not required, so we pass NULL
    return ((int64_t)now.tv_sec * 1000) + now.tv_usec/1000;
}


//  READ A FILE, nbytes AT A TIME
int readfile(char filename[], int nbytes)
{
    int64_t started = milliseconds();
    int fd          = open(filename, O_RDONLY);

//  ENSURE THAT THE OPENING OF THE FILE WAS SUCCESSFUL
    if(fd < 0) {
        return 1;
    }

    int     nreads  = 0;
    char    bytes[nbytes];
    size_t  got;

    while((got = read(fd, bytes, sizeof(bytes))) > 0) {
        ++nreads;
    }
    close(fd);

    int64_t stopped = milliseconds();

    printf("%i\t%i\t%i\n", nbytes, (int)(stopped - started), nreads);

    return 0;
}

void usage(char progname[])
{
    printf("Usage: %s filename nbytes\n", progname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
//  ENSURE WE HAVE SUFFICIENT ARGUMENTS
    if(argc != 3) {
        usage(argv[0]);
    }

//  ENSURE THAT THE nbytes ARGUMENT IS MEANINGFUL
    int nbytes  = atoi(argv[2]);
    if(nbytes <= 0) {
        usage(argv[0]);
    }

//  PASS VALIDATED ARGUMENTS TO TEH FUNCTION WHICH DOES THE WORK
    if(readfile(argv[1], nbytes) != 0) {
        usage(argv[0]);
    }

    return EXIT_SUCCESS;
}
