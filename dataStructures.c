#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructures.h"

Stack createStack() {
    Stack stack;
    stack.top = -1;
    stack.capacity = 10;
    stack.items = (char **)malloc(stack.capacity * sizeof(char *));
    return stack;
}

void push(Stack *stack, const char *item) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->items = (char **)realloc(stack->items, stack->capacity * sizeof(char *));
    }
    stack->items[++(stack->top)] = strdup(item);
}

char* pop(Stack *stack) {
    char *item = stack->items[stack->top];
    stack->items[stack->top] = NULL;
    stack->top--;
    return item;
}

char* peek(const Stack *stack) {
    return stack->items[stack->top];
}

int isEmpty(const Stack *stack) {
    return stack->top == -1;
}

void freeStack(Stack *stack) {
    for (int i = 0; i <= stack->top; ++i) {
        free(stack->items[i]);
    }
    free(stack->items);
}

char** stackToArray(const Stack *stack) {
    int length = (stack->top + 2);
    char **array = (char **)malloc(length * sizeof(char *));

    for (int i = 0; i <= stack->top; ++i) {
        array[i] = strdup(stack->items[i]);
    }
    array[stack->top + 1] = NULL;
    return array;
}
