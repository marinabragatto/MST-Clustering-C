// fazer tudo generico como indicado pelo prof
// podemos fazer uma implementacao mais ok e no final do curso
// como ele disse, vai ter a melhor estrutura para fazer 
// um ST, acho que é tst?
#include "simbolTable.h"
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdlib.h>

// TST: 
// Cada nó armazena: um caractere da chave, e talvez um valor.
// Cada nó tem 3 filhos: menores (esquerda), iguais (meio),
// e maiores (direita)
struct SimbolTable{
    //dados
    Value val; // precisa?
    unsigned char c;
    ST *l, *m, *r;
};


ST * ST_init(){
    ST* st = malloc(sizeof(ST));
    st->val = malloc(sizeof(Value));

    return st;
}

// essa funcao deveria ir pro tad string?
int compare_character(unsigned char c1, unsigned char c2){
    return tolower(c1) - tolower(c2);
}

static ST* rec_put(ST * st, String* key, Value val, int d){ 
    unsigned char c = string_get_character(key, d); //key deveria ser do tipo string?
    // st vazia
    if (st == NULL){ 
        st = create_node(); 
        st->c = c;
    }

    int cmp = compare_character(c, st->c);
    // caso 1: menor, insere a esquerda
    if(cmp < 0){
        st->l = rec_insert(st->l, key, val, d);
    }
    // caso2: maior, insere a direita
    else if(cmp > 0){
        st->r = rec_insert(st->r, key, val, d);
    }

    //caso 3: igual (substring ja esta inserida), insere o proximo caractere
    else if(d < string_get_len(key) - 1){
        st->m = rec_insert(st->m, key, val, d+1);
    }
    else{
        st->val = val;
    }
    return st;
}

ST* ST_PUT(ST * st, Key key, Value val){
    return rec_put(st, key, val, 0);
}

Value ST_get(Key key){

}

static bool rec_search(ST* st, String* key, int d){
    // st vazia
    if(st == NULL){
        //return NULL;
        return false;
    }
    unsigned char c = string_get_character(key, d);
    int cmp = compare_character(c, st->c);
    // caso 1: menor, procura na esquerda
    if(cmp < 0){
        return rec_search(st->l, key, d);
    }
    // caso 2: maior, procura na direita
    else if(cmp > 0){
        return rec_search(st->r, key, d);
    }
    // caso 3: igual (contem substring), busca proximo caractere
    else if (d < string_get_len(key) - 1){
        return rec_search(st->m, key, d+1);
    } 
    //else { return t; }
}

bool ST_contains(ST * st, String * key){
    return rec_search(st, key, 0);
}

void ST_delete(Key key){} // vai precisar remover chave?

bool ST_empty(ST* st){
    return st == NULL;
}

int ST_size(){

}

void ST_destroy(ST* st){
    if(st != NULL){
        ST_destroy(st->l);
        ST_destroy(st->m);
        ST_destroy(st->r);
        // liberar value?
        free(st);
    }
}

