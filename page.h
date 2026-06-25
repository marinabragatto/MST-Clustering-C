#ifndef PAGE_H
#define PAGE_H

#include "string.h"
#include "vector.h"

typedef struct Page Page;


Page * page_create(String * name);
void page_insert_in_file(Page * page, Page * page_in);
String * page_get_name(Page * page);
void page_set_out_number(Page * page, int out_number);
void print_page(Page * page);
void print_page_v2(Page * page);
void page_destroy(void * page);

int page_get_out_number(Page* page);

int page_compare(void* page1, void* page2); //compara por nome, retorna 0 se forem iguais

Vector* page_get_in_page(Page * page);

#endif