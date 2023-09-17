#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressionParser.h"

char **tokenizeExpression(const char *expr) {
    int capacity = 10;
    int size = 0;
    char **tokens = malloc(capacity * sizeof(char *));
    int check = 0;
    if (tokens == NULL) check = 1;
    if(check == 0) {
        int i = 0;
        while (expr[i] && !check && expr[i] != '\0') {
            while (expr[i] == ' ' || expr[i] == '\t') i++;
            if (expr[i] != '\0') {
                int start = i;
                if (strchr("+-*/()", expr[i]) != NULL) {
                    if (expr[i] == '-' && (i == 0 || strchr("+-*/(", expr[i - 1]) != NULL)) {
                        i++;
                        while ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.' || expr[i] == 'x') i++;
                    } else
                        i++;
                } else if ((expr[i] >= 'a' && expr[i] <= 'z') || (expr[i] >= 'A' && expr[i] <= 'Z')) {
                    while ((expr[i] >= 'a' && expr[i] <= 'z') || (expr[i] >= 'A' && expr[i] <= 'Z')) i++;
                } else
                    while ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.') i++;
                int end = i;
                char *token = malloc((end - start + 1) * sizeof(char));
                strncpy(token, expr + start, end - start);
                token[end - start] = '\0';
                if (size >= capacity) {
                    capacity *= 2;
                    tokens = realloc(tokens, capacity * sizeof(char *));
                    if (tokens == NULL) check = 1;
                }
                if (!check) tokens[size++] = token;
            }
        }
        if(!check) tokens[size] = NULL;
    }
    if(check) {
        free(tokens);
        tokens = NULL;
    }
    return tokens;
}

