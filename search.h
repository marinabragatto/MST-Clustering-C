#ifndef SEARCH_H
#define SEARCH_H

#include "string.h"
#include "vector.h"
#include <stdlib.h>

typedef struct Search Search;
Search * search_create();
void search_insert_word(Search * se, String * word);
void search_process(Search * se);
void search_print(Search * se);
void search_destroy(Search * se);
int search_num_words(Search * se);
Vector * search_get_words(Search * se);

#endif