/**
 * @file page.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Definicao do TAD Page
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef PAGE_H
#define PAGE_H

#include "simbolTable.h"
#include "string.h"
#include "vector.h"
#include "stringMapVector.h"

/**
 * @brief Estrutura opaca que representa uma página.
 */
typedef struct Page Page;

/**
 * @brief Cria uma nova página com o seu nome.
 *
 * @param name Nome da página.
 * @return Page* Ponteiro para a página criada.
 */
Page * page_create(String * name);

/**
 * @brief Insere na página a lista de páginas que apontam para ela.
 * 
 * @param page Página de referência.
 * @param page_in Páginas que estão apontando para a página atual.
 */
void page_insert_in_file(Page * page, Page * page_in);

/**
 * @brief Obtém o nome da página.
 * 
 * @param page Ponteiro para a página.
 * @return String* String contendo o nome da página.
 */
String * page_get_name(Page * page);

/**
 * @brief Define o número de páginas apontadas por essa.
 * 
 * @param page Página de referência.
 * @param out_number Quantidade de links de saída.
 */
void page_set_out_number(Page * page, int out_number);

/**
 * @brief Imprime as informações da página.
 *
 * @param page Ponteiro para a página.
 */
void print_page(Page * page);

/**
 * @brief Verifica se a página contém todas as palavras buscadas, esceto as stop words.
 * 
 * @param page Ponteiro para a página.
 * @param words Vetor de palavras buscadas.
 * @param stop_words TST contendo as stop words.
 * @return int Retorna 1 se a página possuir todas as palavras, 0 caso contrário.
 */
int page_has_words(Page * page, Vector * words, ST* stop_words); // words: palabras da busca

/**
 * @brief Insere uma palavra lida da página.
 *
 * @param page Ponteiro para a página.
 * @param word Palavra a ser inserida.
 * @param exist Indicador de controle de existência.
 */
void page_insert_word(Page * page, String * word, char * exist);

/**
 * @brief Imprime o nome da página.
 * @param page Ponteiro para a página.
 */
void print_page_v2(Page * page);

/**
 * @brief Libera a memória alocada para a página.
 * 
 * @param page Ponteiro void (convertido internamente) para a página.
 */
void page_destroy(void * page);


// PAGERANK

/**
 * @brief Define o valor do pageRank de uma página.
 * 
 * @param page Ponteiro para a página.
 * @param pr Valor do pageRank a ser atribuído.
 */
void page_set_pagerank(Page* page, double pr);

/**
 * @brief Obtém o valor atual do pageRank de uma página.
 * 
 * @param page Ponteiro para a página.
 * @return double Valor do pagerank.
 */
double page_get_pagerank(Page* page);

// void page_rank_execute(StringMapVector* pages);
Vector* page_get_in_page(Page* page);

int page_get_out_number(Page* page);


// PAGERANK POR PAGINA

/**
 * @brief Calcula o pagerank de um conjunto de páginas iterativamente.
 * 
 * @param pages Vetor contendo todas as páginas.
 */
void page_calculate_pagerank(Vector* pages);

/**
 * @brief Função de comparação para ordenação das páginas baseada na ordem decrescente de pagerank ou ordem alfabética.
 * 
 * @param page1 Ponteiro constante para a primeira página.
 * @param page2 Ponteiro constante para a segunda página.
 * @return int Resultado da comparação (<0, 0, >0).
 */
int page_compare(const void* page1, const void* page2);

//double page_get_pagerank(Page* page);

#endif