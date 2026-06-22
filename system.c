#include "system.h"

#include "vector.h"
#include "search.h"
#include "simbolTable.h"
#include "system.h"
#include "string.h"
#include "page.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING_SZ 200  // definir um valor para aqui
#define VECTOR_SZ 200  // definir um valor para aqui

struct System{
    Vector * stop_words; // COLOCAR TIPO HASH!
    ST * term_list; // termo -> lista de docs que ele aparece
    // ST * page_links; // mapeia um string em outras strings! Dado uma pagina, para quem ela aponta
    
    ST * page_idx_vector;
    Vector * pages;
};



void print_char(void * s){
    char * s_ptr = (char*)s;
    printf("(%s)\n",s_ptr);
}

// Colocar todos esses reads em um TAD ioread.c/.h depois para organizar leituras da entrada padrao
static Vector * read_stop_words(char * dir);
// static Vector * read_pages(char * dir);
static ST * read_terms(char * dir,  Vector * pages, Vector * stop_words);
static void read_page(String * page_name, char * dir, Vector * stop_words, ST * term_list);
static void read_page_links(char * dir, Vector * pages, ST * page_idx_vector);

// statics de verdade
static char * define_directory_path(char * dir, const char * sub_dir);
static void read_pages(System * sys, char * dir);
void print_pages(System * sys);


System * system_init(char * dir){
    System * sys = (System*) malloc(sizeof(System));

    sys->stop_words = read_stop_words(dir);
    /*debug*/
    printf("stop words\n");
    vector_print(sys->stop_words, string_print);
    printf("stop words END\n");
    /*debug*/ 

    read_pages(sys, dir);
    print_pages(sys) ; // teste debug
        // ST * page_idx_vector;
    // Vector * pages;

    sys->term_list = read_terms(dir, sys->pages, sys->stop_words); /*debug esta dentro das funcoes*/

    // sys->page_links = NULL;

    read_page_links(dir, sys->pages, sys->page_idx_vector); /*debug esta dentro das funcoes*/
    print_pages(sys) ; // teste debug

    return sys;
}

void print_pages(System * sys){
    for(int i = 0; i < vector_size(sys->pages) ; i++){
        // ST_get(sys->page_idx_vector, )
        print_page(vector_get(sys->pages, i));

    }
}

static void read_pages(System * sys, char * dir){
    
    sys->pages = vector_create(VECTOR_SZ, page_destroy);
    sys->page_idx_vector = ST_init();

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

        Page * page = page_create(page_name);
        printf("PAGE NAME : ");
        string_print(page_name);

        vector_insert(sys->pages, page);
        
        int  * idx = (int*)malloc(sizeof(int));
        *idx = i;

        ST_PUT(sys->page_idx_vector, page_name, idx);
        
        i++;
    }

    fclose(fp);


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
        if(sys->pages)
            vector_destroy(sys->pages);

        if(sys->page_idx_vector)
            ST_destroy(sys->page_idx_vector, free);

        // if(sys->page_links)
        //     ST_destroy(sys->page_links, vector_destroy);

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
static ST * read_terms(char * dir,  Vector * pages, Vector * stop_words){
    ST * term_list = ST_init();

    int i = 0;

    for(int i = 0; i < vector_size(pages); i ++){
        Page * page = vector_get(pages, i);
        read_page(page_get_name(page), dir, stop_words, term_list);
    }

    
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
        // string_print(term);

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

static void read_page_links(char * dir, Vector * pages, ST * page_idx_vector){
    printf("\n\n\nPAGE LINKS:\n\n\n");

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

        int * idx_vet = ST_get(page_idx_vector, vertex);

        Page * page = vector_get(pages, *idx_vet); 
        page_set_out_number(page, n);


        for(int i = 0 ; i < n; i++){
            fscanf(fp,"%[^ \n\t]", string);
            // printf("\tadj list : (%s)\n", string);
            fscanf(fp,"%*[ \n\t]");
            
            String * adj_vertex = string_create(string); // nome do arquivo adjacentes ao vertex 
            Page * page_adj = vector_get(pages, *(int*)ST_get(page_idx_vector, adj_vertex)); 
            page_insert_in_file(page_adj,page);
            string_destroy(adj_vertex);

        }


        fscanf(fp,"%*[ \n\t]");

        string_destroy(vertex);
    }
    
    fclose(fp);

}