#include <stdio.h>
#include <stdlib.h>

int count = 0;
int max_depth = 0;
int aman(int m, int n, int depth);

int main(int ac, char **av)
{
    if (ac != 3)
        printf("idiot\n");

    printf("result is %d\n", aman(atoi(av[1]), atoi(av[2]), 1));
    printf("count is %d\n", count);
    printf("depth is %d\n", max_depth);
}

int aman(int m, int n, int depth)
{
    if (depth > max_depth)
        max_depth = depth;
    count++;
    if (m == 0) {
        return n+1;
    }
    else if (m > 0 && n == 0) {
        return aman(m - 1, 1, depth+1);
    }
    else if (m > 0 && n > 0) {
        return aman(m - 1, aman(m, n-1, depth + 1), depth + 1);
    }
    else
        fprintf(stderr, "function is not defined for negative values\n");

    return 0;
}

