/**
 * @file system.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef SYSTEM_H
#define SYSTEM_H

/**
 * @brief Estrutura opaca que encapsula as estruturas do sistema.
 */
typedef struct System System;


/**
 * @brief Inicializa o sistema lendo os arquivos de entradas.
 * 
 * @param dir Caminho do diretório com os arquivos de entrada.
 * @return System* Ponteiro para o sistema inicializado.
 */
System * system_init(char * dir);

/**
 * @brief Execução as operações do sistema.
 * 
 * @param sys Ponteiro para o sistema.
 */
void system_execute(System * sys);

/**
 * @brief Libera toda a memória do sistema.
 * * @param sys Ponteiro para o sistema a ser liberado.
 */
void system_destroy(System * sys);


#endif