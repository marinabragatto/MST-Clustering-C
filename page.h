#ifndef PAGE_H
#define PAGE_H

#include "string.h"
#include "vector.h"
#include "stringMapVector.h"

typedef struct Page Page;


Page * page_create(String * name);
void page_insert_in_file(Page * page, Page * page_in);
String * page_get_name(Page * page);
void page_set_out_number(Page * page, int out_number);
void print_page(Page * page);
void print_page_v2(Page * page);
void page_destroy(void * page);


// PAGERANK
void page_set_pagerank(Page* page, double pr);
double page_get_pagerank(Page* page);
void page_rank_execute(StringMapVector* pages);
Vector* page_get_in_page(Page* page);
int page_get_out_number(Page* page);

#endif