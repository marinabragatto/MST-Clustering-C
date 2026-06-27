#include "page.h"
#include <math.h>

#define ALFA 0.85

#define MAX_SZ 100 // definir esse valor

struct Page{
    int n_out; // numero de outras paginas que essa aponta
    Vector * in_page; // paginas que aponta para mim
    String * name;
    double pagerank;
};

Page * page_create(String * name){
    Page * page = malloc(sizeof(Page));

    page->n_out = -1;
    page->in_page = vector_create(MAX_SZ, NULL);
    page->name = name;

    return page;
}
void page_insert_in_file(Page * page, Page * page_in){
    
    vector_insert(page->in_page, page_in);

}


String * page_get_name(Page * page){
    return page->name;
}

void page_destroy(void * page){

    if(page){
        Page * ptr = (Page *)page;
        if(ptr->name)
            string_destroy(ptr->name);

        if(ptr->in_page)
            vector_destroy(ptr->in_page);
        free(ptr);
    }



}   

void page_set_out_number(Page * page, int out_number){
    if(out_number != -1){
        // erro ja foi setado um vez
        return;
    }
    page->n_out = out_number;
}

void print_page(Page * page){
    printf("Page name:");
    string_print(page->name);
    printf("\nPage IN:");
    for(int i = 0; i < vector_size(page->in_page); i++){
        
        Page * p= vector_get(page->in_page, i);
        printf(" ");
        printf(" ");
        string_print(p->name);
        printf(",");
        
    }
    printf("\n");

}

void print_page_v2(Page * page){
    printf("Page name:");
    string_print(page->name);
}


// PAGERANK
void page_set_pagerank(Page* page, double pr){
    page->pagerank = pr;
}

double page_get_pagerank(Page* page){
    return page->pagerank;
}


// essa função poderia estar em outro lugar, talvez no tad system?
void page_rank_execute(StringMapVector* pages){
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
    double stop_cond;
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

Vector* page_get_in_page(Page* page){
    return page->in_page;
}

int page_get_out_number(Page* page){
    return page->n_out;
}