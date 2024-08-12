#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool superloop(int n, int arr[n], int lim);
void pretty_print(int *arr, int size);

int main()
{
    int arr[3] = {0, 0, 0};

    do {
        pretty_print(arr, 3);
    }
    while (superloop(3, arr, 10));

    return 0;
}

// modifies array for next iteration and returns true if the loop should continue after every call
bool superloop(int n, int state[n], int lim)
{
    for (int i = n - 1; i >= 0; i--) {
        if (state[i] < lim) {
            state[i]++;

            for (int j = i+1; j < n; j++) {
                state[j] = 0;
            }

            return true;
        }
    }
    return false;
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
