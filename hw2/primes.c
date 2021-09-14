#include <stdlib.h>
#include <stdio.h>
#include <MacTypes.h>

int lowerBound, upperBound;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

int main(int argc, const char **argv) {


    if (argc != 3) {
        fprintf(stderr, "USAGE: %s lowerBound upperBound\n", argv[0]);
        return -1;
    }

    lowerBound = atoi(argv[1]);
    upperBound = atoi(argv[2]);

    if (lowerBound < 1 || upperBound < 1) {
        fprintf(stderr, "ERROR: both the lowerBound (%d) and the upperBound (%d) must be positive.\n", lowerBound,
                upperBound);
        return -2;
    } else {
        int currentIndex = lowerBound;
        Boolean isPrime = false;
        do {
            if (currentIndex <= upperBound) {
                if (currentIndex % 2 == 0) {
                    isPrime = false;
                } else {
                    isPrime = true;
                }
                if (currentIndex == 2) isPrime = true;
            } else break;
            if (isPrime && currentIndex != 1) {
                printf("%d \n", currentIndex);
            }
            ++currentIndex;
        } while (currentIndex / 2);
    }
    return 0;
}

#pragma clang diagnostic pop

