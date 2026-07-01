/**
 * @file simbolTable.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */

// fazer tudo generico como indicado pelo prof
// podemos fazer uma implementacao mais ok e no final do curso
// como ele disse, vai ter a melhor estrutura para fazer 
// um ST, acho que é tst?
#include "simbolTable.h"
#include <stdio.h>
//#include "string.h"
#include <ctype.h>
#include <stdlib.h>

// TST: 
// Cada nó armazena: um caractere da chave, e talvez um valor.
// Cada nó tem 3 filhos: menores (esquerda), iguais (meio),
// e maiores (direita)

typedef struct TST TST;

struct TST{
    //dados
    Value val; // precisa?
    unsigned char c;
    TST *l, *m, *r;
};


struct SimbolTable{
    TST * tst;
};


static TST * new_node(unsigned char c){
    TST * tst = malloc(sizeof(TST));

    tst->c = c;
    tst->val = NULL;
    tst->l = NULL;
    tst->m = NULL;
    tst->r = NULL;

    return  tst;
}

ST * ST_init(){
    ST* st = malloc(sizeof(ST));
    st->tst = NULL;
    return st;
}

// essa funcao deveria ir pro tad string?
int compare_character(unsigned char c1, unsigned char c2){
    return tolower(c1) - tolower(c2);
}

static TST * rec_put(TST * tst, String* key, Value val, int d, int * sucess){ 
    unsigned char c = string_get_character(key, d); //key deveria ser do tipo string?
    // st vazia
    if (tst == NULL){ 
        tst = new_node(c); 
    }

    int cmp = compare_character(c, tst->c);
    // caso 1: menor, insere a esquerda
    if(cmp < 0){
        tst->l = rec_put(tst->l, key, val, d, sucess);
    }
    // caso2: maior, insere a direita
    else if(cmp > 0){
        tst->r = rec_put(tst->r, key, val, d, sucess);
    }

    //caso 3: igual (substring ja esta inserida), insere o proximo caractere
    else if(d < string_get_len(key) - 1){
        tst->m = rec_put(tst->m, key, val, d+1, sucess);
    }
    else{
        if (tst->val == NULL) {
            tst->val = val;
            *sucess = 1;
        }
    }
    return tst;
}

int ST_PUT(ST * st, Key key, Value val){
    int sucess = 0;
    st->tst = rec_put(st->tst, key, val, 0, &sucess);
    return sucess;
}

//Value ST_get(Key key){}

static Value rec_search(TST * tst, String* key, int d){
    // st vazia
    if(tst == NULL){
        //return NULL;
        return NULL;
    }
    unsigned char c = string_get_character(key, d);
    int cmp = compare_character(c, tst->c);
    // caso 1: menor, procura na esquerda
    if(cmp < 0){
        return rec_search(tst->l, key, d);
    }
    // caso 2: maior, procura na direita
    else if(cmp > 0){
        return rec_search(tst->r, key, d);
    }
    // caso 3: igual (contem substring), busca proximo caractere
    else if (d < string_get_len(key) - 1){
        return rec_search(tst->m, key, d+1);
    } 
    else {
        return tst->val;
    }
}

Value ST_get(ST * st, String * key){

    return rec_search(st->tst, key, 0);

}

//void ST_delete(Key key){} // vai precisar remover chave?

bool ST_empty(ST* st){
    return st->tst == NULL;
}

//int ST_size(){}

void rec_destroy(TST * tst, destroy_func destroy){
    if(tst != NULL){
        rec_destroy(tst->l, destroy);
        rec_destroy(tst->m, destroy);
        rec_destroy(tst->r, destroy);
        // liberar value?
        if(destroy){
            destroy(tst->val);
        }
        free(tst);
    }
}


void ST_destroy(ST* st, destroy_func destroy){
    if(st){
        rec_destroy(st->tst, destroy);
        free(st);
    }
}
