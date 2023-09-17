#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "doubleStack.h"

int getOperatorPriority(const char *op);

char **toPolishNotation(char **tokens);

void handleArithmeticOperation(DoubleStack *operandStack, char *operation, int *check);

void handleTrigonometricOperation(DoubleStack *operandStack, char *operation, int *check);

void handleOtherOperations(DoubleStack *operandStack, char *operation, int *check);

double evaluatePolishNotation(char **polishTokens, double x);

#endif
