#ifndef Stack_H
#define Stack_H

typedef struct{
	char dummy;
} Stack;

Stack *stackNew(void);
void push(Stack *stack, void *data);
void *pop(Stack *stack);

#endif // Stack_H
