#include "system.h"

#include "list.h"
#include "search.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct System{
    List * stop_words; // colocar aqui ou no indexador? // as stop words devem ser outra simbol table? para dado uma word, retornar se ela deve ser considerada ou nao? ou só uma lista mesmo?
    List * docs_name;
};


static List * read_stop_words(char * dir);
static List * read_docs_name(char * dir);


System * system_init(char * dir){
    // inicia as stop_words
    System * sys = (System*)malloc(sizeof(System));
    sys->stop_words = read_stop_words(dir);
    sys->docs_name = read_docs_name(dir);


    return sys;
}


void system_execute(System * sys){
    Search * se; 
    while(se = search_read()){
        search_print(se);
    }
}
void system_destroy(System * sys){
    
}

static List * read_stop_words(char * dir){
    List * stop_words = list_create(100); // definir um valor para aqui
    
    printf("chegue aqui\n");
    printf("(%s)",dir);
    
    char * dir_name = strdup(dir);
    strcat(dir_name, "/stopwords.txt");
    printf("(%s)",dir_name);
    
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    char string[100]; // definir um valor  para aqui
    int i = 0;
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        printf("(%s)\n", string);
        list_insert(stop_words, i, string); // esse TAD list ainda está sem implementar
        i++;
    }

    return stop_words;
}
static List * read_docs_name(char * dir){
    List * docs_name = list_create(100); // definir um valor para aqui
    
    printf("chegue aqui\n");
    printf("(%s)",dir);

    char * dir_name = strdup(dir);
    strcat(dir_name, "/index.txt");
    printf("(%s)",dir_name);
    
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    char string[100]; // definir um valor  para aqui
    int i = 0;
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        printf("(%s)\n", string);
        list_insert(docs_name, i,string); // esse TAD list ainda está sem implementar
        i++;
    }

    return docs_name;
}

