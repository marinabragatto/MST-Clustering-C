#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Vector Vector; 

typedef void (*destroy_func)(void *); 
typedef void (*print_func)(void *); 
typedef int (*compare_func)(void*, void*); 



Vector * vector_create(int max_size, destroy_func destroy);
void vector_insert(Vector * vet, void * element);
void vector_destroy(void * vet);
void vector_print(Vector * vet, print_func print);
int vector_size(Vector * vet);
void * vector_get(Vector * vet, int idx);
void * vector_get_last(Vector * vet);
int vector_compare_smaller(void * vet1, void * vet2);
void * find_min(Vector * vet, compare_func compare);
// alguma implementação generica de vet, vetor , etc

#endif