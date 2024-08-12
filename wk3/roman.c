#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// clang-format off
char romans[] = { 'M',  'D',  'C',  'L',  'X',  'V',  'I' };
// clang-format off
int reps[] =    { 1000, 500,  100,   50,   10,    5,    1 };

void romanize(int num, char* res);

int main(int ac, char** av)
{
    if (ac != 2) {
        printf("idiot\n");
        exit(EXIT_FAILURE);
    }

    int num = atoi(av[1]);
    for (int i = 1; i < num + 1; i++) {
        char *buf = (char *)malloc(1000);

        romanize(i, buf);
        buf = realloc(buf, strlen(buf) + 1);

        printf("%d: %s\n", i, buf);
    }
}

void romanize(int num, char* res)
{
    strcpy(res, "");
    int i = 0;
    while (num >= 10) {
        if (num >= reps[i]) {
            num -= reps[i];
            strncat(res, &romans[i], 1);
        } else {
            i++;
        }
    }

    if (num == 9) {
        strcat(res, "IX");
        return;
    }

    if (num < 4) {
        for (int i = 0; i < num; i++) {
            strncat(res, &romans[6], 1);
        }
        return;
    }

    if (num == 4) {
        strcat(res, "IV");
        return;
    }

    if (num >= 5) {
        strncat(res, &romans[5], 1);
        num -= 5;

        for (int i = 0; i < num; i++) {
            strncat(res, &romans[6], 1);
        }
        return;
    }
}
