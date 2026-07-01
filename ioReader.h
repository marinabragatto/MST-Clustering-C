/**
 * @file ioReader.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Definição de funções para a leitura dos arquivos de entrada.
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef ioReader_H
#define ioReader_H

#include "vector.h"
#include "simbolTable.h"
#include "stringMapVector.h"
#include "utils.h"
#include "search.h"

/**
 * @brief Lê o conjunto de stop words e as armazena na TST.
 * 
 * @param dir Caminho do diretório onde o arquivo se encontra.
 * @param exist Indicador de existência da palavra.
 * @return ST* Ponteiro para a TST contendo as stop words.
 */
ST * read_stop_words(char * dir,  char * exist);

/**
 * @brief Lê os termos contidos nas páginas.
 *
 * @param dir Caminho do diretório onde os arquivo se encontram.
 * @param pages Estrutura de mapeamento das páginas.
 * @param stop_words TST contendo as stop words a serem ignoradas.
 * @param exist Indicador de existência da palavra.
 * @return ST* Ponteiro para a TST da lista de termos lidos.
 */
ST * read_terms(char * dir,  StringMapVector * pages, ST * stop_words, char * exist);

/**
 * @brief Lê as conexões entre as páginas a partir do grafo de entrada.
 * 
 * @param dir Caminho do diretório onde o arquivo se encontra.
 * @param pages Estrutura de mapeamento das páginas.
 */
void read_pages_graph(char * dir, StringMapVector * pages);

/**
 * @brief Realiza a leitura e impressão dos termos buscdos.
 * 
 * @param stopwords TST contendo as stop words.
 * @return Search* Ponteiro para a estrutura de busca processada.
 */
Search * search_read_print(ST * stopwords);

/**
 * @brief Lê os nomes das páginas de entrada.
 *
 * @param dir Caminho do diretório onde o arquivo se encontra.
 * @return StringMapVector* Estrutura contendo o mapeamento dos nomes das páginas.
 */
StringMapVector * read_pages_name(char * dir);


#endif