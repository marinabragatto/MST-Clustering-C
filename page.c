#include "page.h"

#define MAX_SZ 100 // definir esse valor


struct Page{
    int n_out; // numero de outras paginas que essa aponta
    Vector * in_page; // paginas que aponta para mim
    String * name;
    ST * words;
};

Page * page_create(String * name){
    Page * page = malloc(sizeof(Page));

    page->n_out = -1;
    page->in_page = vector_create(MAX_SZ, NULL);
    page->name = name;
    page->words = ST_init();

    return page;
}
void page_insert_word(Page * page, String * word){
    int sucess = 0;
    printf("inserindo: ");
    if((sucess = ST_PUT(page->words, word, word)) == 0){
        printf("erro\n"); // testar inserir dyas palavras iguais
        string_destroy(word);
    }
    else{
        printf("certo "); // testar inserir dyas palavras iguais
        string_print(word);
        
    }
    // se nao deu certo tem q liberar
}

void page_insert_in_file(Page * page, Page * page_in){
    
    vector_insert(page->in_page, page_in);

}


String * page_get_name(Page * page){
    return page->name;
}

int page_has_words(Page * page, Vector * words){
    /// a nossa tst da pagina, nao guarda se for uma stop word
    // talvez tem que verificar
    // printf("size das palavras da busca %d\n", vector_size(words));
    for(int i  = 0; i < vector_size(words); i++){
        // tem que pensar se ali tem stopword
        String * word = vector_get(words, i);
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
            ST_destroy(ptr->words, string_destroy);
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
    printf("IN:");
    for(int i = 0; i < vector_size(page->in_page); i++){
        
        Page * p= vector_get(page->in_page, i);
        printf(" ");
        string_print_v2(p->name);
        printf(",");
        
    }
    printf("\n\n");

}

void print_page_v2(Page * page){
    printf("Page name:");
    string_print(page->name);
}