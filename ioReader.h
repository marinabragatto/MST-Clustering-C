#ifndef ioReader_H
#define ioReader_H

#include "vector.h"
#include "simbolTable.h"
#include "stringMapVector.h"
#include "utils.h"
#include "search.h"

ST * read_stop_words(char * dir,  char * exist);
ST * read_terms(char * dir,  StringMapVector * pages, ST * stop_words, char * exist);
void read_pages_graph(char * dir, StringMapVector * pages);
Search * search_read_print(ST * stopwords);
StringMapVector * read_pages_name(char * dir);


#endif