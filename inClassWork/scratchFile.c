//
// Created by Michael Brown on 9/7/21.
//
#include <string.h>
#include <stdbool.h>
#include "stdio.h"

int main() {
    
    char originString[] = "  It's   good  to  see  you  ";
    const int len = strlen(originString);
    char modString[len];
    bool foundSpace = false;
    int buildIndex = 0;

    for (int i = 0; i < len; ++i) {
        if (originString[i] == ' ') {
            if (!foundSpace) {
                foundSpace = true;
                modString[buildIndex] = ' ';
                buildIndex++;
            }
        } else {
            modString[buildIndex] = originString[i];
            buildIndex++;
            foundSpace = false;
        }
    }

    printf("Comparing Strings...\n");
    printf("Origin String: %s\n", originString);
    printf("Modified String: %s\n", modString);
}
