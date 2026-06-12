#ifndef SEARCJ_H
#define SEARCJ_H

#include <stdlib.h>

typedef struct Search Search;

Search * search_read();
void search_process(Search * se);
void search_print(Search * se);

#endif