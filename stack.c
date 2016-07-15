#include <stdlib.h>
#include <string.h>

typedef struct Stack {
	void **ptr;
	unsigned int nElements;
} Stack;

Stack* CreateStack(void) {
	Stack* stack = malloc(sizeof(*stack));
	if(stack) {
		memset(stack, 0, sizeof(*stack));
	}
	return stack;
}

unsigned int GetStackElementCount(const Stack *stack) {
	return stack->nElements;
}

void* TopStack(const Stack *stack) {
	return ((stack->ptr)[stack->nElements - 1]);
}

int PushStack(Stack *stack, void *item) {
	void **oldStack = stack->ptr;
	
	if(stack->ptr) {
		stack->ptr = realloc(stack->ptr, sizeof(*(stack->ptr)) * (stack->nElements + 1));
		if(!(stack->ptr)) {
			stack->ptr = oldStack;
			return -1;
		}
	}
	else {
		stack->ptr = malloc(sizeof(*(stack->ptr)));
		if(!(stack->ptr)) return -1;
	}
	
	(stack->ptr)[stack->nElements] = item;
	stack->nElements += 1;
	return 0;
}

void* PopStack(Stack *stack) {
	void *ret = 0;
	
	if(stack->nElements == 0) return 0;
	else if(stack->nElements == 1) {
		ret = *(stack->ptr);
		free(stack->ptr);
		stack->ptr = 0;
	}
	else {
		ret = (stack->ptr)[stack->nElements - 1];
		stack->ptr = realloc(stack->ptr, sizeof(*(stack->ptr)) * (stack->nElements - 1));
	}
	
	stack->nElements -= 1;
	return ret;
}

void ClearStack(Stack *stack) {
	if(stack->ptr) free(stack->ptr);
	stack->ptr = 0;
	stack->nElements = 0;
}

void FreeStack(Stack *stack) {
	if(stack->ptr) free(stack->ptr);
	free(stack);
}