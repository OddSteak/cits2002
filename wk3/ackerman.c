#include <stdio.h>
#include <stdlib.h>

int* aman(int m, int n, int depth, int count);

int main(int ac, char** av)
{
    // intput: 3 3
    // count: 2432
    // depth: 63
    // value: 61
    if (ac != 3) {
        printf("idiot\n");
        return 1;
    }

    int* res = aman(atoi(av[1]), atoi(av[2]), 1, 1);
    printf("\nvalue is %d\n", res[0]);
    printf("depth is %d\n", res[1]);
    printf("count is %d\n\n", res[2]);
}

int* aman(int m, int n, int depth, int count)
{
    int* res = (int*)malloc(3 * sizeof(int));

    if (m == 0) {
        res[0] = n + 1;
        res[1] = depth;
        res[2] = count;
    } else if (m > 0 && n == 0) {
        res = aman(m - 1, 1, depth + 1, count+1);
    } else if (m > 0 && n > 0) {
        int *res1, *res2;
        res1 = aman(m, n - 1, depth + 1, count+1);
        res2 = aman(m - 1, res1[0], depth + 1, count+1);
        res[0] = res2[0];
        res[1] = res1[1] > res2[1] ? res1[1] : res2[1];
        res[2] = res1[2] + res2[2] - count;
    } else {
        fprintf(stderr, "function is not defined for negative values\n");
        exit(EXIT_FAILURE);
    }

    return res;
}
