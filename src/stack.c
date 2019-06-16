#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

void stack_new(stack *stack, int dataSize, freeDataFunction freeData){
    stack->list = malloc(sizeof(list));
    list_new(stack->list, dataSize, freeData);
}

void stack_free(stack *stack){
    list_free(stack->list);
    stack->list = NULL;
}

int stack_get_data_size(stack* stack){
    return stack->list->dataSize;
}

int stack_get_count(stack* stack){
    return list_get_length(stack->list);
}

void stack_push(stack* stack, void* value){
    list_add_to_front(stack->list, value);
}

void stack_pop(stack* stack, void* value){
    assert(stack_get_count(stack) > 0);
    list_get_front(stack->list, value);
    list_delete_from_front(stack->list);
}

void stack_peek(stack* stack, void* value){

    assert(stack_get_count(stack) > 0);

    list_get_front(stack->list, value);
}