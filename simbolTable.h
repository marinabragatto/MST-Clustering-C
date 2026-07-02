/**
 * @file simbolTable.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881
 * @brief Definição da Simbol Table (TST)
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef SIMBOL_TABLE
#define SIMBOL_TABLE

#include <stdbool.h>
#include "string.h"

/**
 * @brief Tipos genéricos para chaves e valores.
 */
typedef void * Key;
typedef void * Value; 

/**
 * @brief Estrutura opaca representando a Tabela de Símbolos.
 */
typedef struct SimbolTable ST;

/**
 * @brief Ponteiro para função utilizada para liberar a memória das chaves na tabela.
 */
typedef void (*destroy_func)(void *); 

/**
 * @brief Inicializa uma nova Tabela de Símbolos.
 * 
 * @return ST* Ponteiro para a tabela criada.
 */
ST * ST_init();

/**
 * @brief Insere um novo par chave/valor na Tabela de Símbolos.
 * * @param st Ponteiro para a Tabela de Símbolos.
 * @param key Chave genérica.
 * @param val Valor genérico associado à chave.
 * @return int 1 em caso de sucesso, 0 em caso de falha.
 */
int ST_PUT(ST * st, Key key, Value val);

/**
 * @brief Obtém o valor associado a uma chave.
 * 
 * @param st Ponteiro para a Tabela de Símbolos.
 * @param key Ponteiro para a chave a chave.
 * @return Value Retorna o valor associado, ou NULL se não encontrado.
 */
Value ST_get(ST * st, String * key);

//void ST_delete(Key key);

/**
 * @brief Verifica se a Tabela de Símbolos está vazia.
 * 
 * @param st Ponteiro para a Tabela de Símbolos.
 * @return true Se a tabela estiver vazia.
 * @return false Se a tabela contiver elementos.
 */
bool ST_empty(ST* st);

//int ST_size();

/**
 * @brief Libera a memória alocada para uma Tabela de Símbolos.
 * 
 * @param st Ponteiro para a Tabela de Símbolos.
 * @param destroy Função para liberar a memória dos valores inseridos.
 */
void ST_destroy(ST* st, destroy_func destroy);

#endif