#include<stdio.h>
#include <stdlib.h>

void getPowers(int x, int *pxSqr, int *pxCube) {
    *pxSqr = x * x;
    *pxCube = *pxSqr * x;
}

int main() {
    int x, xSqr, xCube;
    x = 3;
    getPowers(x, &xSqr, &xCube);
    printf("%d %d %d", x, xSqr, xCube);
}

