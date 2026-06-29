#ifndef PAGE_H
#define PAGE_H

#include "simbolTable.h"
#include "string.h"
#include "vector.h"
#include "stringMapVector.h"

typedef struct Page Page;


Page * page_create(String * name);
void page_insert_in_file(Page * page, Page * page_in);
String * page_get_name(Page * page);
void page_set_out_number(Page * page, int out_number);
void print_page(Page * page);
int page_has_words(Page * page, Vector * words, ST* stop_words); // words: palabras da busca
void page_insert_word(Page * page, String * word, char * exist);
void print_page_v2(Page * page);
void page_destroy(void * page);

// PAGERANK
void page_set_pagerank(Page* page, double pr);
double page_get_pagerank(Page* page);
void page_rank_execute(StringMapVector* pages);
Vector* page_get_in_page(Page* page);
int page_get_out_number(Page* page);


// PAGERANK POR PAGINA
void page_calculate_pagerank(Vector* pages);

int page_compare(const void* page1, const void* page2);

double page_get_pagerank(Page* page);

#endif