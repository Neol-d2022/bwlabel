#define DEBUG

#include <stdlib.h>
#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#endif
#include "stack.h"

typedef struct coord {
	unsigned int i;
	unsigned int j;
} coord;

static int pathStart(Stack *stack, Stack *pstack, unsigned int **arr2D, unsigned int rows, unsigned int cols, unsigned int start_i, unsigned int start_j) {
	coord *coorStackElement;
	unsigned int i = start_i, j = start_j;
	
	ClearStack(stack);
	ClearStack(pstack);
	
#ifdef DEBUG
	fprintf(stderr, "pathStart called, rows = %u, cols = %u, i = %u, j = %u.\n", rows, cols, i, j);
#endif
	coorStackElement = (coord*)malloc(sizeof(*coorStackElement));
	if(!coorStackElement) return -1;
	coorStackElement->i = i;
	coorStackElement->j = j;
	if(PushStack(stack, coorStackElement)) return -1;
#ifdef DEBUG
	fprintf(stderr, "Current cord.(%u,%u) pushed into stack.\n", i, j);
#endif
	
	while(GetStackElementCount(stack) > 0) {
		if(i < rows - 1) {
			if(arr2D[i + 1][j] > 0) {
				coorStackElement = (coord*)malloc(sizeof(*coorStackElement));
				if(!coorStackElement) return -1;
				
				coorStackElement->i = i + 1;
				coorStackElement->j = j;
				if(PushStack(stack, coorStackElement)) return -1;
#ifdef DEBUG
				fprintf(stderr, "Downside cord.(%u,%u) pushed into stack.\n", i + 1, j);
#endif
			}
		}
		
		if(j > 1) {
			if(arr2D[i][j - 1] > 0) {
				coorStackElement = (coord*)malloc(sizeof(*coorStackElement));
				if(!coorStackElement) return -1;
				
				coorStackElement->i = i;
				coorStackElement->j = j - 1;
				if(PushStack(stack, coorStackElement)) return -1;
#ifdef DEBUG
				fprintf(stderr, "Leftside cord.(%u,%u) pushed into stack.\n", i, j - 1);
#endif
			}
		}
		
		if(i > 1) {
			if(arr2D[i - 1][j] > 0) {
				coorStackElement = (coord*)malloc(sizeof(*coorStackElement));
				if(!coorStackElement) return -1;
				
				coorStackElement->i = i - 1;
				coorStackElement->j = j;
				if(PushStack(stack, coorStackElement)) return -1;
#ifdef DEBUG
				fprintf(stderr, "Upside cord.(%u,%u) pushed into stack.\n", i - 1, j);
#endif
			}
		}
		
		if(j < cols - 1) {
			if(arr2D[i][j + 1] > 0) {
				coorStackElement = (coord*)malloc(sizeof(*coorStackElement));
				if(!coorStackElement) return -1;
				
				coorStackElement->i = i;
				coorStackElement->j = j + 1;
				if(PushStack(stack, coorStackElement)) return -1;
#ifdef DEBUG
				fprintf(stderr, "Rightside cord.(%u,%u) pushed into stack.\n", i, j + 1);
#endif
			}
		}
		
		coorStackElement = (coord*)malloc(sizeof(*coorStackElement));
		if(!coorStackElement) return -1;
		coorStackElement->i = i;
		coorStackElement->j = j;
		if(PushStack(pstack, coorStackElement)) return -1;
#ifdef DEBUG
		fprintf(stderr, "Current cord.(%u,%u) pushed into pstack.\n", i, j);
#endif
		
		arr2D[i][j] = 0;
		
		coorStackElement = PopStack(stack);
		i = coorStackElement->i;
		j = coorStackElement->j;
		free(coorStackElement);
#ifdef DEBUG
		fprintf(stderr, "Next cord.(%u,%u) popped from stack.\n", i, j);
#endif
	}
	
	return 0;
}

void bwlabel(unsigned int **arr2D, unsigned int rows, unsigned int cols, unsigned int *numLabels) {
	coord *coorStackElement;
	Stack *stack, **pstack, **oldpstack;
	unsigned int i, j, k, n;
	
#ifdef DEBUG
	fprintf(stderr, "bwlabel called, rows = %u, cols = %u.\n", rows, cols);
#endif
	
	n = 0;
	stack = CreateStack();
	if(!stack) return;
	pstack = malloc(sizeof(*pstack));
	if(!pstack) {
		FreeStack(stack);
		return;
	}
	if(numLabels) *numLabels = (unsigned int)-1;
	
	for(i = 0; i < rows; i += 1) {
		for(j = 0; j < cols; j += 1) {
			if(arr2D[i][j] <= 0) { 
#ifdef DEBUG
				fprintf(stderr, "(%u,%u) skipped.\n", i, j);
#endif
				continue;
			}
			
			pstack[n] = CreateStack();
			if(!(pstack[n])) {
				FreeStack(stack);
				for(k = 0; k < n; k += 1)
					FreeStack(pstack[k]);
				free(pstack);
				return;
			}
			
#ifdef DEBUG
			fprintf(stderr, "Found path start at (%u,%u), n = %u.\n", i, j, n);
#endif
			if(pathStart(stack, *(pstack + n), arr2D, rows, cols, i, j)) {
				FreeStack(stack);
				for(k = 0; k <= n; k += 1)
					FreeStack(pstack[k]);
				free(pstack);
				return;
			}
			
			oldpstack = pstack;
			if(!(pstack = realloc(pstack, sizeof(*pstack) * (n + 2)))) {
				pstack = oldpstack;
				FreeStack(stack);
				for(k = 0; k <= n; k += 1)
					FreeStack(pstack[k]);
				free(pstack);
				return;
			}
			
			n += 1;
		}
	}
	
#ifdef DEBUG
	fprintf(stderr, "Completed! n = %u\n", n);
#endif
	FreeStack(stack);
	for(k = 0; k < n; k += 1) {
		while(GetStackElementCount(pstack[k])) {
			coorStackElement = (coord*)PopStack(pstack[k]);
			arr2D[coorStackElement->i][coorStackElement->j] = k + 1;
			free(coorStackElement);
		}
		
		FreeStack(pstack[k]);
	}
	free(pstack);
	
	if(numLabels) *numLabels = n;
}