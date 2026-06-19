#include "hash.h"
#include <stdlib.h>
#include "linkedList.h"

struct Hash{
	int n;
	int size; //tamanho do vetor
	LinkedList** keys;
};

Hash* hash_init(){
	Hash* hash = malloc(sizeof(Hash));
	hash->n = 0;
	hash->size = 200; // definir um valor
	hash->keys = (LinkedList**)malloc(hash->size * sizeof(LinkedList*));

	for(int i = 0; i < hash->size; ++i){
		hash->keys[i] = NULL;
	}
	
	return hash;

}

static uint32_t horner(String* string, int size){ // size eh da hash
	uint32_t h = 0;
	int len = string_get_len(string);
	for (int i = 0; i < len; i++) {
		h = (251*h + string_get_character(string, i)) % size;
	}
	return h;
}

Hash* hash_put(Hash* hash, String* key){
	if(hash->n > 0.75*hash->size){
		hash = hash_resize(hash);
	}

	int h = horner(key, hash->size);
	hash->keys[h] = list_insert(hash->keys[h], key);
	hash->n++;

	return hash;
}

Hash* hash_resize(Hash* hash){
	int previous_size = hash->size;
	LinkedList** previous = hash->keys;
	//int previous_n = hash->n;

	hash->n = 0;
	hash->size *= 1.5;
	hash->keys = (LinkedList**)malloc(hash->size * sizeof(LinkedList*));

	for(int i = 0; i < previous_size; i++){
		LinkedList* list = previous[i];
		if(list == NULL)
			continue;

		while(!list_empty(list)){
			String* key = list_remove_first(list);
			hash = hash_put(hash, key);
		}
		free(list);

	}

	free(previous);

	return hash;

}