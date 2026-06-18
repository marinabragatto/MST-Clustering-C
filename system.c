#include "system.h"

#include "vector.h"
#include "search.h"
#include "simbolTable.h"
#include "system.h"
#include "graph.h"
#include "string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING_SZ 200  // definir um valor para aqui
#define VECTOR_SZ 200  // definir um valor para aqui

struct System{
    Vector * stop_words; // colocar aqui ou no indexador? // as stop words devem ser outra simbol table? para dado uma word, retornar se ela deve ser considerada ou nao? ou só uma lista mesmo?
    ST * term_list; // lista de dado um termo, em quais paginas ele está
    // Qual estrura vai guardar os links entre páginas?
    // Poderia ser uma ST para o IN de cada pagina 
    // E outra ST para o out de cada pagina ---> perguntar para o professor!
    Graph * page_links; // mapeia um string em outras strings!
};



void print_char(void * s){
    char * s_ptr = (char*)s;
    printf("(%s)\n",s_ptr);
}

// Colocar todos esses reads em um TAD ioread.c/.h depois para organizar leituras da entrada padrao
static Vector * read_stop_words(char * dir);
static ST * read_terms(char * dir);
static void read_page(String * page_name, char * dir, ST * term_list);
static Graph * read_page_links(char * dir);

static char * define_directory_path(char * dir, const char * sub_dir);

System * system_init(char * dir){
    System * sys = (System*) malloc(sizeof(System));

    sys->stop_words = read_stop_words(dir);
    /*debug*/
    printf("stop words\n");
    vector_print(sys->stop_words, string_print);
    printf("stop words END\n");
    /*debug*/
    
    sys->term_list = read_terms(dir); /*debug esta dentro das funcoes*/

    sys->page_links  = read_page_links(dir); 

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
        if(sys->page_links)
            graph_destroy(sys->page_links);

        if(sys->term_list)
            ST_destroy(sys->term_list);

        if(sys->stop_words)
            vector_destroy(sys->stop_words, string_destroy);

        free(sys);
    }
}

static Vector * read_stop_words(char * dir){
    // nossa stopword vai ser uma Simbol Table (hash)
    Vector * stop_words = vector_create(VECTOR_SZ);
    
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
static ST * read_terms(char * dir){
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
        read_page(page_name, dir, term_list);
        string_destroy(page_name);
        i++;
    }

    fclose(fp);
    
    return term_list;
}

static char * define_directory_path(char * dir, const char * sub_dir){
    
    // printf("(%s)", dir);
    int len = strlen(dir) + strlen(sub_dir) + 1;
    char * ptr_dir = malloc(sizeof(char) * len);
    strcpy(ptr_dir, dir);
    strcat(ptr_dir, sub_dir);

    return ptr_dir;
}

static void read_page(String * page_name, char * dir, ST * term_list){

    // !!!!!!!!!!!! Essa função já tá lendo os termos de todos os arquivos, falta agora
    // fazer com que ela coloque eles na ST seguindo as condições
    
    // termo -> Vector com documentos que contém ele
    // termo -> Vector de documentos que contém ele
    
    char * tmp =  define_directory_path(dir, "/pages/");
    char * file_path = define_directory_path(tmp, string_get_character(page_name,0));
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
        string_destroy(term); // nao vai
        Vector * vet_term_docs = NULL;
        // ***** tem que verificar se o documento ja nao esta na lista de documentos *****
        // ***** tem que verificar se o termo é uma stop word *****
        if(vet_term_docs = ST_get(term_list, term)){
            // se o termo já tem um vetor associado a ele
            // pega esse vetor e insere mais um documento na lista de documentos
            // mas pode ser que o documento já esteja associado a esse termo, COMO TRATAR ISSO?
            if(vet_term_docs) // ****  deixar so enquanto a ST nao funciona **** 
                vector_insert(vet_term_docs, page_name); // insere o documento cmo associado ao termo

        }
        else {
            // cria um vetor de documentos novo
            vet_term_docs = vector_create(VECTOR_SZ);
            vector_insert(vet_term_docs, page_name); // insere o documento cmo associado ao termo
            
            ST_PUT(term_list, term, vet_term_docs);
        }
       
        vector_destroy(vet_term_docs, NULL);
    }
    
    fclose(fp);

}

static Graph * read_page_links(char * dir){
    printf("\n\n\nPAGE LINKS:\n\n\n");

    Graph * page_links = graph_create();

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

        Vector * adj_list =  vector_create(n);
        for(int i = 0 ; i < n; i++){
            fscanf(fp,"%[^ \n\t]", string);
            // printf("\tadj list : (%s)\n", string);
            fscanf(fp,"%*[ \n\t]");

            String * adj_vertex = string_create(string); // nome do arquivo adjacentes ao vertex 
            vector_insert(adj_list, adj_vertex); // precisaria armanezar o tamanho de cada lista
        }

        fscanf(fp,"%*[ \n\t]");

        vector_destroy(adj_list, string_destroy);
        string_destroy(vertex);

    
    }
    
    fclose(fp);

    return NULL;
}