#ifndef STRING_MAP_VECTOR_H
#define STRING_MAP_VECTOR_H

#include "vector.h"
#include "simbolTable.h"
#include "utils.h"


typedef struct StringMapVector StringMapVector;

StringMapVector * SMV_create(destroy_func destroy);
void SMV_insert(StringMapVector * smv, Value element, String * key);
void SMV_destroy(StringMapVector * smv);
Value SMV_get_by_idx(StringMapVector * smv, int idx);
Value SMV_get_by_key(StringMapVector * smv, Key key);
int SMV_get_size(StringMapVector * smv);


#endif