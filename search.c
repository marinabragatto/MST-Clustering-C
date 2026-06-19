#include "search.h"

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#define MAX_SIZE 30

struct Search{
    String * string; // talvez separar cada termo em uma string diferente
    // acho que é melhor dividir em termos diferentes mesmo, ai podemos conferir se cada termo separadamente é uma stopword
    Vector * terms; // vetor de termos
};

void search_process(Search * se);
void search_print(Search * se);

Search * search_read(){
    char string[MAX_SIZE];
    // o caractere de fim de arquivo seja lido.
    // precisa ler ate o fim de um arquivo na verdade
    if(scanf("%[^\n\t]", string) != 1){
        return NULL;
    }
    scanf("%*[\n\t]");

    Search * se = (Search*)malloc(sizeof(Search)); 

    se->string = string_create(string);
    
    return se;
}

void search_process(Search * se){

}

String * search_get_word(Search * se){
    return se->string;
}

void search_print(Search * se){
    printf("(");
    string_print(se->string);
    printf(")");
}