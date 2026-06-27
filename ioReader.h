#ifndef ioReader_H
#define ioReader_H

#include "vector.h"
#include "simbolTable.h"
#include "stringMapVector.h"
#include "utils.h"

ST * read_stop_words(char * dir);

ST * read_terms(char * dir,  StringMapVector * pages, ST * stop_words);

void read_pages_graph(char * dir, StringMapVector * pages);

StringMapVector * read_pages_name(char * dir);


#endif