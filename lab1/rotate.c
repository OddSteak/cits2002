#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//  The rotate function returns the character ROT positions further along the
//  alphabetic character sequence from c, or c if c is not lower-case

char rotate(char c, int rot)
{
    if(islower(c)) {
        // The ciphered character is ROT positions beyond c,
        // allowing for wrap-around
        return ('a' + (c - 'a' + rot) % 26);
    }
    else {
        return ('A' + (c - 'A' + rot) % 26);
    }
}

int check_file(char *arg, char *buf, int rot) {
    FILE *cfd = fopen(arg, "r");

    if (!cfd) return 1;

    char current_char;
    char rotchar;

    while(current_char = fgetc(cfd), current_char != EOF) {
        if (current_char == ' ') {
            strncat(buf, &current_char, 1);
            continue;
        }
        rotchar = rotate(current_char, rot);
        strncat(buf, &rotchar, 1);
    }

    fclose(cfd);

    return 0;
}

int main(int argcount, char *argvalue[])
{
    int rot = 13;
    if(argcount <= 1) {
        fprintf(stderr, "program expected at least 1 arguments");
        exit(EXIT_FAILURE);
    } else {
        for (int i = 1; i<argcount; i++) {
            int argrot = atoi(argvalue[i]);

            if (argrot) {
                rot = argrot;
                continue;
            }

            char buf[100];
            if (!check_file(argvalue[i], buf, rot)) {
                printf("%s\n", buf);
            } else {
                printf("in else block\n");
                for(int j = 0; j < (int) strlen(argvalue[i]); j++) {
                    printf("%c", rotate(argvalue[i][j], rot));
                }
                printf("\n");
            }
        }
    }
    return 0;
}

