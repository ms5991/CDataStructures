#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// helper function to allocate a new node
struct node* get_new_node(int dataSize, void* data){	

	// create new node on heap
	struct node *newNode = malloc(sizeof(struct node));

	// create space for the data
	newNode->data = malloc(dataSize);

	// this will prevent situations, for example, when the list is of ints,
	// where the caller passes in the address of an int on the stack and now
	// a node is pointing to the stack.  This will keep the node data pointers 
	// pointing to the heap. Of course, it's possible that data is a pointer type,
	// and it in turn is pointing to the stack, but we can't prevent that. 
	memcpy(newNode->data, data, dataSize);

	return newNode;
}

// initializes a new list
void list_new(list *list, int dataSize, freeDataFunction freeData){

	list->dataSize = dataSize;
	list->freeData = freeData;
	list->length = 0;
	list->front = NULL;
	list->back = NULL;
}

// frees dynamically allocated memory for this list
void list_free(list *list){

	struct node *currentNode;

	// loop through every node
	while(list->front != NULL){

		// advance the loop pointer
		currentNode = list->front;
		list->front = currentNode->next;

		// if there is a free function, call it on the data
		if(list->freeData != NULL){
			list->freeData(currentNode->data);
		}

		// even if there is a free function, still need to free
		// from the malloc in list_new
		free(currentNode->data);

		// free the node itself
		free(currentNode);
	}

	// front and back to NULL
	list->front = NULL;
	list->back = NULL;
}

// add a node to the front of the list
void list_add_to_front(list *list, void* data){

	// get a new node
	struct node *newNode = get_new_node(list->dataSize, data);

	// special case for the first node added
	if(list->length == 0){
		list->front = newNode;
		list->front->next = NULL;
		list->back = list->front;

	} else {		
		list->front->previous = newNode;
		newNode->next = list->front;
		list->front = newNode;
	}

	// always set the first node's previous to null
	list->front->previous = NULL;

	// increment length
	list->length++;
}

// add a node to the end of the list 
void list_add_to_back(list *list, void *data){

	// get a new node
	struct node *newNode = get_new_node(list->dataSize, data);

	// special case for the first node added
	if(list->length == 0){
		list->front = newNode;
		list->front->next = NULL;
		list->back = list->front;
		list->front->previous = NULL;

	} else {
		list->back->next = newNode;
		newNode->next = NULL;
		newNode->previous = list->back;
		list->back = newNode;
	}

	// increment length
	list->length++;
}

// add a node at some position in the list
void list_add_to_position(list *list, void* data, int position){
	assert(position >= 0);
	assert(position <= list->length);

	// add to front if pos = 0
	if(list->length == 0){ 
		list_add_to_front(list, data);
	// add to back if pos = length
	} else if(list->length == 0){
		list_add_to_back(list, data);
	} else {
		// get a new node
		struct node *newNode = get_new_node(list->dataSize, data);

		// loop pointer
		struct node *current;

		// slight optimization (factor of a constant 1/2): only iterate half the list in the worst case
		if(position < list->length / 2)
		{
			current = list->front;

			for(int i=0;i != position;i++){
				current = current->next;
			}

		} else {
			current = list->back;

			for(int i=list->length-1; i != position; i--){
				current = current->previous;
			}
		}

		newNode->previous = current->previous;
		current->previous->next = newNode;
		newNode->next = current;
		current->previous = newNode;

		list->length++;
	}
}

void list_delete_from_front(list *list){
	assert(list->length > 0);

	struct node* toDelete = list->front;

	if(toDelete->next == NULL){
		list->front = NULL;
		list->back = NULL;
	} else {
		toDelete->next->previous = NULL;
		list->front = toDelete->next;		
	}

	// if there is a free function, call it on the data
	if(list->freeData != NULL){
		list->freeData(toDelete->data);
	}

	// even if there is a free function, still need to free
	// from the malloc in list_new
	free(toDelete->data);

	// free the node itself
	free(toDelete);

	// decrement length
	list->length--;
}

void list_delete_from_back(list *list){
	assert(list->length > 0);

	struct node* toDelete = list->back;

	if(toDelete->previous == NULL){
		list->front = NULL;
		list->back = NULL;
	} else {
		toDelete->previous->next = NULL;
		list->back = toDelete->previous;		
	}

	// if there is a free function, call it on the data
	if(list->freeData != NULL){
		list->freeData(toDelete->data);
	}

	// even if there is a free function, still need to free
	// from the malloc in list_new
	free(toDelete->data);

	// free the node itself
	free(toDelete);

	// decrement length
	list->length--;
}

void list_delete_from_position(list* list, int position);

int list_get_length(list* list){
	return list->length;
}


void list_get_front(list* list, void* valuePtr){
	assert(list->front != NULL);
	memcpy(valuePtr, list->front->data, list->dataSize);
}

void list_get_back(list* list, void* valuePtr){
	assert(list->back != NULL);
	memcpy(valuePtr, list->back->data, list->dataSize);
}
void list_get_at_position(list* list, void* valuePtr, int position){
	assert(list->front != NULL);
	assert(position >= 0);
	assert(position < list->length);

	struct node *current;

	// slight optimization (factor of a constant 1/2): only iterate half the list in the worst case
	if(position < list->length / 2)
	{
		current = list->front;

		for(int i=0;i != position;i++){
			current = current->next;
		}

	} else {
		current = list->back;

		for(int i=list->length-1; i != position; i--){
			current = current->previous;
		}
	}

	memcpy(valuePtr, current->data, list->dataSize);
}

