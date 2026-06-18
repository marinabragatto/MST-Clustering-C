#include "vector.h"

#define TAM_MAX 10
#define BLOCK 200

struct Vector{
    void ** data;
    int size;
    int max;
};



Vector * vector_create(int max_size){
    Vector * vet = (Vector *)malloc(sizeof(Vector));

    vet->data = (void**)calloc(max_size, sizeof(void*));
    vet->size = 0;
    vet->max = max_size;

    return vet;
}
void vector_insert(Vector * vet, void * element){
    if(vet->size >= vet->max){
        vet->data = realloc(vet->data, sizeof(void*)*(vet->max + BLOCK));
        vet->max = vet->max + BLOCK;
    }

    vet->data[vet->size] = element;
    vet->size++;


}

void vector_destroy(Vector * vet, destroy_func destroy){
    if(vet){
        if(vet->data){
            
            for(int i = 0; i < vet->size; i++){
                if(destroy)
                    destroy(vet->data[i]);
            }

            free(vet->data);
        }

        free(vet);
    }
}


void vector_print(Vector * vet, print_func print){
   for(int i = 0; i < vet->size; i++)
        print(vet->data[i]);
}

void * vector_get(Vector * vet, int idx){
    if(idx < vet->size)
        return vet->data[idx];

    return NULL;
}

int vector_size(Vector * vet){
    return vet->size;
}