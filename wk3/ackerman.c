#include <stdio.h>
#include <stdlib.h>

int count = 0;
int *aman(int m, int n, int depth);

int main(int ac, char **av)
{
    // count: 2432
    // depth: 63
    // value: 61
    if (ac != 3)
        printf("idiot\n");

    int *res = aman(atoi(av[1]), atoi(av[2]), 1);
    printf("value is %d\n", res[0]);
    printf("depth is %d\n", res[1]);
    printf("count is %d\n", count);
}

int *aman(int m, int n, int depth)
{
    count++;

    int *res = (int *)malloc(2 * sizeof(int));
    if (m == 0) {
        res[0] = n + 1;
        res[1] = depth;
    }
    else if (m > 0 && n == 0) {
        res = aman(m -1 , 1, depth + 1);
    }
    else if (m > 0 && n > 0) {
        int *res1, *res2;
        res1 = aman(m, n-1, depth + 1);
        res2 = aman(m-1, res1[0], depth + 1);
        res[0] = res2[0];
        res[1] = res1[1] > res2[1] ? res1[1] : res2[1];
    }
    else
        fprintf(stderr, "function is not defined for negative values\n");

    return res;
}

