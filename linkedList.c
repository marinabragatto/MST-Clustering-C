#include "linkedList.h"
#include <stdlib.h>

typedef struct Node Node;
struct Node{
	String* key;
	Node* next;
};

Node* node_create(String* key){
	Node* node = malloc(sizeof(Node));
	node->key = key;
	node->next = NULL;

	return node;
}

void node_destroy(Node* node){
	free(node);
}

struct List{
	Node* first;
	Node* last;
	//int size;
};

LinkedList* list_create(){
	LinkedList* list = malloc(sizeof(LinkedList));
	list->first = NULL;
	//list->size = 0;

	return list;
};

LinkedList* list_insert(LinkedList* list, String* key){
	Node* new = node_create(key);
	
	// lista vazia
	if(list_empty(list)){
		list->first = new;
		list->last = new;
	}
	else{
		list->last->next = new;
		list->last = list->last->next;
	}
	list->last->next = NULL;
	
}

// precisa?
/*void list_remove(LinkedList* list, String* key){
	Node* previous = NULL;
	Node* aux = list->first;

	while(aux != NULL && aux->key != key){
		previous = aux;
		aux = aux->next;
	}

	// chave nao encontrada
	if(aux == NULL) 
		return NULL;
	
	// unico elemento
	if(aux == list->first && aux == list->last){
		list->first = NULL;
		list->last = NULL;
		node_destroy(aux);
		
		return;
	}

	// ultimo elemento
	if(aux == list->last){
		list->last = previous;
		previous->next = NULL;
		node_destroy(aux);

		return;
	}

	// primeiro elemento
	if(aux == list->first)
		list->first = aux->next;

	else
		previous->next = aux->next;

	node_destroy(aux);
}
*/

//LinkedList* list_contains(LinkedList* list, String* key);

String* list_remove_first(LinkedList* list){
	// lista vazia
	if(list == NULL || list_empty(list))
		return NULL;

	//Node* previous = NULL;
	Node* aux = list->first;
	String* rtn = aux->key;

	list->first = aux->next;

	// lista ficou vazia
	if(list->first == NULL){
		list->last = NULL;
	}

	node_destroy(aux);

	return rtn;
}

bool list_empty(LinkedList* list){
	return list->first == NULL;
}

void list_destroy(LinkedList* list){
	Node* aux = list->first;
	while(aux != NULL){
		Node* next = aux->next;
		node_destroy(aux);
		aux = next;
	}
	free(list);
}
