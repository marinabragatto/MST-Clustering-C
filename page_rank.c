#include "page_rank.h"
#include <string.h>
#include <math.h>

#define ALFA 0.85

struct PageRank{
    double * value;
    int size;
};

static PageRank * page_rank_init(int size){
    // Inicializac¸˜ ao.Nopassozero,oPageRankdecadap´ agina´ einicializadodemaneirauniforme: (tirei do pdf)
    PageRank* pr = malloc(sizeof(PageRank));
    pr->value = malloc(size* sizeof(double));
    pr->size = size;

    for(int i = 0; i < pr->size; i++){
        pr->value[i] = 1.0 / pr->size;
    }

    return pr;
}

double page_rank(PageRank* pr, int idx){
    /// retorna o valor do page ranlk
    return pr->value[idx];
}

PageRank* page_rank_execute(Vector * pages){
    int size = vector_size(pages);
    PageRank* pr = page_rank_init(size); // inicializacao
//  Lac¸odeatualizac¸˜ ao.Naiterac¸˜ aok≥1,ovalordoPageRank´ ecomputadocombasenosvaloresdaiterac¸˜ ao
// anterior:

// esse deve ser o laco de atualizacao 
    
    double fixed_value = (1.0 - ALFA)/ size;
    double sum;
    double stop_criterion = 1;
    while(1){ // definir a formula de parada
        double* previous = memcpy(previous, pr->value, pr->size); // copia da iteração anterior
        for(int i = 0; i < size; i++){
            sum = 0; // melhor deixar a declaracao fora do loop?
            stop_criterion = 0;

            Page* pi = vector_get(pages, i);

            // parte comum aos dois casos
            for(int j = 0; j < size; j++){
                if(j == i) continue;
                Page* pj = vector_get(pages, j);
                if(vector_contains(page_get_in_page(pi), pj, &page_compare)){
                    sum += previous[j] / fabs(page_get_out_number(pj));
                }
            }

            if(page_get_out_number(pi) != 0){
                pr->value[i] = fixed_value + ALFA * sum;
            }
            else{ // n_out(i) eh zero
                pr->value[i] = fixed_value + ALFA * previous[i] + ALFA * sum;
            }
            stop_criterion += fabs(pr->value[i] - previous[i]);
        }

        stop_criterion = 1.0 / size *stop_criterion;
        if(stop_criterion < pow(10, -6)) // executa a operacao pow varias vezes
            break;
    }

    return pr;
}