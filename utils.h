/**
 * @file utils.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef UTIL_H
#define UTIL_H

#define STRING_SZ 100  // definir um valor para aqui
#define VECTOR_SZ 10 // definir um valor para aqui

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Concatena o diretório base com um subdiretório, gerando um caminho completo para a leitura da entrada.
 * 
 * @param dir Diretório base em formato de string.
 * @param sub_dir Subdiretório a ser concatenado.
 * @return char* Retorna um ponteiro para a nova string com o path completo.
 */
char * define_directory_path(char * dir, const char * sub_dir);

#endif
