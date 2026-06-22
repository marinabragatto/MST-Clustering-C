#include "string_map_vector.h"

struct StringMapVector{
    ST * string_idx; // dado o nome de uma pagina, em que indice do vetor ela se encontra
    Vector * vet; // as paginas armazenadas

};

StringMapVector * SMV_create(destroy_func destroy){
    StringMapVector * smv = (StringMapVector*)malloc(sizeof(StringMapVector));

    smv->vet = vector_create(VECTOR_SZ, destroy);
    smv->string_idx = ST_init(); 
    return smv;
}


void SMV_insert(StringMapVector * smv, Value value, String * key){
    vector_insert(smv->vet, value);

    int  * idx = (int*)malloc(sizeof(int));
    *idx = vector_size(smv->vet) - 1;
    ST_PUT(smv->string_idx, key, idx);
}


void SMV_destroy(StringMapVector * smv){
    if(smv){
        if(smv->vet)
            vector_destroy(smv->vet);
        if(smv->string_idx)
            ST_destroy(smv->string_idx, free);

        free(smv);
    }
}

Value SMV_get_by_idx(StringMapVector * smv, int idx){
    return vector_get(smv->vet, idx);
}

Value  SMV_get_by_key(StringMapVector * smv, Key key){
    int * idx_vet = ST_get(smv->string_idx, key);
    void * element = vector_get(smv->vet, *idx_vet); 
    return element;
}


int SMV_get_size(StringMapVector * smv){
    if(smv)
        return vector_size(smv->vet);

    return -1; // erro
}