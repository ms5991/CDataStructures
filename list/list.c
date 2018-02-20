#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void list_new(list *list, int dataSize, freeDataFunction freeData){

	list->dataSize = dataSize;
	list->freeData = freeData;
	list->length = 0;
	list->front = NULL;
	list->back = NULL;
}

void list_free(list *list){

	struct node *currentNode;

	while(list->front != NULL){
		currentNode = list->front;
		list->front = currentNode->next;

		// if there is a free function, call it
		if(list->freeData != NULL){
			list->freeData(currentNode->data);
		}

		// even if there is a free function, still need to free
		// from the malloc in list_new
		free(currentNode->data);
		free(currentNode);
	}
}


void list_add_to_front(list *list, void* data){

	// create the new node on the heap
	struct node *newNode = malloc(sizeof(struct node));

	// data on the heap too
	newNode->data = malloc(list->dataSize);

	// copy the data to the new node on the heap
	// let's the caller not have to worry about malloc
	memcpy(newNode->data, data, list->dataSize);

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

void list_add_to_back(list *list, void *data){

	struct node *newNode = malloc(sizeof(struct node));

	newNode->data = malloc(list->dataSize);

	memcpy(newNode->data, data, list->dataSize);

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

	list->length++;
}

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
	if(position < list->length / 2)
	{
		current = list->front;

		for(int i=0;i != position;i++){
			current = current->next;
		}

	} else {
		current = list->back;

		for(int i=list->length-1; i != position ;i--){
			current = current->previous;
		}
	}

	memcpy(valuePtr, current->data, list->dataSize);
}

