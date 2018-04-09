#ifndef __STACKGUARD_H
#define __STACKGUARD_H

#include "list.h"

typedef struct {
	list* list;
} stack;


void stack_new(stack *stack, int dataSize, freeDataFunction freeData);

void stack_free(stack* stack);

int stack_get_count(stack* stack);

int stack_get_data_size(stack* stack);

void stack_push(stack* stack, void* value);

void stack_pop(stack* stack, void* value);

void stack_peek(stack* stack, void* value);

#endif