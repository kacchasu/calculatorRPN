#include "polishNotation.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "expressionParser.h"
#include <string.h>
#include <math.h>

int isValidExpression(char **tokens) {
    int numOperands = 0;
    int numOperators = 0;
    int openBrackets = 0;
    int unaryFunctions = 0;
    int check = 0;
    for (int i = 0; tokens[i] != NULL; ++i) {
        if (!check) {
            if (strcmp(tokens[i], "+") == 0 || strcmp(tokens[i], "*") == 0 ||
                strcmp(tokens[i], "/") == 0) {
                numOperators++;
            } else if (strcmp(tokens[i], "-") == 0) {
                if (i == 0 || strcmp(tokens[i - 1], "(") == 0) {
                } else {
                    numOperators++;
                }
            } else if (strcmp(tokens[i], "tan") == 0 || strcmp(tokens[i], "ctg") == 0 ||
                       strcmp(tokens[i], "sqrt") == 0 || strcmp(tokens[i], "ln") == 0 ||
                       strcmp(tokens[i], "sin") == 0 || strcmp(tokens[i], "cos") == 0) {
                numOperators++;
                unaryFunctions++;
            } else if (strcmp(tokens[i], "(") == 0) {
                openBrackets++;
            } else if (strcmp(tokens[i], ")") == 0) {
                openBrackets--;
                if (openBrackets < 0)
                    check = 1;
            } else if (strcmp(tokens[i], "-x") == 0 || strcmp(tokens[i], "x") == 0 || atof(tokens[i]) != 0 ||
                       strcmp(tokens[i], "0") == 0 || strcmp(tokens[i], "-0") == 0) {
                numOperands++;
            } else {
                check = 1;
            }
        }
    }
    if (openBrackets != 0) {
        check = 1;
    }
    if (numOperands != numOperators - unaryFunctions + 1) check = 1;
    return check == 1 ? 0 : 1;
}

int main() {
    printf("--- enter an expression ---\n");
    char expr[100];
    fgets(expr, sizeof(expr), stdin);
    expr[strlen(expr) - 1] = '\0';
    int check = 0;
    char **tokens = tokenizeExpression(expr);
    if (tokens == NULL) {
        printf("memory allocation failed during tokenization\n");
        check = 1;
    }
    if (!check) {
        if (!isValidExpression(tokens)) {
            printf("invalid expression\n");
            check = 1;
        }
        if(!check) {
            printf("tokens: ");
            for (int i = 0; tokens[i] != NULL; ++i) {
                printf("%s ", tokens[i]);
            }
            printf("\n");
            char **polishTokens = toPolishNotation(tokens);
            if (polishTokens == NULL) {
                printf("memory allocation failed during Polish notation conversion\n");
                check = 1;
            }
            if(!check) {
                printf("polish tokens: ");
                for (int i = 0; polishTokens[i] != NULL; ++i) {
                    printf("%s ", polishTokens[i]);
                }
                printf("\n");
                printf("result: %f\n", evaluatePolishNotation(polishTokens, M_PI));
                drawGraph(polishTokens);
                free(polishTokens);
            }
        }
        free(tokens);
    }
    return 0;
}