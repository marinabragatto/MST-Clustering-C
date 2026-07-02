/**
 * @file stringMapVector.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Definição do TAD StringMapVector
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef stringMapVector_H
#define stringMapVector_H

#include "vector.h"
#include "simbolTable.h"
#include "utils.h"

/**
 * @brief Estrutura opaca de mapeamento de Strings no Vetor.
 */
typedef struct StringMapVector StringMapVector;

/**
 * @brief Cria um novo StringMapVector.
 *
 * @param destroy Ponteiro de função para liberar os elementos armazenados.
 * @return StringMapVector* Ponteiro para a estrutura criada.
 */
StringMapVector * SMV_create(destroy_func destroy);

/**
 * @brief Insere um elemento genérico associado a uma chave string.
 * 
 * @param smv Ponteiro para a estrutura de mapeamento.
 * @param element Valor/Elemento a ser inserido.
 * @param key Chave associada ao elemento.
 */
void SMV_insert(StringMapVector * smv, Value element, String * key);

/**
 * @brief Libera a memória alocada pela estrutura StringMapVector.
 * * @param smv Ponteiro para a estrutura a ser liberada.
 */
void SMV_destroy(StringMapVector * smv);

/**
 * @brief Obtém um elemento do mapeamento pelo seu índice.
 * 
 * @param smv Ponteiro para a estrutura de mapeamento.
 * @param idx Índice do elemento desejado.
 * @return Value O valor associado ao índice.
 */
Value SMV_get_by_idx(StringMapVector * smv, int idx);


int SMV_get_idx_by_key(StringMapVector * smv, Key key);

/**
 * @brief Obtém um elemento do mapeamento pela chave.
 * 
 * @param smv Ponteiro para a estrutura de mapeamento.
 * @param key Chave buscada.
 * @return Value O valor associado à chave, ou NULL se não encontrado.
 */
Value SMV_get_by_key(StringMapVector * smv, Key key);

/**
 * @brief Obtém quantidade de elementos armazenados na estrutura.
 *
 * @param smv Ponteiro para a estrutura de mapeamento.
 * @return int Quantidade de elementos.
 */
int SMV_get_size(StringMapVector * smv);


#endif