/**
 * @file page.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "page.h"
#include <string.h>

#define MAX_SZ 20 // definir esse valor


struct Page{
    int n_out; // numero de outras paginas que essa aponta
    Vector * in_page; // paginas que aponta para mim
    String * name;
    ST * words;
    double pagerank;
};

Page * page_create(String * name){
    Page * page = malloc(sizeof(Page));

    page->n_out = -1;
    page->in_page = vector_create(MAX_SZ, NULL);
    page->name = name;
    page->words = ST_init();

    return page;
}
void page_insert_word(Page * page, String * word, char * exist){
    int sucess = 0;
    //printf("inserindo: ");
    if((sucess = ST_PUT(page->words, word, exist)) == 0){
        //printf("erro "); 
        // testar inserir dyas palavras iguais
        //string_print(word);
        // string_destroy(word); removi
    }
    else{
        //printf("certo "); 
        // testar inserir dyas palavras iguais
        //string_print(word);
        
    }
    // se nao deu certo tem q liberar
}

void page_insert_in_file(Page * page, Page * page_in){
    
    vector_insert(page->in_page, page_in);

}


String * page_get_name(Page * page){
    return page->name;
}

int page_has_words(Page * page, Vector * words, ST* stop_words){
    /// a nossa tst da pagina, nao guarda se for uma stop word
    // talvez tem que verificar
    // printf("size das palavras da busca %d\n", vector_size(words));
    int size = vector_size(words);
    for(int i  = 0; i < size; i++){
        // tem que pensar se ali tem stopword
        String * word = vector_get(words, i);
        if(ST_get(stop_words, word) != NULL){ // se for stop word, ignora
            continue;
        }
        // string_print(word);
        void * has = ST_get(page->words, word);
        if(has ==  NULL){ // pagina nao tem todas as words da search
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
        // erro ja foi setado um vez
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
    //printf("Page name:");
    string_print_v2(page->name);
}


// PAGERANK
void page_set_pagerank(Page* page, double pr){
    page->pagerank = pr;
}

double page_get_pagerank(Page* page){
    return page->pagerank;
}


// essa função poderia estar em outro lugar, talvez no tad system?

/*void page_calculate_pagerank(Vector* pages){
    int size = vector_size(pages); // n (formula): número total de páginas/documentos;
    
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
            Page* pi = vector_get(pages, i);
            Vector* in = page_get_in_page(pi);
            int sz = vector_size(in);

            double sum = 0.0;
            for(int j = 0; j < sz; j++){
                Page* pj = vector_get(in, j);
                int idx_j = -1; // indice no vetor original de paginas
                for(int k = 0; k < size; k++){
                    if(vector_get(pages, k) == pj){
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
        Page* page = vector_get(pages, i);
        page_set_pagerank(page, pr_prev[i]);
    }

    free(pr_prev);
    free(pr_new);
}
*/

Vector* page_get_in_page(Page* page){
    return page->in_page;
}

int page_get_out_number(Page* page){
    return page->n_out;
}

int page_compare(const void* page1, const void* page2){
    Page* p1 = *(Page**)page1;
    Page* p2 = *(Page**)page2;

    // ordenacao decrescente, por isso nao segue a convenção de funcoes de comparacao
    if(p1->pagerank < p2->pagerank){
        return 1;
    }
    if(p1->pagerank > p2->pagerank){
        return -1;
    }

    return compare(p1->name, p2->name);
}

