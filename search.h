#ifndef SEARCH_H
#define SEARCH_H

#include "string.h"
#include <stdlib.h>

typedef struct Search Search;

Search * search_read();
void search_process(Search * se);
void search_print(Search * se);
String * search_get_word(Search * se);

#endif