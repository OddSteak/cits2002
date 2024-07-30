#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

# define MAX_LENGTH_FILE 5000

char rotate(char c, int rot);
int rotate_file(char *arg, char *buf, int rot);

int main(int argcount, char *argvalue[])
{
    int rot = 13;

    if (argcount <= 1)
    {
        fprintf(stderr, "program expected at least 1 argument");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 1; i<argcount; i++)
        {
            int argrot = atoi(argvalue[i]);
            if (argrot)
            {
                rot = argrot;
                continue;
            }

            char buf[MAX_LENGTH_FILE];
            if (!rotate_file(argvalue[i], buf, rot))
            {
                printf("%s\n", buf);
            }
            else
            {
                for(int j = 0; j < (int) strlen(argvalue[i]); j++)
                {
                    printf("%c", rotate(argvalue[i][j], rot));
                }

                printf("\n");
            }
        }
    }
    return 0;
}

char rotate(char c, int rot)
{
    if(islower(c))
    {
        return ('a' + (c - 'a' + rot) % 26);
    }
    else
    {
        return ('A' + (c - 'A' + rot) % 26);
    }
}

int rotate_file(char *arg, char *buf, int rot)
{
    FILE *cfd = fopen(arg, "r");

    if (!cfd) return 1;

    char current_char;
    char rotchar;

    while(current_char = fgetc(cfd), current_char != EOF)
    {
        if (strlen(buf) == MAX_LENGTH_FILE - 1)
        {
            fprintf(stderr, "ERROR: the given file is too large, rotating the filename instead\n");
            fclose(cfd);
            return 1;
        }

        if (!(current_char >= 65 && current_char <= 90) &&
            !(current_char >= 97 && current_char <= 122))
        {
            strncat(buf, &current_char, 1);
            continue;
        }

        rotchar = rotate(current_char, rot);
        strncat(buf, &rotchar, 1);
    }

    fclose(cfd);

    return 0;
}

