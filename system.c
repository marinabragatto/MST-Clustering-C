#include "system.h"

#include "list.h"
#include "search.h"
#include "simbolTable.h"
#include "system.h"
#include "string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct System{
    List * stop_words; // colocar aqui ou no indexador? // as stop words devem ser outra simbol table? para dado uma word, retornar se ela deve ser considerada ou nao? ou só uma lista mesmo?
    List * docs_name; // Conjunto de páginas na web 
    ST * term_list; // lista de dado um termo, em quais paginas ele está
    // Qual estrura vai guardar os links entre páginas?
    // Poderia ser uma ST para o IN de cada pagina 
    // E outra ST para o out de cada pagina ---> perguntar para o professor!
};



void print_char(void * s){
    char * s_ptr = (char*)s;
    printf("(%s)\n",s_ptr);
}

static List * read_stop_words(char * dir);
static List * read_docs_name(char * dir);
static ST * process_docs(List * docs_name, char * dir);

static char * define_directory_path(char * dir, char * sub_dir);

System * system_init(char * dir){
    // inicia as stop_words
    System * sys = (System*) malloc(sizeof(System));
    sys->stop_words = read_stop_words(dir);
    sys->docs_name = read_docs_name(dir);
    printf("stop words\n");
    list_print(sys->stop_words, print_char);
    printf("docs name\n");
    list_print(sys->docs_name, string_print);

    sys->term_list = process_docs(sys->docs_name, dir);
    return sys;
}


void system_execute(System * sys){
    Search * se; 
    while(se = search_read()){
        search_print(se);
    }
}
void system_destroy(System * sys){
    if(sys){
        if(sys->docs_name)
            list_destroy(sys->docs_name, string_destroy);

        if(sys->stop_words)
            list_destroy(sys->stop_words, free);

        free(sys);
    }
}

static List * read_stop_words(char * dir){
    List * stop_words = list_create(100); // definir um valor para aqui
    
    char * sub_dir = strdup("/stopwords.txt");
    char * dir_name =  define_directory_path(dir, sub_dir);
    free(sub_dir);
    
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }

    char string[100]; // definir um valor  para aqui
    int i = 0;

    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");

        char * str_ptr = strdup(string);
        // acho que tem que colocar no tipo string aqui
        list_insert(stop_words, str_ptr); // esse TAD list ainda está sem implementar
        i++;
    }


    free(dir_name);
    fclose(fp);

    return stop_words;
}
static List * read_docs_name(char * dir){
    List * docs_name = list_create(100); // definir um valor para aqui

    char * sub_dir = strdup("/index.txt");
    char * dir_name =  define_directory_path(dir, sub_dir);
    free(sub_dir);
    
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }


    char string[100]; // definir um valor  para aqui
    int i = 0;
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        // printf("(%s)\n", string);
        String * str_ptr = string_create(string);

        list_insert(docs_name,str_ptr); // esse TAD list ainda está sem implementar
        i++;
    }

    
    free(dir_name);
    fclose(fp);
    
    return docs_name;
}

static char * define_directory_path(char * dir, char * sub_dir){
    
    // printf("(%s)", dir);
    int len = strlen(dir) + strlen(sub_dir) + 1;
    char * ptr_dir = malloc(sizeof(char) * len);
    strcpy(ptr_dir, dir);
    strcat(ptr_dir, sub_dir);

    return ptr_dir;
}

static ST * process_docs(List * docs_name, char * dir){

    // !!!!!!!!!!!! Essa função já tá lendo os termos de todos os arquivos, falta agora
    // fazer com que ela coloque eles na ST seguindo as condições
    String * name;
    printf("\n\n\n\nPROCESS DOCS!!!!!!!!!!!!!\n\n\n\n");
    
    for(int i = 0; i < list_size(docs_name); i++){
        // termo -> lista com documentos que contém ele
        // termo -> lista de documentos que contém ele
        name = list_get(docs_name, i);
        string_print(name);
        
        char * sub_dir = strdup("/pages/");
        char * dir_name =  define_directory_path(dir, sub_dir);
        free(sub_dir);
        char * file_path = define_directory_path(dir_name, string_get_character(name,0));
        free(dir_name);

        print_char(file_path);
        FILE * fp = fopen(file_path, "r");
        free(file_path);
        

        char string[100]; // definir um valor  para aqui
        while(fscanf(fp,"%[^\n\t ]", string) != EOF){
            fscanf(fp,"%*[\n\t ]");
            // printf("(%s)\n", string);
            String * term = string_create(string); 
            string_tolower(term);
            string_print(term);
            string_destroy(term);

            // if(){ // if lista do termo x não existe ainda, crie
            //      // se nao pegue a lista que ja existe
            //      // a stop word tambem precisa nao estar aqui

            // }

            // coloquei por enquanto para criar sempre, só para testar
            // o outro seria um get na ST 
            List * list_term_docs = list_create(100); // lista de docs que contem o termo
            list_insert(list_term_docs, name); // esse TAD list ainda está sem implementar
              //inserir a lista na ST!

            // como nao estamos inserindo ainda, vou liberar memoria aqui
            list_destroy(list_term_docs, NULL);
        }

      
        fclose(fp);

    }


    return NULL;
}