/**
 * @file stringMapVector.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Implementação do TAD StringMapVector
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "stringMapVector.h"

struct StringMapVector{
    Vector * vet; /* Vetor de Paginas Armazenadas */
    ST * string_idx; /* Dado o nome de uma pagina, em que indice do vetor ela se encontra */

};

StringMapVector * SMV_create(destroy_func destroy){
    StringMapVector * smv = (StringMapVector*)malloc(sizeof(StringMapVector));
    if(smv==NULL){
        perror("Erro ao realizar o malloc");
        exit(1);
    }

    smv->vet = vector_create(VECTOR_SZ, destroy);
    smv->string_idx = ST_init(); 
    return smv;
}


void SMV_insert(StringMapVector * smv, Value value, String * key){

    int  * idx = (int*)malloc(sizeof(int));
    if(idx==NULL){
        perror("Erro ao realizar o malloc");
        exit(1);
    }
    
    *idx = vector_size(smv->vet);
    int sucess = ST_PUT(smv->string_idx, key, idx); // Aqui estamos considerando que nao vai tentar inserir a mesma coisa duas vezes
    if(sucess == 0){
        free(idx);
        return;
    }
    vector_insert(smv->vet, value);

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
    if(idx_vet)
        return vector_get(smv->vet, *idx_vet); 
    return NULL;
}


int SMV_get_size(StringMapVector * smv){
    if(smv)
        return vector_size(smv->vet);

    return -1; /* erro */
}