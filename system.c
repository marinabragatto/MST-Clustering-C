#include "system.h"

#include "vector.h"
#include "search.h"
#include "simbolTable.h"
#include "system.h"
#include "string.h"
#include "page.h"
#include "stringMapVector.h"
#include "ioReader.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct System{
    ST * stop_words; // COLOCAR TIPO HASH!
    ST * term_list; // termo -> lista de Pages que ele aparece
    StringMapVector * pages;
};

static Vector *  system_process_search(System * sys, Vector * words);
static Vector * system_find_smaller_vector(System * sys, Vector * words);

void print_pages(System * sys){
    for(int i = 0; i < SMV_get_size(sys->pages) ; i++){
        // ST_get(sys->page_idx_vector, )
        print_page(SMV_get_by_idx(sys->pages, i));

    }
}





System * system_init(char * dir){
    System * sys = (System*) malloc(sizeof(System));

    sys->stop_words = read_stop_words(dir);
    
    sys->pages = read_pages_name(dir);
    //print_pages(sys) ; // debug
    sys->term_list = read_terms(dir, sys->pages, sys->stop_words); /*debug esta dentro das funcoes*/

    read_pages_graph(dir, sys->pages); /*debug esta dentro das funcoes*/
    //print_pages(sys) ; // debug

    return sys;
}

static Vector * system_find_smaller_vector(System * sys, Vector * words){
    // verificar se nao tem caso que quebra
    int idx_min = -1;
    Vector * min = NULL;
    
   for(int j = 0; j < vector_size(words); j++){
        String * w = vector_get(words, j); // palavra individual
        Vector * pages = ST_get(sys->term_list, w); // vetor de paginas associadas
        
        if(pages){ // se o termo nao eh uma stop word ou se o termo existe no nosso conjunto de paginas  
            if(min){ // se o min ja foi inicializado
                if(vector_compare_smaller(min, pages) == 1){ // min maior que pages
                    min = pages;
                    idx_min = j;
                }
            }
            else{ // se ele for nulo tem que iniciar a primeira vez
                // depois vai cair sempre no if acima
                min = pages;
                idx_min = j;
            
            }
        }
    }


    return min;
    
}

static Vector * system_process_search(System * sys, Vector * words){
    // if(search_get_word(se)  != nao eh uma stop word)  //

    // cada palavra tem um vetor associado
    // ai teria que iterar sobre esses vetores e achar o minimo
    Vector * smaller_vet =  system_find_smaller_vector(sys, words); // tratar se retornar null
    // poderia por acaso ter um com tamanho 0? acho que sim

    // iterar sobre os documentos do smaller vet e verificar
    // saida vetor de documentos resposta do problema!
    Vector * output = vector_create(VECTOR_SZ, NULL);
    
    if(smaller_vet){
        // printf("smaller vet size : %d\n", vector_size(smaller_vet));
        for(int i = 0; i < vector_size(smaller_vet); i ++){
            // printf("entrei looping\n");
            // para cada documento, verificar se tem todos os termos da busca
            Page * page = vector_get(smaller_vet, i);
            if(page_has_words(page, words, sys->stop_words)){
                vector_insert(output, page);
            }
            else{
                // printf("page do not have the term\n");
            }
        }
    }

    return output;
}

void system_execute(System * sys){
    Search * se; 
    //int i = 0;
    page_rank_execute(sys->pages);
    while(se = search_read(sys->stop_words)){
        //printf("search %d\n", i);
        Vector * words = search_get_words(se); // palavras da busca
        Vector * docs_answer = system_process_search(sys, words);

        //page_calculate_pagerank(docs_answer);

        vector_sort(docs_answer, page_compare);

        //for(int i = 0; i <  vector_size(docs_answer); i++){
        //    printf("ANSWER: ");
        //    printf("\t");
        //    print_page_v2(vector_get(docs_answer, i));
        //}   
        //if(vector_size(docs_answer) == 0){
        //    printf("no anwser!\n");
        //}
        //printf("\n");
        printf("search:");
        vector_print(words, string_print_v2);
        printf("\n");
        printf("pages:");
        for(int i = 0; i <  vector_size(docs_answer); i++){
            print_page_v2(vector_get(docs_answer, i));
        }
        printf("\n");
        printf("pr:");
        for(int i = 0; i <  vector_size(docs_answer); i++){
            printf("%.8lf ", page_get_pagerank(vector_get(docs_answer, i)));
        }
        printf("\n");


        search_destroy(se);
        vector_destroy(docs_answer);
        //i++;
    }

    /// depois teria que ordenar aqui com base no page rank de alguma forma
    // vai ter uma funcao que dado uma pagina computa o page rank dela, talvez vale a pena computar uma vez só e armazenar para nao ficar fazendo de novo toda vez.
}


void system_destroy(System * sys){
    if(sys){
        if(sys->pages)
            SMV_destroy(sys->pages);

        if(sys->term_list)
            ST_destroy(sys->term_list, vector_destroy);

        if(sys->stop_words)
            ST_destroy(sys->stop_words, string_destroy);

        free(sys);
    }
}





