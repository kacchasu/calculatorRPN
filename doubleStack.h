#ifndef DOUBLE_STACK_H
#define DOUBLE_STACK_H

typedef struct {
    double *data;
    int size;
    int capacity;
} DoubleStack;

DoubleStack createDoubleStack();

void pushDouble(DoubleStack *stack, double value);

double popDouble(DoubleStack *stack);

void clearDoubleStack(DoubleStack *stack);

#endif // DOUBLE_STACK_H
