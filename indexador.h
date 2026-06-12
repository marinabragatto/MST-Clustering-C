// deve guardar a simbol table de termo -> LISTA de documentos
// chave : termo
// valor : lista

#ifndef INDEX_H
#define INDEX_H

#include "list.h"

typedef struct Indexador Index; 

Index * index_create(List * docs);
void index_destroy(Index * ind);


#endif