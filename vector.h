/**
 * @file vector.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Estrutura opaca que representa um Vetor dinâmico.
 */
typedef struct Vector Vector; 

/**
 * @brief Ponteiros de funções para manipulação genérica de elementos.
 */
typedef void (*destroy_func)(void *); 
typedef void (*print_func)(void *); 
typedef int (*compare_func)(void*, void*); 
typedef int (*compare_tosort_func)(const void*, const void*);


/**
 * @brief Cria um novo vetor genérico.
 * 
 * @param max_size Tamanho inicial máximo do vetor.
 * @param destroy Ponteiro de função para liberar a memória dos elementos inseridos.
 * @return Vector* Ponteiro para o vetor criado.
 */
Vector * vector_create(int max_size, destroy_func destroy);

/**
 * @brief Insere um novo elemento no vetor.
 *
 * @param vet Ponteiro para o vetor.
 * @param element Ponteiro para o elemento a ser inserido.
 */
void vector_insert(Vector * vet, void * element);

/**
 * @brief Libera a memória alocada para um vetor, aplicando a função destroy em cada elemento interno.
 * 
 * @param vet Ponteiro void para o vetor.
 */
void vector_destroy(void * vet);

/**
 * @brief Imprime todos os elementos do vetor utilizando a função de impressão fornecida.
 *
 * @param vet Ponteiro para o vetor.
 * @param print Função para formatar a impressão do dado genérico.
 */
void vector_print(Vector * vet, print_func print);

/**
 * @brief Obtém o número de elementos inseridos no vetor.
 * * @param vet Ponteiro para o vetor.
 * @return int Tamanho atual do vetor.
 */
int vector_size(Vector * vet);

/**
 * @brief Obtém um elemento pelo índice.
 * * @param vet Ponteiro para o vetor.
 * @param idx Índice do elemento desejado.
 * @return void* Ponteiro para o elemento genérico, ou NULL se o índice for inválido.
 */
void * vector_get(Vector * vet, int idx);

/**
 * @brief Obtém o último elemento inserido no vetor.
 * 
 * @param vet Ponteiro para o vetor.
 * @return void* Ponteiro para o último elemento.
 */
void * vector_get_last(Vector * vet);

/**
 * @brief Compara se o tamanho do primeiro vetor é menor que o do segundo vetor.
 * * @param vet1 Ponteiro void para o primeiro vetor.
 * @param vet2 Ponteiro void para o segundo vetor.
 * @return int 1 se vet1 for maior que vet2, -1 se vet1 for menor que vet2 ou 0 se os tamanhos forem iguais.
 */
int vector_compare_smaller(void * vet1, void * vet2);

/**
 * @brief Busca o menor elemento do vetor.
 *
 * @param vet Ponteiro para o vetor.
 * @param compare Ponteiro de função de comparação.
 * @return void* Ponteiro para o menor elemento encontrado.
 */
void * find_min(Vector * vet, compare_func compare);
// alguma implementação generica de vet, vetor , etc

/**
 * @brief Ordena os elementos do vetor utilizando a função de comparação.
 * 
 * @param vet Ponteiro para o vetor.
 * @param compare Ponteiro para a função de comparação.
 */
void vector_sort(Vector* vet, compare_tosort_func compare);

#endif