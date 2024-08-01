#include <stdio.h>

int new(int h)
{
    return 0;
}

int main()
{
    int h = 9;
    new(h++);
    printf("%d", h);
}
