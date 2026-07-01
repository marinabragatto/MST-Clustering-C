#include "vector.h"

#define TAM_MAX 10
#define BLOCK 200

struct Vector{
    void ** data;
    int size;
    destroy_func destroy;
    int max;
};



Vector * vector_create(int max_size, destroy_func destroy){
    Vector * vet = (Vector *)malloc(sizeof(Vector));

    vet->data = (void**)calloc(max_size, sizeof(void*));
    vet->size = 0;
    vet->max = max_size;
    vet->destroy = destroy;

    return vet;
}
void vector_insert(Vector * vet, void * element){
    if(vet->size >= vet->max){
        vet->data = realloc(vet->data, sizeof(void*)*(vet->max*2));
        vet->max = vet->max*2;
    }

    vet->data[vet->size] = element;
    vet->size++;

}

void * find_min(Vector * vet, compare_func compare){

    int idx_min = 0;
    void * value = vector_get(vet, 0);
    for(int  i = 1; i < vet->size; i++){
        void * element = vector_get(vet, i);
        if(compare(value,element) > 0){
            idx_min=i;
            value = element;
        }
    }


    return value;
}
void vector_destroy(void * vet){
    Vector * vet_ptr = (Vector*)vet;
    
    if(vet_ptr){
        if(vet_ptr->data){
            
            for(int i = 0; i < vet_ptr->size; i++){
                if(vet_ptr->destroy)
                    vet_ptr->destroy(vet_ptr->data[i]);
            }

            free(vet_ptr->data);
        }

        free(vet_ptr);
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

void * vector_get_last(Vector * vet){
    if (vet->size > 0)
        return vet->data[vet->size - 1];
    return NULL;
}


int vector_compare_smaller(void * vet1, void * vet2){
    Vector * v1_ptr = (Vector*)vet1;
    Vector * v2_ptr = (Vector*)vet2;

    if(vector_size(v1_ptr) > vector_size(v2_ptr)){
        return 1;
    }
    if(vector_size(v1_ptr) < vector_size(v2_ptr)){
        return -1;
    }

    return 0;

}


void vector_sort(Vector* vet, compare_tosort_func compare){
    //printf("chamando qsort\n"); // debug
    qsort(vet->data, vet->size, sizeof(void*), compare);
    //printf("qsort finalizado\n"); // debug
}