// fazer tudo generico como indicado pelo prof
#ifndef SIMBOL_TABLE
#define SIMBOL_TABLE

#include <stdbool.h>

typedef void * Key;
typedef void * Value; 
typedef struct SimbolTable ST;

ST * ST_init();

ST* ST_PUT(ST * st, Key key, Value val);

Value ST_get(Key key);

bool ST_contains(ST * st, String* key);

void ST_delete(Key key);

bool ST_empty(ST* st);

int ST_size();

void ST_destroy(ST* st);

#endif