#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


void split_list(list*, list*, list*);
void merge_list_node(list* originalList, struct node*, struct node*, compareValuesFunction);

// helper function to allocate a new node
struct node* get_new_node(int dataSize, void* data){

    // create new node on heap
    struct node *newNode; 

    newNode = malloc(sizeof(struct node));

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
    struct node *newNode;

    newNode = get_new_node(list->dataSize, data);

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
    struct node *newNode;

    newNode = get_new_node(list->dataSize, data);

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
    
    int i;

    // Assert position is within valid range
    assert(position >= 0);
    assert(position <= list->length);

    // add to front if pos = 0
    if(position == 0){ 
        list_add_to_front(list, data);
    // add to back if pos = length
    } else if(position == list->length){
        list_add_to_back(list, data);
    } else {
        // get a new node
        struct node *newNode = get_new_node(list->dataSize, data);

        // loop pointer
        struct node *current;
        
        current = list->front;

        for(i=0;i != position;i++){
            current = current->next;
        }

        newNode->previous = current->previous;
        current->previous->next = newNode;
        newNode->next = current;
        current->previous = newNode;

        list->length++;
    }
}

// delete the node at the front of the list
void list_delete_from_front(list *list){

    struct node* toDelete;

    assert(list->length > 0);

    toDelete = list->front;

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

// delete the node from the back of the list
void list_delete_from_back(list *list){

    struct node* toDelete;

    assert(list->length > 0);

    toDelete = list->back;

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

// delete the node at some position in the list
void list_delete_from_position(list* list, int position){

    int i;

    // Assert position is within valid range
    assert(position >= 0);
    assert(position < list->length);

    // delete from front if pos = 0
    if(position == 0){ 
        list_delete_from_front(list);
    // delete from back if pos = length-1
    } else if(list->length == (list->length) - 1){
        list_delete_from_back(list);
    } else {

        // loop pointer
        struct node *current;

        current = list->front;

        for(i=0;i != position;i++){
            current = current->next;
        }

        // adjust pointers of surrounding nodes
        // next and previous will not be null because this is not the front or back node
        current->next->previous = current->previous;
        current->previous->next = current->next;

        // if there is a free function, call it on the data
        if(list->freeData != NULL){
            list->freeData(current->data);
        }

        // even if there is a free function, still need to free
        // from the malloc in list_new
        free(current->data);

        // free the node itself
        free(current);

        // decrement length
        list->length--;
    }
}

// get the length of the list
int list_get_length(list* list){
    return list->length;
}

// get the value at the front of the list
void list_get_front(list* list, void* valuePtr){
    assert(list->front != NULL);

    // copy the data so there isn't an aliased ptr
    memcpy(valuePtr, list->front->data, list->dataSize);
}

// get the value at the back of the list
void list_get_back(list* list, void* valuePtr){
    assert(list->back != NULL);

    // copy the data so there isnt' an aliased ptr
    memcpy(valuePtr, list->back->data, list->dataSize);
}


// get the value at some position in the list
void list_get_at_position(list* list, void* valuePtr, int position){

    struct node *current;
    int i;

    // Assert position is within valid range
    assert(list->front != NULL);
    assert(position >= 0);
    assert(position < list->length);

    current = list->front;

    for(i=0;i != position;i++){
        current = current->next;
    }

    // copy the value so there isn't an aliased ptr
    memcpy(valuePtr, current->data, list->dataSize);
}


void list_merge_sort(list* originalList, compareValuesFunction compare){
    
    list firstHalf, secondHalf;

    // list of length 0 or 1 is sorted
    if(originalList->length <= 1) return; 

    // new lists
    list_new(&firstHalf, originalList->dataSize, originalList->freeData);
    list_new(&secondHalf, originalList->dataSize, originalList->freeData);

    // split the list into first half and second half
    split_list(originalList, &firstHalf, &secondHalf);

    // sort the two halves
    list_merge_sort(&firstHalf, compare);
    list_merge_sort(&secondHalf, compare);

    merge_list_node(originalList, firstHalf.front, secondHalf.front, compare);
}

void split_list(list* originalList, list* firstHalf, list* secondHalf){	
    int originalLength, midPoint, i;
    struct node *traversal;

    // Calculate the lengths
    originalLength = list_get_length(originalList);
    midPoint = originalLength / 2;
    // Find the midpoint and set the fronts
    firstHalf->front = originalList->front;
    traversal = firstHalf->front;

    for(i=0;i<midPoint;i++){
        traversal = traversal->next;
    }

    // set front and back for second half
    secondHalf->front = traversal;
    secondHalf->back = originalList->back;

    if(traversal->previous != NULL){
        firstHalf->back = traversal->previous;
    } else{
        firstHalf->back = traversal;
    }

    secondHalf->front->previous->next = NULL;
    secondHalf->front->previous = NULL;

    // set the lengths
    firstHalf->length = midPoint;
    secondHalf->length = originalLength - midPoint;
}

void merge_list_node(list* originalList, struct node* first, struct node* second, compareValuesFunction compare){
    int compareValue;
    struct node* frontFirst, *frontSecond, *traversal;

    // If first or second is null, just return the other one, because it is sorted
    if(first == NULL){
        originalList->front = second;

        traversal = second;

        // find the back
        while(traversal->next != NULL)
        {
            traversal = traversal->next;
        }

        originalList->back = traversal;

    } else if(second == NULL){
        originalList->front = first;

        traversal = first;

        // find the back
        while(traversal->next != NULL)
        {
            traversal = traversal->next;
        }

        originalList->back = traversal;
    } else{

        // compare the first ones
        compareValue = compare(first->data, second->data);

        if(compareValue > 0){
            originalList->front = first;
            frontFirst = first->next;
            frontSecond = second;
        } else{
            originalList->front = second;
            frontSecond = second->next;
            frontFirst = first;
        }

        // set the front
        traversal = originalList->front;

        traversal->previous = NULL;

        while(frontFirst != NULL || frontSecond != NULL)
        {
            // compare the fronts
            if(frontFirst == NULL){
                compareValue = -1;
            } else if (frontSecond == NULL){
                compareValue = 1;
            } else {
                compareValue = compare(frontFirst->data, frontSecond->data);
            }

            // take the bigger one and set pointers
            if(compareValue > 0){
                traversal->next = frontFirst;
                traversal->next->previous = traversal;
                traversal = traversal->next;

                frontFirst = frontFirst->next;

            } else{

                traversal->next = frontSecond;
                traversal->next->previous = traversal;
                traversal = traversal->next;
                
                frontSecond = frontSecond->next;
            }
        }

        // list->back->next == NULL
        traversal->next = NULL;

        // set the back
        originalList->back = traversal;
    }
}

