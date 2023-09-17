#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataStructures.h"
#include "polishNotation.h"

int getOperatorPriority(const char *op) {
    int res = 0;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        res = 1;
    }
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        res = 2;
    }
    if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "tan") == 0 ||
        strcmp(op, "ctg") == 0 || strcmp(op, "sqrt") == 0 || strcmp(op, "ln") == 0) {
        res = 3;
    }
    return res;
}

char **toPolishNotation(char **tokens) {
    Stack operators = createStack();
    Stack output = createStack();
    for (int i = 0; tokens[i] != NULL; ++i) {
        if (strcmp(tokens[i], "+") == 0 || strcmp(tokens[i], "-") == 0 ||
            strcmp(tokens[i], "*") == 0 || strcmp(tokens[i], "/") == 0) {
            while (!isEmpty(&operators) &&
                   getOperatorPriority(peek(&operators)) >= getOperatorPriority(tokens[i])) {
                push(&output, pop(&operators));
            }
            push(&operators, tokens[i]);
        } else if (strcmp(tokens[i], "(") == 0) {
            push(&operators, tokens[i]);
        } else if (strcmp(tokens[i], ")") == 0) {
            while (strcmp(peek(&operators), "(") != 0) {
                push(&output, pop(&operators));
            }
            pop(&operators);
        } else if (strcmp(tokens[i], "sin") == 0 || strcmp(tokens[i], "cos") == 0
            || strcmp(tokens[i], "tan") == 0 || strcmp(tokens[i], "ctg") == 0
            || strcmp(tokens[i], "sqrt") == 0 || strcmp(tokens[i], "ln") == 0) {
            push(&operators, tokens[i]);
        } else {
            push(&output, tokens[i]);
        }
    }
    while (!isEmpty(&operators))
        push(&output, pop(&operators));
    freeStack(&operators);
    char **polish = stackToArray(&output);
    freeStack(&output);
    return polish;
}

void handleArithmeticOperation(DoubleStack *operandStack, char *operation, int *check) {
    double a = popDouble(operandStack);
    double b = popDouble(operandStack);

    if (strcmp(operation, "+") == 0) {
        pushDouble(operandStack, b + a);
    } else if (strcmp(operation, "-") == 0) {
        pushDouble(operandStack, b - a);
    } else if (strcmp(operation, "*") == 0) {
        pushDouble(operandStack, b * a);
    } else if (strcmp(operation, "/") == 0) {
        if (a != 0) {
            pushDouble(operandStack, b / a);
        } else {
            *check = 1;
            printf("note: division by zero is not allowed\n");
        }
    }
}

void handleTrigonometricOperation(DoubleStack *operandStack, char *operation, int *check) {
    double a = popDouble(operandStack);

    if (strcmp(operation, "sin") == 0) {
        pushDouble(operandStack, sin(a));
    } else if (strcmp(operation, "cos") == 0) {
        pushDouble(operandStack, cos(a));
    } else if (strcmp(operation, "tan") == 0) {
        if (cos(a) != 0) {
            pushDouble(operandStack, tan(a));
        } else {
            *check = 1;
            printf("note: tan of pi/2 + n*pi is undefined\n");
        }
    } else if (strcmp(operation, "ctg") == 0) {
        if (sin(a) != 0) {
            pushDouble(operandStack, 1 / tan(a));
        } else {
            *check = 1;
            printf("note: cotangent of n*pi is undefined\n");
        }
    }
}

void handleOtherOperations(DoubleStack *operandStack, char *operation, int *check) {
    double a = popDouble(operandStack);

    if (strcmp(operation, "sqrt") == 0) {
        if (a >= 0) {
            pushDouble(operandStack, sqrt(a));
        } else {
            *check = 1;
            printf("note: square root of a negative number is undefined\n");
        }
    } else if (strcmp(operation, "ln") == 0) {
        if (a > 0) {
            pushDouble(operandStack, log(a));
        } else {
            *check = 1;
            printf("note: natural log of zero or negative number is undefined\n");
        }
    }
}

double evaluatePolishNotation(char **polishTokens, double x) {
    DoubleStack operandStack = createDoubleStack();
    int check = 0;

    for (int i = 0; polishTokens[i] != NULL && !check; ++i) {
        char *token = polishTokens[i];

        if (strcmp(token, "x") == 0) {
            pushDouble(&operandStack, x);
        } else if (strcmp(token, "-x") == 0) {
            pushDouble(&operandStack, -x);
        } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                   strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            handleArithmeticOperation(&operandStack, token, &check);
        } else if (strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 ||
                   strcmp(token, "tan") == 0 || strcmp(token, "ctg") == 0) {
            handleTrigonometricOperation(&operandStack, token, &check);
        } else if (strcmp(token, "sqrt") == 0 || strcmp(token, "ln") == 0) {
            handleOtherOperations(&operandStack, token, &check);
        } else {
            pushDouble(&operandStack, atof(token));
        }
    }

    double result = -10101010;
    if (!check) {
        result = popDouble(&operandStack);
        clearDoubleStack(&operandStack);
    } else if (operandStack.size != 0) {
        clearDoubleStack(&operandStack);
    }
    return result == 0 ? 0 : result;
}
