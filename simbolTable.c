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
  
}

// essa funcao deveria ir pro tad string?
int compare_character(unsigned char c1, unsigned char c2){
   
}

static ST* rec_put(ST * st, String* key, Value val, int d){ 
   
}

ST* ST_PUT(ST * st, Key key, Value val){
}

Value ST_get(Key key){

}

static bool rec_search(ST* st, String* key, int d){

}

bool ST_contains(ST * st, String * key){
}

void ST_delete(Key key){} // vai precisar remover chave?

bool ST_empty(ST* st){
}

int ST_size(){

}

void ST_destroy(ST* st){
   
}

