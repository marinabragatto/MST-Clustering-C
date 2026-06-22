#ifndef IOREADER_H
#define IOREADER_H

#include "vector.h"
#include "simbolTable.h"
#include "string_map_vector.h"
#include "utils.h"

Vector * read_stop_words(char * dir);

ST * read_terms(char * dir,  StringMapVector * pages, Vector * stop_words);

void read_pages_graph(char * dir, StringMapVector * pages);

StringMapVector * read_pages_name(char * dir);


#endif