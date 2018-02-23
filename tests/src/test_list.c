#include "list.h"
#include "test_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define AMOUNT_TO_ADD 10
#define VALUE_TO_ADD AMOUNT_TO_ADD+1
#define POS_TO_ADD AMOUNT_TO_ADD/2

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

void test_list_free(){
	list list;

	int toAdd = VALUE_TO_ADD;

	list_new(&list, sizeof(int), NULL);
	list_add_to_front(&list, &toAdd);
	list_free(&list);

	assert(list.front == NULL);
	assert(list.back == NULL);
}

void test_list_add_to_front_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

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

	toAdd=VALUE_TO_ADD;

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

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

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

	toAdd=VALUE_TO_ADD;

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

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

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

void test_list_add_to_pos_zero_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	list_add_to_position(&list, &toAdd, 0);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list add to pos from empty to zero int SUCCEEDED\n");	
}

void test_list_add_to_pos_length_empty_int(){
	list list;

	int toAdd, position, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	position = list_get_length(&list);

	list_add_to_position(&list, &toAdd, position);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, position);

	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);
	assert(list_get_length(&list) == 1);

	list_free(&list);

	printf("Test list add to pos from empty to length int SUCCEEDED\n");
}

void test_list_add_to_pos_non_empty_int(){
	list list;
	int valueToAdd, i, position, frontValue, backValue, posValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;
	position = POS_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	numberToAdd++;

	list_add_to_position(&list, &valueToAdd, position);

	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, position);

	assert(posValue == valueToAdd);
	assert(list_get_length(&list) == numberToAdd);

	list_free(&list);

	printf("Test list add to pos from non empty int SUCCEEDED\n");
}


void test_list_delete_from_front_to_empty_int(){

	list list;

	int toAdd;

	toAdd=VALUE_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	list_add_to_front(&list, &toAdd);

	list_delete_from_front(&list);

	assert(list_get_length(&list) == 0);
	assert(list.front == NULL);
	assert(list.back == NULL);

	list_free(&list);

	printf("Test list delete from front to empty int SUCCEEDED\n");
}

void test_list_delete_from_front_to_non_empty_int(){
	
	list list;
	int valueToAdd, i, frontValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	list_delete_from_front(&list);

	list_get_front(&list, &frontValue);
	assert(list_get_length(&list) == numberToAdd - 1);
	assert(frontValue != valueToAdd);

	list_free(&list);

	printf("Test list delete from front to non empty int SUCCEEDED\n");

}

void test_list_delete_from_back_to_empty_int(){

	list list;

	int toAdd;

	toAdd=VALUE_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	list_add_to_front(&list, &toAdd);

	list_delete_from_back(&list);

	assert(list_get_length(&list) == 0);
	assert(list.front == NULL);
	assert(list.back == NULL);

	list_free(&list);

	printf("Test list delete from back to empty int SUCCEEDED\n");
}

void test_list_delete_from_back_to_non_empty_int(){
	
	list list;
	int valueToAdd, i, backValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	list_delete_from_back(&list);

	list_get_back(&list, &backValue);
	assert(list_get_length(&list) == numberToAdd - 1);
	assert(backValue != valueToAdd);

	list_free(&list);

	printf("Test list delete from back to non empty int SUCCEEDED\n");
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

void test_all_list_scenarios() {
	test_list_new_int();
	test_list_free();
	test_list_add_to_front_empty_int();
	test_list_get_length();
	test_list_add_to_front_non_empty_int();
	test_list_add_to_back_empty_int();
	test_list_add_to_back_non_empty_int();
	test_list_add_to_pos_zero_empty_int();
	test_list_add_to_pos_length_empty_int();
	test_list_add_to_pos_non_empty_int();
	test_list_delete_from_front_to_empty_int();
	test_list_delete_from_front_to_non_empty_int();
	test_list_delete_from_back_to_empty_int();
	test_list_delete_from_back_to_non_empty_int();
	test_list_new_str();
	test_list_add_to_front_empty_str();
}
