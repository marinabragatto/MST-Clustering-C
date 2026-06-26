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



Search * search_read(){
    // o caractere de fim de arquivo seja lido.
    // precisa ler ate o fim de um arquivo na verdade
    Search * se = (Search*)malloc(sizeof(Search)); 
    se->words = vector_create(VECTOR_SZ, string_destroy);
    
    char string[MAX_SIZE];
    char c;
    while(scanf("%29s",string) == 1){

        vector_insert(se->words, string_create(string));
        // printf("coisa estranha: (%s)\n", string);
        
        if(scanf("%c", &c) != 1)
            break;
        
        if(c == '\n' || c == '\r')
            break;
    }
    // scanf("%*[ \n\t]");


    if(vector_size(se->words) == 0){
        search_destroy(se);
        return NULL;
    }
    // scanf("%*[ ]");
    

    return se;
}

void search_process(Search * se){

}

Vector * search_get_words(Search * se){
    return se->words;
}

void search_print(Search * se){
    printf("(\n");
    for(int i = 0; i < vector_size(se->words); i++){
        printf("\t");
        string_print(vector_get(se->words, i));
    }
    printf(")");
}

void search_destroy(Search * se){
    if(se){
        if(se->words)
            vector_destroy(se->words);
            // se.
        free(se);
    }
}