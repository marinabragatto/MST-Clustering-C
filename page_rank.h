#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "vector.h"

typedef struct PageRank PageRank;

void page_rank_execute(Vector * pages);

#endif