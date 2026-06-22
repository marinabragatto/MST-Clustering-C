#include "page.h"

#define MAX_SZ 100 // definir esse valor

struct Page{
    int n_out; // numero de outras paginas que essa aponta
    Vector * in_page; // paginas que aponta para mim
    String * name;
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