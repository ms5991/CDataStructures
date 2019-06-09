#include "stack.h"
#include "test_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define VALUE_TO_ADD 8
#define AMOUNT_TO_ADD 7

void test_stack_new_int(){
    stack stack;

    stack_new(&stack, sizeof(int), NULL);

    /* length should be zero
    */
    assert(stack_get_count(&stack) == 0);

    /* data size should be what was passed in
    */
    assert(stack_get_data_size(&stack) == sizeof(int));

    stack_free(&stack);

    printf("Test stack new int SUCCEEDED\n");

}

void test_stack_free(){
    stack stack;
    int toAdd;

    stack_new(&stack, sizeof(int), NULL);

    toAdd = VALUE_TO_ADD;

    stack_push(&stack, &toAdd);

    stack_free(&stack);

    assert(stack.list == NULL);

    printf("Test stack free int SUCCEEDED\n");
}

void test_stack_push_empty(){
    
    stack stack;
    int toAdd, peekVal;

    stack_new(&stack, sizeof(int), NULL);

    toAdd = VALUE_TO_ADD;

    stack_push(&stack, &toAdd);

    assert(stack_get_count(&stack) == 1);

    stack_peek(&stack, &peekVal);

    assert(peekVal == toAdd);

    stack_free(&stack);

    printf("Test stack push empty int SUCCEEDED\n");
}

void test_stack_get_length(){
    stack stack;
    int i;

    stack_new(&stack, sizeof(int), NULL);

    for(i=0;i<AMOUNT_TO_ADD;i++){
        stack_push(&stack, &i);
    }

    assert(stack_get_count(&stack) == AMOUNT_TO_ADD);

    stack_free(&stack);

    printf("Test stack get length int SUCCEEDED\n");

}

void test_stack_push_non_empty(){
    stack stack;
    int first, second, peekVal;

    stack_new(&stack, sizeof(int), NULL);

    first = VALUE_TO_ADD;
    second = VALUE_TO_ADD + 1;

    stack_push(&stack, &first);
    stack_push(&stack, &second);

    stack_peek(&stack, &peekVal);

    assert(stack_get_count(&stack) == 2);
    assert(peekVal == second);


    stack_free(&stack);

    printf("Test stack push non empty int SUCCEEDED\n");

}

void test_stack_pop_to_empty(){}

void test_stack_pop_to_non_empty(){}

void test_stack_new_str(){}

void test_stack_push_empty_str(){}


void test_all_stack_scenarios(){

    printf("======= STACK TESTS ========\n");

    test_stack_new_int();
    test_stack_free();
    test_stack_get_length();
    test_stack_push_empty();
    test_stack_push_non_empty();
    test_stack_pop_to_empty();
    test_stack_pop_to_non_empty();
    test_stack_new_str();
    test_stack_push_empty_str();
}