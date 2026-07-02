/**
 * @file page.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Implementação do TAD Page
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "page.h"
#include <string.h>

#define PAGE_VECTOR_SZ 20 


struct Page{
    int n_out; /*Numero de Links de Saida*/
    Vector * in_page; /*Lista de Paginas que apontam para mim*/
    String * name;
    ST * words; /*Lista de termos dessa pagina*/
    double pagerank;
};

Page * page_create(String * name){
    Page * page = malloc(sizeof(Page));

    page->n_out = -1;
    page->in_page = vector_create(PAGE_VECTOR_SZ, NULL);
    page->name = name;
    page->words = ST_init();

    return page;
}
void page_insert_word(Page * page, String * word, char * exist){
    int sucess = 0;
    sucess = ST_PUT(page->words, word, exist); /* Esse retorno pode ser ignorado, nesse caso.*/ 
}

void page_insert_in_page(Page * page, Page * page_in){
    vector_insert(page->in_page, page_in);
}


String * page_get_name(Page * page){
    return page->name;
}

int page_has_words(Page * page, Vector * words, ST* stop_words){
    int size = vector_size(words);
    for(int i  = 0; i < size; i++){
        String * word = vector_get(words, i);
        // if(ST_get(stop_words, word) != NULL){ /* se for stop word, ignora, mas o vetor de entrada words, nunca terá stopwords */
        //     continue;
        // }
        void * has = ST_get(page->words, word);
        if(has ==  NULL){ /* Pagina nao tem todas as Words do vetor*/
            return 0;
        }
    }

    return 1;
}

void page_destroy(void * page){
    if(page){
        Page * ptr = (Page *)page;
        if(ptr->name)
            string_destroy(ptr->name);

        if(ptr->in_page)
            vector_destroy(ptr->in_page);
        if(ptr->words)
            ST_destroy(ptr->words, NULL);
        free(ptr);
    }
}   

void page_set_out_number(Page * page, int out_number){
    if(page->n_out != -1){
        /* Erro ja foi setado um vez */
        return;
    }
    page->n_out = out_number;
}

void print_page(Page * page){
    printf("Page name:");
    string_print(page->name);
    printf("IN:");
    int size = vector_size(page->in_page);
    for(int i = 0; i < size; i++){
        
        Page * p= vector_get(page->in_page, i);
        printf(" ");
        string_print_v2(p->name);
        printf(",");
        
    }
    printf("\n\n");

}

void print_page_v2(Page * page){
    string_print_v2(page->name);
}


/* FUNCOES RELACIONADAS AO PAGERANK */

void page_set_pagerank(Page* page, double pr){
    page->pagerank = pr;
}

double page_get_pagerank(Page* page){
    return page->pagerank;
}

Vector* page_get_in_page(Page* page){
    return page->in_page;
}

int page_get_out_number(Page* page){
    return page->n_out;
}

int page_compare(const void* page1, const void* page2){
    Page* p1 = *(Page**)page1;
    Page* p2 = *(Page**)page2;

    /* Ordenacao decrescente*/
    if(p1->pagerank < p2->pagerank){
        return 1;
    }
    if(p1->pagerank > p2->pagerank){
        return -1;
    }

    return compare(p1->name, p2->name);
}

