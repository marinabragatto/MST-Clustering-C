#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Vector Vector; 

typedef void (*destroy_func)(void *); 
typedef void (*print_func)(void *); 


Vector * vector_create(int max_size);
void vector_insert(Vector * vet, void * element);
void vector_destroy(Vector * vet, destroy_func destroy);
void vector_print(Vector * vet, print_func print);
int vector_size(Vector * vet);
void * vector_get(Vector * vet, int idx);
// alguma implementação generica de vet, vetor , etc

#endif