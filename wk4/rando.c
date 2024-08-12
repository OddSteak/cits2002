#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void fill_arr(int *arr, int size);
void pretty_print(int *arr, int size);
void head(int *arr, int size);

int main()
{
    int test[10] = {0};

    pretty_print(test, 10);
    fill_arr(test, 10);
    pretty_print(test, 10);
    head(test, 10);
    pretty_print(test, 10);
    return 0;
}

void fill_arr(int *arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void pretty_print(int *arr, int size)
{
    printf("{ ");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d ", arr[size-1]);
    printf("}\n");
}

void head(int *arr, int size)
{
    int max = INT_MIN;
    int max_idx = -1;

    for (int i = 0; i <size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            max_idx = i;
        }
    }

    for (int i = max_idx; i > 0; i--) {
        arr[i] = arr[i - 1];
    }

    arr[0] = max;
}
