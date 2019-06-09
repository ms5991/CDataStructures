#ifndef __LISTGUARD_H
#define __LISTGUARD_H

typedef void (*freeDataFunction)(void *);

typedef int (*compareValuesFunction)(void *, void*);

struct node {
    struct node* next;
    struct node* previous;
    void* data;
};

typedef struct {
    struct node* front;
    struct node* back;
    freeDataFunction freeData;
    int length;
    int dataSize;
} list;


void list_new(list *list, int dataSize, freeDataFunction freeData);

void list_free(list *list);

void list_add_to_front(list *list, void* data);

void list_add_to_back(list *list, void* data);

void list_add_to_position(list *list, void* data, int position);

void list_delete_from_front(list *list);

void list_delete_from_back(list *list);

void list_delete_from_position(list* list, int position);

int list_get_length(list* list);

void list_get_front(list* list, void* valuePtr);

void list_get_back(list* list, void* valuePtr);

void list_get_at_position(list* list, void* valuePtr, int position);

void list_merge_sort(list* list, compareValuesFunction compare);

#endif
