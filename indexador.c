// deve guardar a simbol table de termo -> LISTA de documentos
// chave : termo
// valor : lista

#include "indexador.h"
#include "simbolTable.h"
#include <stdlib.h>


#define MAX_ST 100 // qual valor daqui?


struct Indexador {
    ST * st_term_doc; // mapeia o termo no documento
}; 


Index * index_create(List * docs_name){
    Index * index = (Index*)malloc(sizeof(Index));

    index->st_term_doc = ST_init(MAX_ST);



    return index;
}
void index_destroy(Index * ind){

}