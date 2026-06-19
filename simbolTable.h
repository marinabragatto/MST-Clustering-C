// fazer tudo generico como indicado pelo prof
#ifndef SIMBOL_TABLE
#define SIMBOL_TABLE

#include <stdbool.h>
#include "string.h"

typedef void * Key;
typedef void * Value; 
typedef struct SimbolTable ST;

typedef void (*destroy_func)(void *); 

ST * ST_init();

void ST_PUT(ST * st, Key key, Value val);

//Value ST_get(Key key);

Value ST_get(ST * st, String* key);

//void ST_delete(Key key);

bool ST_empty(ST* st);

//int ST_size();

void ST_destroy(ST* st, destroy_func destroy);

#endif