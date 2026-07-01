/**
 * @file search.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "search.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#define MAX_SIZE 30

struct Search{
    // String * string; // talvez separar cada termo em uma string diferente
    // acho que é melhor dividir em termos diferentes mesmo, ai podemos conferir se cada termo separadamente é uma stopword
    Vector * words; // vetor de termos
};

void search_process(Search * se);
void search_print(Search * se);


Search * search_create(){
    Search * se = (Search*)malloc(sizeof(Search)); 
    se->words = vector_create(MAX_SIZE, string_destroy); // mudar o nome de max_size

    return se;
}

void search_insert_word(Search * se, String * word){
    vector_insert(se->words, word);
}


int search_num_words(Search * se){
    return vector_size(se->words);
}
void search_process(Search * se){

}

Vector * search_get_words(Search * se){
    return se->words;
}

void search_print(Search * se){
    printf("(\n");
    int size = vector_size(se->words);
    for(int i = 0; i < size; i++){
        printf("\t");
        string_print(vector_get(se->words, i));
    }
    printf(")\n");
}

void search_destroy(Search * se){
    if(se){
        if(se->words)
            vector_destroy(se->words);
        free(se);
    }
}