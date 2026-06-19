#include "system.h"

#include "vector.h"
#include "search.h"
#include "simbolTable.h"
#include "system.h"
#include "string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING_SZ 200  // definir um valor para aqui
#define VECTOR_SZ 200  // definir um valor para aqui

struct System{
    Vector * stop_words; // COLOCAR TIPO HASH!
    ST * term_list; // termo -> lista de docs que ele aparece
    ST * page_links; // mapeia um string em outras strings! Dado uma pagina, para quem ela aponta
};



void print_char(void * s){
    char * s_ptr = (char*)s;
    printf("(%s)\n",s_ptr);
}

// Colocar todos esses reads em um TAD ioread.c/.h depois para organizar leituras da entrada padrao
static Vector * read_stop_words(char * dir);
static ST * read_terms(char * dir, Vector * stop_words);
static void read_page(String * page_name, char * dir, Vector * stop_words, ST * term_list);
static ST * read_page_links(char * dir);

// statics de verdade
static char * define_directory_path(char * dir, const char * sub_dir);

System * system_init(char * dir){
    System * sys = (System*) malloc(sizeof(System));

    sys->stop_words = read_stop_words(dir);
    /*debug*/
    printf("stop words\n");
    vector_print(sys->stop_words, string_print);
    printf("stop words END\n");
    /*debug*/

    sys->term_list = read_terms(dir, sys->stop_words); /*debug esta dentro das funcoes*/

    sys->page_links  = read_page_links(dir); /*debug esta dentro das funcoes*/

    return sys;
}


void system_execute(System * sys){
    Search * se; 
    while(se = search_read()){
        search_print(se);
        
        // if(search_get_word(se)  != nao eh uma stop word)  //

        // verificar aqui se para cada termo da search, ele ta no documento X 
        // sys->term_list 
        // usar essa var para conferir
        // fazer looping buscando
    }

    /// depois teria que ordenar aqui com base no page rank de alguma forma
    // vai ter uma funcao que dado uma pagina computa o page rank dela, talvez vale a pena computar uma vez só e armazenar para nao ficar fazendo de novo toda vez. 
}
void system_destroy(System * sys){
    if(sys){
        if(sys->page_links)
            ST_destroy(sys->page_links, vector_destroy);

        if(sys->term_list)
            ST_destroy(sys->term_list, vector_destroy);

        if(sys->stop_words)
            vector_destroy(sys->stop_words);

        free(sys);
    }
}

static Vector * read_stop_words(char * dir){
    // nossa stopword vai ser uma Simbol Table (hash)
    Vector * stop_words = vector_create(VECTOR_SZ, string_destroy);
    
    char * dir_name =  define_directory_path(dir, "/stopwords.txt");
    print_char(dir_name);
    FILE * fp = fopen(dir_name,"r"); 
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(dir_name);

    char string[STRING_SZ];
    int i = 0;

    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        String * str_ptr = string_create(string);
        vector_insert(stop_words, str_ptr);
        i++;
    }


    fclose(fp);

    return stop_words;
}
static ST * read_terms(char * dir,  Vector * stop_words){
    ST * term_list = ST_init();

    char * dir_name =  define_directory_path(dir, "/index.txt");
    
    FILE * fp = fopen(dir_name,"r");
    free(dir_name);

    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }

    char string[STRING_SZ];
    int i = 0;
    while(fscanf(fp,"%[^\n\t]", string) != EOF){
        fscanf(fp,"%*[\n\t]");
        String * page_name = string_create(string);
        printf("PAGE NAME : ");
        string_print(page_name);
        read_page(page_name, dir, stop_words, term_list);
        // string_destroy(page_name);
        i++;
    }

    fclose(fp);
    
    return term_list;
}

static char * define_directory_path(char * dir, const char * sub_dir){
    
    int len = strlen(dir) + strlen(sub_dir) + 1;
    char * ptr_dir = malloc(sizeof(char) * len);
    strcpy(ptr_dir, dir);
    strcat(ptr_dir, sub_dir);

    return ptr_dir;
}

static void read_page(String * page_name, char * dir, Vector * stop_words, ST * term_list){

    // !!!!!!!!!!!! Essa função já tá lendo os termos de todos os arquivos, falta agora
    // fazer com que ela coloque eles na ST seguindo as condições
    
    // termo -> Vector com documentos que contém ele
    // termo -> Vector de documentos que contém ele
    
    char * tmp =  define_directory_path(dir, "/pages/");
    char * file_path = define_directory_path(tmp, string_get_char_pointer(page_name,0));
    free(tmp);

    print_char(file_path);
    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
    

    char string[STRING_SZ];
    while(fscanf(fp,"%[^\n\t ]", string) != EOF){
        fscanf(fp,"%*[\n\t ]");
        // printf("(%s)\n", string);
        String * term = string_create(string); 
        string_tolower(term);
        string_print(term);

        Vector * vet_term_docs = NULL;

        // ***** tem que verificar se o termo é uma stop word *****
        if(1){ // esse if é para verificar se é uma stop word
            if(vet_term_docs = ST_get(term_list, term)){
                String * last_page_name = vector_get_last(vet_term_docs);
                if(last_page_name != NULL){
                    if(compare(page_name,last_page_name) != 0){ // Nao eh igual
                        vector_insert(vet_term_docs, page_name); // insere o documento cmo associado ao termo
                    }
                }
            }
            else {
                // cria um vetor de documentos novo
                vet_term_docs = vector_create(VECTOR_SZ, NULL);
                vector_insert(vet_term_docs, page_name); // insere o documento cmo associado ao termo
                ST_PUT(term_list, term, vet_term_docs);
            }
        }
        string_destroy(term);
    }
    
    fclose(fp);

}

static ST * read_page_links(char * dir){
    printf("\n\n\nPAGE LINKS:\n\n\n");

    ST * page_links = ST_init();

    char * file_path =  define_directory_path(dir, "/graph.txt");

    FILE * fp = fopen(file_path, "r");
    if(fp == NULL){
        perror("Error, open file");
        exit(1);
    }
    free(file_path);
    
    char string[STRING_SZ]; 
    
    while(fscanf(fp,"%[^\n\t ]", string) != EOF){
        fscanf(fp,"%*[\n\t ]");
        String * vertex = string_create(string); // nome do arquivo (vertice)
        
        int n; // numero de elementos associados
        fscanf(fp,"%d", &n);
        fscanf(fp,"%*[ ]");
        // printf("int n : %d\n", n);

        Vector * adj_list =  vector_create(n, string_destroy);
        for(int i = 0 ; i < n; i++){
            fscanf(fp,"%[^ \n\t]", string);
            // printf("\tadj list : (%s)\n", string);
            fscanf(fp,"%*[ \n\t]");

            String * adj_vertex = string_create(string); // nome do arquivo adjacentes ao vertex 
            vector_insert(adj_list, adj_vertex); // precisaria armanezar o tamanho de cada lista
        }

        ST_PUT(page_links, vertex, adj_list);

        fscanf(fp,"%*[ \n\t]");

        // vector_destroy(adj_list);
        string_destroy(vertex);
    }
    
    fclose(fp);

    return page_links;
}