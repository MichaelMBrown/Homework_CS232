#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int *getRange(const int lower, const int upper) {
    int i;
    const int n = upper - lower + 1;
    int *array;

    if (n <= 0) {
        return NULL;
    }

    array = malloc(sizeof(int) * n);
    if (array == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        return NULL;
    }

    for (i = lower; i <= upper; i++) {
        array[i - lower] = i;
    }

    return array;
}

int main() {
    const int lower = 20;
    const int upper = 100;
    int *array = getRange(lower, upper);
    int i;

    if (array != NULL) {
        for (i = 0; i < upper - lower + 1; i++) {
            printf("%d\n", array[i]);
        }
    }
    free(array);
    return 0;
}
