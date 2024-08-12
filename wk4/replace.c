#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void replace(char oldword[], char newword[], char whole_sentence[]);
char *mystrndup(char *str, int num);

int main()
{
    char sent[1000] = "catocathartic";
    replace("cat", "bison", sent);
    printf("%s", sent);
}

void replace(char oldword[], char newword[], char whole_sentence[])
{
    char newbuf[1000];
    strcpy(newbuf, whole_sentence);
    int i = 0;

    while (1) {
        if (i >= (int) strlen(whole_sentence))
            break;

        if (!strcmp(mystrndup(&whole_sentence[i], strlen(oldword)), oldword)) {
            newbuf[i] = 0;
            strcat(strcat(newbuf, newword), &whole_sentence[i + strlen(oldword)]);
            printf("rest: %s\n", &whole_sentence[i + strlen(oldword)]);
            strcpy(whole_sentence, newbuf);
            i += strlen(newword);
        } else {
            i++;
        }
    }
}

char *mystrndup(char *str, int num)
{
    char *new = (char*) malloc(num * sizeof(char) + 1);

    for (int i = 0; i < num; i++) {
        new[i] = str[i];
    }

    new[num] = 0;
    return new;
}
