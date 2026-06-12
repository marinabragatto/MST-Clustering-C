#include "search.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30

struct Search{
    String * string; // talvez separar cada termo em uma string diferente
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

void search_print(Search * se){
    printf("(");
    string_print(se->string);
    printf(")");
}