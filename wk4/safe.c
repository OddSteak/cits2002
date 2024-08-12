#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool isSafe(char *str);

int main()
{
    printf("%s safe\n", isSafe("SuPer44") ? "is" : "not");
    printf("%s safe\n", isSafe("password") ? "is" : "not");
    return 0;
}

bool isSafe(char *str)
{
    int upper_count = 0, lower_count = 0, num_count = 0;

    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            num_count++;
        } else if (islower(str[i])) {
            lower_count++;
        } else if (isupper(str[i])) {
            upper_count++;
        } else {
            printf("tf %c\n", str[i]);
        }
    }

    return upper_count > 1 && lower_count > 1 && num_count > 1;
}
