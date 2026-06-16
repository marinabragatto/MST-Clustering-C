#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct List List;

typedef void (*destroy_func)(void *); 
typedef void (*print_func)(void *); 


List * list_create(int max_size);
void list_insert(List * list, void * element);
void list_destroy(List * list, destroy_func destroy);
void list_print(List * list, print_func print);
// alguma implementação generica de lista, vetor , etc

#endif