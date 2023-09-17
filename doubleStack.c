#include <stdio.h>
#include <stdlib.h>
#include "doubleStack.h"

DoubleStack createDoubleStack() {
    DoubleStack stack;
    stack.size = 0;
    stack.capacity = 10;
    stack.data = malloc(stack.capacity * sizeof(double));
    return stack;
}

void pushDouble(DoubleStack *stack, double value) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(double));
    }
    stack->data[stack->size++] = value;
}

double popDouble(DoubleStack *stack) {
    return stack->data[--stack->size];
}

void clearDoubleStack(DoubleStack *stack) {
    stack->size = 0;
    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
}
