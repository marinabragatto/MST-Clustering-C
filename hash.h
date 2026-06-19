#ifndef HASH_H
#define HASH_H

#include "string.h"
#include <stdint.h>


typedef struct Hash Hash;

Hash* hash_init();

Hash* hash_put(Hash* hash, String* key);

Hash* hash_resize(Hash* hash);

//uint32_t horner(String* string);

#endif