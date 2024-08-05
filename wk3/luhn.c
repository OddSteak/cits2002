#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Compile with: cc -std=c11 -Wall -Werror -o square square.c

bool luhn_test(char* number);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s value1\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf(luhn_test(argv[1]) ? "%s is a valid card number\n"
                              : "%s is not a valid card number\n",
        argv[1]);

    return EXIT_SUCCESS;
}

bool luhn_test(char* num)
{
    int s1 = 0;
    int s2 = 0;

    int digs = strlen(num);

    for (int i = digs - 1; i >= 0; i -= 2) {
        char cur_num = num[i];
        s1 += atoi(&cur_num);
    }

    for (int i = digs - 2; i >= 0; i -= 2) {
        char cur_num = num[i];
        int prod = atoi(&cur_num) * 2;

        if (prod / 10) {
            int first_dig = 1;
            int last_dig = prod % 10;

            s2 += first_dig + last_dig;
        } else {
            s2 += prod;
        }
    }

    return !((s1 + s2) % 10);
}
