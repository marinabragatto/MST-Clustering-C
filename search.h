/**
 * @file search.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef SEARCH_H
#define SEARCH_H

#include "string.h"
#include "vector.h"
#include <stdlib.h>

/**
 * @brief Estrutura opaca que representa uma operação de busca.
 */
typedef struct Search Search;

/**
 * @brief Cria uma nova estrutura de busca.
 * 
 * @return Search* Ponteiro para a estrutura criada.
 */
Search * search_create();

/**
 * @brief Insere uma nova palavra buscada.
 * 
 * @param se Ponteiro para a estrutura de busca.
 * @param word String palavra buscada.
 */
void search_insert_word(Search * se, String * word);

/**
 * @brief Processa as palavras buscadas.
 * @param se Ponteiro para a estrutura de busca.
 */
void search_process(Search * se);

/**
 * @brief Imprime as palavras buscadas.
 *
 * @param se Ponteiro para a estrutura de busca.
 */
void search_print(Search * se);

/**
 * @brief Libera a memória alocada para a busca.
 * 
 * @param se Ponteiro para a estrutura de busca.
 */
void search_destroy(Search * se);

/**
 * @brief Obtém a quantidade de palavras na busca.
 * 
 * @param se Ponteiro para a estrutura de busca.
 * @return int Número de palavras.
 */
int search_num_words(Search * se);

/**
 * @brief Obtém os termos da busca.
 * 
 * @param se Ponteiro para a estrutura de busca.
 * @return Vector* Vetor de strings com as palavras da busca.
 */
Vector * search_get_words(Search * se);

#endif