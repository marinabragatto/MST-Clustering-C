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




void print_pages(System * sys){
    for(int i = 0; i < SMV_get_size(sys->pages) ; i++){
        // ST_get(sys->page_idx_vector, )
        print_page(SMV_get_by_idx(sys->pages, i));

    }
}





System * system_init(char * dir){
    System * sys = (System*) malloc(sizeof(System));

    sys->stop_words = read_stop_words(dir);
    // sys->stop_words =NULL;
    
    /*debug*/
    printf("stop words\n");
    // vector_print(sys->stop_words, string_print);
    printf("stop words END\n");
    /*debug*/ 

    sys->pages = read_pages_name(dir);
    print_pages(sys) ; // teste debug
    sys->term_list = read_terms(dir, sys->pages, sys->stop_words); /*debug esta dentro das funcoes*/

    // sys->page_links = NULL;

    read_pages_graph(dir, sys->pages); /*debug esta dentro das funcoes*/
    print_pages(sys) ; // teste debug

    return sys;
}



void system_execute(System * sys){
    Search * se; 
    int i = 0;
    while(se = search_read()){
        printf("search %d\n", i);
        Vector * words = search_get_words(se);

        for(int j = 0; j < vector_size(words); j++){
            printf("\t");
            string_print(vector_get(words, j));
            // Vector * pages = ST_get(sys->term_list);
            // if(pages){
            //     for(int i = 0; i <  vector_size(pages); i++){
            //         print_page_v2(vector_get(pages,i));
            //     }
            // }
        }

        // fflush(stdout);
        search_destroy(se);
        // printf("search %d\n\n", i);
        i++;
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
            SMV_destroy(sys->pages);

        if(sys->term_list)
            ST_destroy(sys->term_list, vector_destroy);

        if(sys->stop_words)
            ST_destroy(sys->stop_words, string_destroy);

        free(sys);
    }
}





