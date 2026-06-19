#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "string.h"
#include <stdbool.h>

typedef struct List LinkedList;

LinkedList* list_create();

LinkedList* list_insert(LinkedList* list, String* key);

//void list_remove(LinkedList* list, String* key); // precisa?

//precisa?
//LinkedList* list_contains(LinkedList* list, String* key);

String* list_remove_first(LinkedList* list);

bool list_empty(LinkedList* list);

void list_destroy(LinkedList* list);

#endif