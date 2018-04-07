#include "list.h"
#include "test_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define AMOUNT_TO_ADD 10
#define VALUE_TO_ADD AMOUNT_TO_ADD+1
#define POS_TO_ADD AMOUNT_TO_ADD/2
#define EVEN_NUMBER 8
#define ODD_NUMBER EVEN_NUMBER+1


/* test to make sure list_new behaves correctly
*/
void test_list_new_int(){
	list list;

	list_new(&list, sizeof(int), NULL);

	/* length should be zero
	*/
	assert(list_get_length(&list) == 0);

	/* data size should be what was passed in
	*/
	assert(list.dataSize = sizeof(int));

	/* front and back should be null
	*/
	assert(list.front == NULL);
	assert(list.back == NULL);

	/* no function was passed in
	*/
	assert(list.freeData == NULL);

	list_free(&list);

	printf("Test list new int SUCCEEDED\n");
}

/* function to test that the list is appropriately nulled
*/
void test_list_free(){
	list list;

	int toAdd = VALUE_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add a value
	*/
	list_add_to_front(&list, &toAdd);

	/* free the list
	*/
	list_free(&list);

	/* make sure pointers are null
	*/
	assert(list.front == NULL);
	assert(list.back == NULL);
}

/* make sure add to front works when the list starts empty
*/
void test_list_add_to_front_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add the value
	*/
	list_add_to_front(&list, &toAdd);

	/* get the value in 3 different ways
	*/
	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	/* make sure all the values are correct
	*/
	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);

	/* make sure the length was incremented
	*/
	assert(list_get_length(&list) == 1);

	/* free the list
	*/
	list_free(&list);

	printf("Test list add to front from empty int SUCCEEDED\n");
}

/* test that length is correct
*/
void test_list_get_length()
{
	list list;

	int toAdd;

	toAdd=VALUE_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add a value
	*/
	list_add_to_front(&list, &toAdd);

	/* make sure the function returns what the struct has
	*/
	assert(list_get_length(&list) == list.length);

	/* make sure the value is correct
	*/
	assert(list_get_length(&list) == 1);

	/* free the list
	*/
	list_free(&list);

	printf("Test list get length SUCCEEDED\n");
}

/* test add to front when the list is not empty
*/
void test_list_add_to_front_non_empty_int(){
	list list;
	int valueToAdd, i, frontValue, posValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add some values
	*/
	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	/*local counter of length
	*/
	numberToAdd++;

	/* add the test value
	*/
	list_add_to_front(&list, &valueToAdd);

	/* get the various values
	*/
	list_get_front(&list, &frontValue);
	list_get_at_position(&list, &posValue, 0);

	/* make sure the test value is at the front
	*/
	assert(frontValue == valueToAdd);

	/* make sure the test value is at the front when obtained with pos function
	*/
	assert(posValue == valueToAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == numberToAdd);

	/* free list
	*/
	list_free(&list);

	printf("Test list add to front from non empty int SUCCEEDED\n");

}

/* test add to back when list is empty
*/
void test_list_add_to_back_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add the value
	*/	
	list_add_to_back(&list, &toAdd);

	/* get the value in different ways
	*/
	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	/* make sure the values are correct
	*/
	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);

	/* make sure the length is correct
	*/
	assert(list_get_length(&list) == 1);

	/* free list
	*/
	list_free(&list);

	printf("Test list add to back from empty int SUCCEEDED\n");

}

/* test add to back when list is not empty
*/
void test_list_add_to_back_non_empty_int(){
	list list;
	int valueToAdd, i, backValue, posValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add some values
	*/
	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	/* local length
	*/
	numberToAdd++;

	/* add to back
	*/
	list_add_to_back(&list, &valueToAdd);

	/* get the value in different ways
	*/
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, list_get_length(&list) - 1);

	/* make sure value is correct
	*/
	assert(backValue == valueToAdd);
	assert(posValue == valueToAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == numberToAdd);

	/* free list
	*/
	list_free(&list);

	printf("Test list add to back from non empty int SUCCEEDED\n");

}

/* test add to pos from empty add to zero
*/
void test_list_add_to_pos_zero_empty_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add to position 0
	*/
	list_add_to_position(&list, &toAdd, 0);

	/* make sure back front and 0 are all the same
	*/
	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == 1);

	/* free list*/
	list_free(&list);

	printf("Test list add to pos from empty to zero int SUCCEEDED\n");	
}

/* test add to position L when list is empty
*/
void test_list_add_to_pos_length_empty_int(){
	list list;

	int toAdd, position, frontValue, backValue, posValue;

	toAdd=VALUE_TO_ADD;

	/* create list
	*/
	list_new(&list, sizeof(int), NULL);

	/* get the length (=0)
	*/
	position = list_get_length(&list);

	/* add to position
	*/
	list_add_to_position(&list, &toAdd, position);

	/* get the values
	*/
	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, position);

	/* make sure all the values are the same
	*/
	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == 1);

	/* free list
	*/
	list_free(&list);

	printf("Test list add to pos from empty to length int SUCCEEDED\n");
}

/* test add to position when list is non empty
*/
void test_list_add_to_pos_non_empty_int(){
	list list;
	int valueToAdd, i, j, position, posValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	/* defined to be the middle of the list
	*/
	position = POS_TO_ADD;

	/* create list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add some values
	*/
	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_back(&list, &i);
	}

	/*length tracker
	*/
	numberToAdd++;

	/* add test value
	*/
	list_add_to_position(&list, &valueToAdd, position);

	/* get value at test position
	*/
	list_get_at_position(&list, &posValue, position);

	/* make sure the value obtained is the value added
	*/
	assert(posValue == valueToAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == numberToAdd);

	/* make sure the rest of the list is correct
	*/
	for(j=0;j<list_get_length(&list);j++)
	{
		list_get_at_position(&list, &posValue, j);
		if(j==position)
		{
			assert(posValue == valueToAdd);
		} else if(j > position){
			assert(posValue == j-1);
		} else {
			assert(posValue == j);
		}
	}

	/* free list
	*/
	list_free(&list);

	printf("Test list add to pos from non empty int SUCCEEDED\n");
}

/* test delete from front when list will be empty
*/
void test_list_delete_from_front_to_empty_int(){

	list list;

	int toAdd;

	toAdd=VALUE_TO_ADD;

	/* create list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add value
	*/
	list_add_to_front(&list, &toAdd);

	/* delete value
	*/
	list_delete_from_front(&list);

	/* make sure length is zero
	*/
	assert(list_get_length(&list) == 0);

	/* list is appropriately nulled
	*/
	assert(list.front == NULL);
	assert(list.back == NULL);

	/* free list
	*/
	list_free(&list);

	printf("Test list delete from front to empty int SUCCEEDED\n");
}

/* test delete from front when list will not be empty
*/
void test_list_delete_from_front_to_non_empty_int(){
	
	list list;
	int valueToAdd, i, frontValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	/* create list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add some values
	*/
	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	/* add test value
	*/
	list_add_to_front(&list, &valueToAdd);

	/* delete test value
	*/
	list_delete_from_front(&list);

	/* get front value
	*/
	list_get_front(&list, &frontValue);

	/* make sure front value is not what was added
	*/
	assert(frontValue != valueToAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == numberToAdd);

	/* free list
	*/
	list_free(&list);

	printf("Test list delete from front to non empty int SUCCEEDED\n");

}

/* test delete from back when list will be empty
*/
void test_list_delete_from_back_to_empty_int(){

	list list;

	int toAdd;

	toAdd=VALUE_TO_ADD;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add value
	*/
	list_add_to_front(&list, &toAdd);

	/* delete value
	*/
	list_delete_from_back(&list);

	/* make sure length is zero
	*/
	assert(list_get_length(&list) == 0);

	/* appropriately nulled
	*/
	assert(list.front == NULL);
	assert(list.back == NULL);

	/* free list
	*/
	list_free(&list);

	printf("Test list delete from back to empty int SUCCEEDED\n");
}

/* test delete from back when it won't be empty
*/
void test_list_delete_from_back_to_non_empty_int(){
	
	list list;
	int valueToAdd, i, backValue, numberToAdd;

	valueToAdd = VALUE_TO_ADD;
	numberToAdd = AMOUNT_TO_ADD;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add some values
	*/
	for(i=0;i<numberToAdd;i++)
	{
		list_add_to_front(&list, &i);
	}

	/* add test value
	*/
	list_add_to_back(&list, &valueToAdd);

	/* delete test value
	*/
	list_delete_from_back(&list);

	/* get value at the back
	*/
	list_get_back(&list, &backValue);

	/* make sure it's not the value that was added
	*/
	assert(backValue != valueToAdd);

	/* make sure length is correct
	*/
	assert(list_get_length(&list) == numberToAdd);

	/* free list
	*/
	list_free(&list);

	printf("Test list delete from back to non empty int SUCCEEDED\n");
}

/* test add/delete to/from front maintains correct state of list at all times
*/
void test_list_add_delete_front_each_position(){
	
	list list;
	int i, j, numberToAdd, frontValue, posValue, delFrontValue;

	numberToAdd = AMOUNT_TO_ADD;

	/* create list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add
	*/
	for(i=0;i<numberToAdd;i++)
	{
		/* make sure length is currently correct
		*/
		assert(list_get_length(&list) == i);

		/* add a value
		*/
		list_add_to_front(&list, &i);

		/* make sure length increments
		*/
		assert(list_get_length(&list) == i + 1);

		/* get the value just added
		*/
		list_get_front(&list, &frontValue);

		/* make sure it's the correct value
		*/
		assert(frontValue == i);

		/* check the rest of the list to make sure it wasn't corrupted
		*/
		for(j=0;j<i;j++)
		{
			list_get_at_position(&list, &posValue, j);
			assert(posValue == (i-j));
		}
	}

	/* delete
	*/
	for(i=list_get_length(&list) - 1;i>=0;i--)
	{
		/* make sure the length is currently correct
		*/
		assert(list_get_length(&list) == i + 1);

		/* get the value before it's deleted
		*/
		list_get_front(&list, &delFrontValue);

		/* delete the value
		*/
		list_delete_from_front(&list);

		/* make sure the length was decremented
		*/
		assert(list_get_length(&list) == i);

		/* can't get the value once the list is empty
		*/
		if(i > 0)
		{
			/* get the value that's now at the front
			*/
			list_get_front(&list, &frontValue);

			/* make sure it isn't equal to the value that was at the front before deletion
			*/
			assert(frontValue != delFrontValue);
		}

		/* make sure the rest of the list wasn't corrupted
		*/
		for(j=0;j<i;j++)
		{
			list_get_at_position(&list, &posValue, j);
			assert(posValue == (i-j)-1);
		}

	}

	/* free list
	*/
	list_free(&list);

	printf("Test list delete front each position SUCCEEDED\n");
}

/* test add/delete to/from back maintains correct state at all times
*/
void test_list_add_delete_back_each_position(){
	
	list list;
	int i, j, numberToAdd, backValue, posValue, delBackValue;

	numberToAdd = AMOUNT_TO_ADD;

	/* create list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add
	*/
	for(i=0;i<numberToAdd;i++)
	{
		/* make sure length is currently correct
		*/
		assert(list_get_length(&list) == i);

		/* add a value
		*/
		list_add_to_back(&list, &i);

		/* make sure it increments
		*/
		assert(list_get_length(&list) == i + 1);

		/* get the value just added
		*/
		list_get_back(&list, &backValue);

		/* make sure it's the correct value
		*/
		assert(backValue == i);

		/* check the rest of the list to make sure it wasn't corrupted
		*/
		for(j=0;j<i;j++)
		{
			list_get_at_position(&list, &posValue, j);
			assert(posValue == j);
		}
	}

	/* delete
	*/
	for(i=list_get_length(&list) - 1;i>=0;i--)
	{
		/* make sure the length is currently correct
		*/
		assert(list_get_length(&list) == i + 1);

		/* get the value before it's deleted
		*/
		list_get_back(&list, &delBackValue);

		/* delete the value
		*/
		list_delete_from_back(&list);

		/* make sure the length was decremented
		*/
		assert(list_get_length(&list) == i);

		/* can't get the value once the list is empty
		*/
		if(i > 0)
		{
			/* get the value that's now at the front
			*/
			list_get_back(&list, &backValue);

			/* make sure it isn't equal to the value that was at the front before deletion
			*/
			assert(backValue != delBackValue);
		}

		/* make sure the rest of the list wasn't corrupted
		*/
		for(j=0;j<i;j++)
		{
			list_get_at_position(&list, &posValue, j);
			assert(posValue == j);
		}

	}

	list_free(&list);

	printf("Test list delete back each position SUCCEEDED\n");
}

int compareInts(void* int1, void* int2){
	int first, second;

	first = *((int*)int1);
	second = *((int*)int2);

	if(first < second){
		return 1;
	} else if (first == second){
		return 0;
	} else {
		return -1;
	}

}

void test_list_sort_int_even(){

	list list;
	int value, i, posValue, previousValue, numberToAdd, originalLength;

	numberToAdd = EVEN_NUMBER;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++){
		value = rand() % numberToAdd;
		list_add_to_front(&list, &value);
	}

	originalLength = list_get_length(&list);

	list_merge_sort(&list, &compareInts);

	assert(originalLength == list_get_length(&list));

	list_get_at_position(&list, &previousValue, 0);

	for(i=1;i<numberToAdd;i++){
		list_get_at_position(&list, &posValue, i);

		assert(previousValue <= posValue);

		previousValue = posValue;
	}

	assert(list.back->next == NULL);
	assert(list.front->previous == NULL);

	list_free(&list);

	printf("Test list sort int even SUCCEEDED\n");
}

void test_list_sort_int_odd(){

	list list;
	int value, i, posValue, previousValue, numberToAdd, originalLength;

	numberToAdd = ODD_NUMBER;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++){
		value = rand() % numberToAdd;
		list_add_to_front(&list, &value);
	}

	originalLength = list_get_length(&list);

	list_merge_sort(&list, &compareInts);

	assert(originalLength == list_get_length(&list));

	list_get_at_position(&list, &previousValue, 0);

	for(i=1;i<numberToAdd;i++){
		list_get_at_position(&list, &posValue, i);

		assert(previousValue <= posValue);

		previousValue = posValue;
	}

	assert(list.back->next == NULL);
	assert(list.front->previous == NULL);

	list_free(&list);

	printf("Test list sort int odd SUCCEEDED\n");

}

void test_list_sort_sorted(){

	list list;
	int i, posValue, numberToAdd, originalLength;

	numberToAdd = AMOUNT_TO_ADD;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++){
		list_add_to_front(&list, &i);
	}

	originalLength = list_get_length(&list);

	list_merge_sort(&list, &compareInts);

	assert(originalLength == list_get_length(&list));

	for(i=0;i<numberToAdd;i++){
		list_get_at_position(&list, &posValue, i);

		assert(posValue == i);
	}

	assert(list.back->next == NULL);
	assert(list.front->previous == NULL);

	list_free(&list);

	printf("Test list sort int sorted SUCCEEDED\n");

}

void test_list_sort_reversed(){

	list list;
	int i, posValue, numberToAdd, originalLength;

	numberToAdd = AMOUNT_TO_ADD;

	/* new list
	*/
	list_new(&list, sizeof(int), NULL);

	for(i=0;i<numberToAdd;i++){
		list_add_to_back(&list, &i);
	}

	originalLength = list_get_length(&list);

	list_merge_sort(&list, &compareInts);

	assert(originalLength == list_get_length(&list));

	for(i=0;i<numberToAdd;i++){
		list_get_at_position(&list, &posValue, i);

		assert(posValue == i);
	}

	assert(list.back->next == NULL);
	assert(list.front->previous == NULL);

	list_free(&list);

	printf("Test list sort int reversed SUCCEEDED\n");

}

void test_list_sort_int_empty(){

	list list;

	list_new(&list, sizeof(int), NULL);

	list_merge_sort(&list, &compareInts);

	/* length should be zero
	*/
	assert(list_get_length(&list) == 0);

	/* data size should be what was passed in
	*/
	assert(list.dataSize = sizeof(int));

	/* front and back should be null
	*/
	assert(list.front == NULL);
	assert(list.back == NULL);

	/* no function was passed in
	*/
	assert(list.freeData == NULL);

	list_free(&list);

	printf("Test list sort empty SUCCEEDED\n");
}


/* make sure sorting a list of length 1 behaves correctly
*/
void test_list_sort_single_int(){
	list list;

	int toAdd, frontValue, backValue, posValue;

	toAdd = VALUE_TO_ADD;

	/* create the list
	*/
	list_new(&list, sizeof(int), NULL);

	/* add the value
	*/
	list_add_to_front(&list, &toAdd);

	list_merge_sort(&list, &compareInts);

	/* get the value in 3 different ways
	*/
	list_get_front(&list, &frontValue);
	list_get_back(&list, &backValue);
	list_get_at_position(&list, &posValue, 0);

	/* make sure all the values are correct
	*/
	assert(frontValue == toAdd);
	assert(backValue == toAdd);
	assert(posValue == toAdd);

	/* make sure the length was incremented
	*/
	assert(list_get_length(&list) == 1);

	/* free the list
	*/
	list_free(&list);

	printf("Test list sort single SUCCEEDED\n");
}

/* test new list using char*
*/
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

/* test list add with char*
*/
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

/* call all test functions
*/
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
	test_list_add_delete_front_each_position();
	test_list_add_delete_back_each_position();
	test_list_sort_int_even();
	test_list_sort_int_odd();
	test_list_sort_sorted();
	test_list_sort_reversed();
	test_list_sort_single_int();
	test_list_sort_int_empty();

	test_list_new_str();
	test_list_add_to_front_empty_str();
}
