#include "list.h"

#define TAM_MAX 10
#define BLOCK 200

struct List{
    void ** data;
    int size;
    int max;
};



List * list_create(int max_size){
    List * list = (List *)malloc(sizeof(List));

    list->data = (void**)calloc(max_size, sizeof(void*));
    list->size = 0;
    list->max = max_size;

    return list;
}
void list_insert(List * list, void * element){
    if(list->size >= list->max){
        list->data = realloc(list->data, sizeof(void*)*(list->max + BLOCK));
        list->max = list->max + BLOCK;
    }

    list->data[list->size] = element;
    list->size++;


}

void list_destroy(List * list, destroy_func destroy){
    if(list){
        if(list->data){
            
            for(int i = 0; i < list->size; i++)
                destroy(list->data[i]);

            free(list->data);
        }

        free(list);
    }
}


void list_print(List * list, print_func print){
   for(int i = 0; i < list->size; i++)
        print(list->data[i]);
}