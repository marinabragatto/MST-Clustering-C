#ifndef LIST_H
#define LIST_H

typedef struct List List;

List * list_create(int max_size);
List * list_insert(List * list, int idx, void * element);
// alguma implementação generica de lista, vetor , etc

#endif