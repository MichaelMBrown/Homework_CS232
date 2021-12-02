#include <printf.h>
#include <stdlib.h>
#include <string.h>

//define main method
int *getData() {
    int buffer[] = {1, 2};
    return buffer;
}

int main() {
    int *data = getData();
    int result = data[0] / data[1];
}
