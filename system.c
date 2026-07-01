/**
 * @file system.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Implementação do TAD System
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
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
#include <math.h>


struct System{
    ST * stop_words; /*Termos ignorados na busca*/
    ST * term_list; /*Termo -> lista de Pages que ele aparece*/
    StringMapVector * pages; 
    char * exist; /*Marcador de Existência*/
};
#define ALFA 0.85
static void page_rank_execute(StringMapVector * pages);
static Vector *  system_process_search(System * sys, Vector * words);
static Vector * system_find_smaller_vector(System * sys, Vector * words);
void print_page_results(Vector * docs_answer);

void print_page_results(Vector * docs_answer){
    printf("pages:");
    if(docs_answer){
        vector_sort(docs_answer, page_compare);
        int size = vector_size(docs_answer);
        for(int i = 0; i < size; i++){
            if(i > 0){
                printf(" ");
            }
            print_page_v2(vector_get(docs_answer, i));
        }
    }
    printf("\n");
    printf("pr:");
    if(docs_answer){
        int size = vector_size(docs_answer);
        for(int i = 0; i < size; i++){
            if(i > 0){
                printf(" ");
            }
            printf("%.17lf", page_get_pagerank(vector_get(docs_answer, i)));
        }        
    }
    printf("\n");
}


System * system_init(char * dir){
    System * sys = (System*) malloc(sizeof(System));

    if(!sys){
        perror("Erro ao realizar malloc");
        exit(1);
    }

    sys->exist = string_create("1"); /* String que verifica a existencia de um elemento em uma SimbolTable*/
    sys->stop_words = read_stop_words(dir, sys->exist);
    sys->pages = read_pages_name(dir);
    sys->term_list = read_terms(dir, sys->pages, sys->stop_words, sys->exist);
    read_pages_graph(dir, sys->pages); 

    return sys;
}

static Vector * system_find_smaller_vector(System * sys, Vector * words){
    // verificar se nao tem caso que quebra
    int idx_min = -1;
    Vector * min = NULL;
    
    int size = vector_size(words);
    for(int j = 0; j < size; j++){
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

    Vector * smaller_vet =  system_find_smaller_vector(sys, words);
    // poderia por acaso ter um com tamanho 0? acho que sim

    // iterar sobre os documentos do smaller vet e verificar
    // saida vetor de documentos resposta do problema!
    Vector * output = NULL;
    if(smaller_vet){
        output = vector_create(vector_size(smaller_vet), NULL); 
        int size = vector_size(smaller_vet);
        // Para cada Página do menor vetor
        for(int i = 0; i < size; i ++){
            /* Para cada documento, verificar se tem todos os termos da busca */ 
            Page * page = vector_get(smaller_vet, i);
            // Verificar se ela tem todos os termos
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
    Search * se=NULL; 

    page_rank_execute(sys->pages);
    while(se = search_read_print(sys->stop_words)){
        Vector * words = search_get_words(se); // Palavras validas da busca
        Vector * docs_answer = system_process_search(sys, words);
        print_page_results(docs_answer);
        vector_destroy(docs_answer);
        search_destroy(se);
    }

}


static void page_rank_execute(StringMapVector * pages){
    int size = SMV_get_size(pages); // n (formula): número total de páginas/documentos;
    
    double* pr_prev = malloc(size * sizeof(double));
    double* pr_new = malloc(size * sizeof(double));

    //Inicialização. No passo zero, o PageRank de cada página é inicializado de maneira uniforme: 1/n
    double pr_initial = 1.0 / size; // evitar ficar repetindo a divisao no loop
    for(int i = 0; i < size; i++){
        pr_prev[i] = pr_initial;
    }

    // Laço de atualização. Na iteração k ≥ 1, o valor do PageRank é computado com base nos valores da iteração anterior:
    double fixed_value = (1.0 - ALFA) / size;
    double stop_cond = 0;
    
    do{
        stop_cond = 0;
        for(int i = 0; i < size; i++){
            Page* pi = SMV_get_by_idx(pages, i);
            Vector* in = page_get_in_page(pi);
            int sz = vector_size(in);

            double sum = 0.0;
            for(int j = 0; j < sz; j++){
                Page* pj = vector_get(in, j);
                int idx_j = -1; // indice no vetor original de paginas
                for(int k = 0; k < size; k++){
                    if(SMV_get_by_idx(pages, k) == pj){
                        idx_j = k;
                        break;
                    }
                }
                sum += pr_prev[idx_j] / page_get_out_number(pj);  // out_j > 0 sempre, nao precisa de verificao para a divisao
            }

            if(page_get_out_number(pi) != 0){
                pr_new[i] = fixed_value + ALFA * sum;
            }
            else{ // n_out(i) eh zero
                pr_new[i] = fixed_value + (ALFA * pr_prev[i]) + (ALFA * sum);
            }
            stop_cond += fabs(pr_new[i] - pr_prev[i]);
        }

        stop_cond = 1.0 / size *stop_cond;

        // armezenar valores para a proxima iteração
        // trocar os ponteiros funciona?
        double *temp = pr_prev;
        pr_prev = pr_new; // apos a ultima iteração, os valores corretos estarão no vetor pr_prev por causa da troca
        pr_new = temp;
        
    }while(stop_cond >= 1e-6); // 10^-6 == 1e-6

    // salvar os page ranks finais nas paginas
    for(int i = 0; i < size; i++) {
        Page* page = SMV_get_by_idx(pages, i);
        page_set_pagerank(page, pr_prev[i]);
    }

    free(pr_prev);
    free(pr_new);
}

void system_destroy(System * sys){
    if(sys){
        if(sys->pages)
            SMV_destroy(sys->pages);

        if(sys->term_list)
            ST_destroy(sys->term_list, vector_destroy);

        if(sys->stop_words)
            ST_destroy(sys->stop_words, NULL);
        if(sys->exist)
            free(sys->exist);

        free(sys);
    }
}





