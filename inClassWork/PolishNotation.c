#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculatePolishNotation(char *expression);

int doTheMath(int first, char operator, int second);

void printStack(int *stack, int topOfStack);

enum {
    MAX_NUM_LENGTH = 100
};

double calculatePolishNotation(char *expression) {

    printf("\n************************** Poland Calculating ***************************\n\n");

    int len = strlen(expression);
    int *stack = malloc(sizeof(double) * len);
    int topOfStack = 0;

//    char c;

    char *numberBuffer = malloc(sizeof(char) * MAX_NUM_LENGTH);
    int numberIndex = 0;

    for (int i = 0; i < len; i++) {

        char c = expression[i];

        if (c == ' ') { //Is a space
            if (strlen(numberBuffer) != 0) { //If we were reading a number before this space
                numberBuffer[numberIndex + 1] = '\0';
                numberIndex = 0;

                //Put number on stack
                stack[topOfStack] = atoi(numberBuffer);
                topOfStack++;

                numberBuffer[0] = '\0'; //Reset buffer

                printStack(stack, topOfStack);
            }
        } else { //Not a space
            if (c >= '0' && c <= '9') { // Is a digit
                numberBuffer[numberIndex] = c;
                numberIndex++;
            } else { //Is an operator
                int second = stack[--topOfStack];
                int first = stack[--topOfStack];

                int result;


                //Do the math and put the result back on the stack
                result = doTheMath(first, c, second);
                stack[topOfStack] = result;
                topOfStack++;
                printStack(stack, topOfStack);
            }
        }
    }
    free(stack);
}

int doTheMath(int first, char operator, int second) {
    printf("Calculated %d %c %d\n\n", first, operator, second);

    switch (operator) {
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '*':
            return first * second;
        case '/':
            return first / second;
    }
}

void printStack(int *stack, int topOfStack) {

    int goBackToTop = topOfStack;

    printf("Stack:\n");
    while (topOfStack != 0) {
        printf("%d\n", stack[--topOfStack]);
    }

    printf("\n");
    topOfStack = goBackToTop;
}

int main(int argc, char *argv[]) {

    const int EXPRESSION_MAX_LENGTH = 1000;

    //Use command line
    calculatePolishNotation(argv[1]);

    char *expression = malloc(sizeof(char) * EXPRESSION_MAX_LENGTH);

    //Use standard input
    fgets(expression, EXPRESSION_MAX_LENGTH, stdin);
    calculatePolishNotation(expression);

    //Use a file
    FILE *f = fopen("polish.txt", "r");
    fgets(expression, EXPRESSION_MAX_LENGTH, f);
    calculatePolishNotation(expression);
}