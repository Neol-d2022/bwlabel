#ifndef STACK
#define STACK

typedef struct Stack {
	void * const * const ptr;
	const unsigned int nElements;
} Stack;

Stack* CreateStack(void);
unsigned int GetStackElementCount(const Stack *stack);
void* TopStack(const Stack *stack);
int PushStack(Stack *stack, void *item);
void* PopStack(Stack *stack);
void ClearStack(Stack *stack);
void FreeStack(Stack *stack);

#endif