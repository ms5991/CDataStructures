#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_list_new_int(){
	list list;

	list_new(&list, sizeof(int), NULL);

	assert(list_get_length(&list) == 0);
	assert(list.dataSize = sizeof(int));
	assert(list.front == NULL);
	assert(list.back == NULL);
	assert(list.freeData == NULL);

	list_free(&list);

	printf("Test list new int SUCCEEDED\n");
}

void test_list_add_to_front_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=5;

	list_new(&list, sizeof(int), NULL);

	list_add_to_front(&list, &toAdd);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list add to front from empty int SUCCEEDED\n");
}

void test_list_get_length()
{
	list list;

	int toAdd;

	toAdd=5;

	list_new(&list, sizeof(int), NULL);

	list_add_to_front(&list, &toAdd);

	assert(list_get_length(&list) == list.length);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list get length SUCCEEDED\n");
}


void test_list_add_to_front_non_empty_int(){
	list list;
	int valueToAdd, i, frontValue, backValue, posValue, numberToAdd;

	valueToAdd = 32;
	numberToAdd = 10;

	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	numberToAdd++;

	list_add_to_front(&list, &valueToAdd);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	assert(frontValue == valueToAdd);
	assert(backValue != valueToAdd);
	assert(posValue == valueToAdd);
	assert(list_get_length(&list) == numberToAdd);

	list_free(&list);

	printf("Test list add to front from non empty int SUCCEEDED\n");

}

void test_list_add_to_back_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=5;

	list_new(&list, sizeof(int), NULL);

	list_add_to_back(&list, &toAdd);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list add to back from empty int SUCCEEDED\n");

}


void test_list_add_to_back_non_empty_int(){
	list list;
	int valueToAdd, i, frontValue, backValue, posValue, numberToAdd;

	valueToAdd = 32;
	numberToAdd = 10;

	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	numberToAdd++;

	list_add_to_back(&list, &valueToAdd);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, list_get_length(&list) - 1);

	assert(frontValue != valueToAdd);
	assert(backValue == valueToAdd);
	assert(posValue == valueToAdd);
	assert(list_get_length(&list) == numberToAdd);

	list_free(&list);

	printf("Test list add to back from non empty int SUCCEEDED\n");

}

void test_list_new_str(){
	list list;

	list_new(&list, sizeof(char*), NULL);

	assert(list_get_length(&list) == 0);
	assert(list.dataSize = sizeof(char*));
	assert(list.front == NULL);
	assert(list.back == NULL);
	assert(list.freeData == NULL);

	list_free(&list);

	printf("Test list new str SUCCEEDED\n");
}

void test_list_add_to_front_empty_str(){
	list list;

	char* toAdd, *frontValue, *backValue, *posValue;

	toAdd="test";

	list_new(&list, sizeof(char*), NULL);

	list_add_to_front(&list, &toAdd);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	assert(strcmp(frontValue, toAdd) == 0);
	assert(strcmp(backValue, toAdd) == 0);
	assert(strcmp(posValue, toAdd) == 0);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list add to front from empty str SUCCEEDED\n");
}


void test_list_ptr_not_same()
{
	list list;

	char* toAdd, *frontValue, *backValue, *posValue;

	toAdd="test";

	list_new(&list, sizeof(char*), NULL);

	list_add_to_front(&list, &toAdd);
	list_add_to_front(&list, &toAdd);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);
	list_get_at_position(&list, &posValue, list_get_length(&list) - 1);

printf("F:%p B:%p P:%p ToAdd: %p\n", frontValue, backValue, posValue, toAdd);

	assert(frontValue != toAdd);
	assert(backValue != toAdd);

	assert(frontValue != backValue);
	assert(backValue == posValue);


	assert(strcmp(backValue, toAdd) == 0);
	assert(strcmp(posValue, toAdd) == 0);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list ptr not same SUCCEEDED\n");
}


void test_all_list_scenarios() {
	test_list_new_int();
	test_list_add_to_front_empty_int();
	test_list_get_length();
	test_list_add_to_front_non_empty_int();
	test_list_add_to_back_empty_int();
	test_list_add_to_back_non_empty_int();
	test_list_add_to_front_empty_str();
	test_list_new_str();
	test_list_ptr_not_same();
}
