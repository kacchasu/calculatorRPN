#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct {
    char **items;
    int top;
    int capacity;
} Stack;

Stack createStack();
void push(Stack *stack, const char *item);
char* pop(Stack *stack);
char* peek(const Stack *stack);
int isEmpty(const Stack *stack);
void freeStack(Stack *stack);
char** stackToArray(const Stack *stack);

#endif // DATA_STRUCTURES_H
