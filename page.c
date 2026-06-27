#include "page.h"
#include <math.h>

#define MAX_SZ 100 // definir esse valor
#define ALFA 0.85

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
static StringMapVector* rec_pagerank(StringMapVector* pages, double* pr_prev, 
                                     double* pr_new, int size){
    // sempre vai executar pelo menos uma vez, por isso a verificação do 
    // criterio de parada não está no início da função, e sim antes da chamada recursiva

    double stop_cond = 0.0;

    // Laço de atualização. Na iteração k ≥ 1, o valor do PageRank é computado com base nos valores da iteração anterior:
    for(int i = 0; i < size; i++){
        Page* pi = SMV_get_by_idx(pages, i);
        Vector* in = page_get_in_page(pi); // In(k)(formula): conjunto de todas as páginas que têm um link para a página k
        int sz = vector_size(in); // n(formula): número total de páginas/documentos;
        
        double sum = 0.0; // acumulador de pr(j) / out_j para todas as j-esimas paginas

        for(int j = 0; j < sz; j++){
            Page * pj = vector_get(in, j); // j-esima pagina em In(i)
            int idx_j = -1; // indice no vetor original de paginas
            
            // varrer vetor original de paginas para buscar a posição correta da pagina j
            for(int k = 0; k < size; k++){
                if(SMV_get_by_idx(pages, k) == pj){
                    idx_j = k;
                    break;
                }
            }

            int out_j = page_get_out_number(pj); // Out(k)(formula): tamanho conjunto de todas as páginas com um link saindo da página k;
            sum += pr_prev[idx_j] / out_j; // out_j > 0 sempre, nao precisa de verificao para a divisao
        }


        // verificação da qtd de paginas que saem da pagina i
        if(page_get_out_number(pi) != 0){
            pr_new[i] = ((1.0 - ALFA) / size) + (ALFA * sum);
        }
        else{ // n_out(i) eh zero
            pr_new[i] = ((1.0 - ALFA) / size) + (ALFA * pr_prev[i]) + (ALFA * sum);
        }

        // acumula o "erro" dessa pagina i (pagina de referencia)
        stop_cond += fabs(pr_new[i] - pr_prev[i]);
    }

    stop_cond = stop_cond / size;

    // verificação do criterio de parada
    if(stop_cond < 1e-6){ // 10^-6 == 1e-6
        // salvar os pageranks finais nas paginas
        for(int i = 0; i < size; i++){
            Page* page = SMV_get_by_idx(pages, i);
            page_set_pagerank(page, pr_new[i]); // pr_new contém os valores finais
        }
        return pages; 
    }

    // troca os ponteiros pr_new e pr_old na chamada da recursão
    // pr_new contem os valores a serem usados na proxima iteração
    // pr_prev sera sobrescrito com os valores novos atualizados
    return rec_pagerank(pages, pr_new, pr_prev, size);
}

void page_rank_execute(StringMapVector* pages){
    int size = SMV_get_size(pages); // n (formula)
    
    double* pr_prev = malloc(size * sizeof(double));
    double* pr_new = malloc(size * sizeof(double));

    //Inicialização. No passo zero, o PageRank de cada página é inicializado de maneira uniforme: 1/n
    double pr_initial = 1.0 / size; // evitar ficar repetindo a divisao no loop
    for(int i = 0; i < size; i++) {
        pr_prev[i] = pr_initial;
    }

    // recursão
    //double stop_cond = 1.0;
    pages = rec_pagerank(pages, pr_prev, pr_new, size);

    free(pr_prev);
    free(pr_new);
}

Vector* page_get_in_page(Page* page){
    return page->in_page;
}

int page_get_out_number(Page* page){
    return page->n_out;
}