//
// Created by Michael Brown on 07/12/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(int i);

int findMatches(FILE *primesFile, FILE *oddsFile) {
    FILE *pf = primesFile;
    FILE *of = oddsFile;

    //If primes.txt is empty, fill it with the first 100 primes
    if (pf == NULL) {
        pf = fopen("primes.txt", "w");
        for (int i = 2; i < 100; i++) {
            if (isPrime(i)) {
                fprintf(pf, "%d\n", i);
            }
        }
    }
    //If odds.txt is empty, fill it with the first 100 odd numbers
    if (of == NULL) {
        of = fopen("odds.txt", "w");
        for (int i = 1; i < 100; i++) {
            if (i % 2 == 1) {
                fprintf(of, "%d\n", i);
            }
        }
    }

    int prime = fscanf(pf, "%d", &prime);
    int odd = fscanf(of, "%d", &odd);

    int count = 0;
    while (prime != EOF && odd != EOF) {
        if (prime == odd) {
            count++;
        }
        prime = fscanf(pf, "%d", &prime);
        odd = fscanf(of, "%d", &odd);
    }
    fclose(pf);
    fclose(of);
    return count;
}

bool isPrime(int i) {
    if (i < 2) {
        return false;
    }
    return 1;
}

int main(int argc, const char *argv[]) {
    printf("%d\n", findMatches(fopen("primes.txt", "r"), fopen("odds.txt", "r")));
    return 0;
}
