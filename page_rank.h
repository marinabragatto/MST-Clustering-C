#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "vector.h"
#include "page.h"

typedef struct PageRank PageRank;

double page_rank(PageRank* pr, int idx);

PageRank* page_rank_execute(Vector * pages);

#endif