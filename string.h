/**
 * @file string.h
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief  Definição do TAD String
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef STRING_H
#define STRING_H

/**
 * @brief Redefinição do tipo char para String.
 */
typedef char  String;

/**
 * @brief Cria uma nova string a partir de um array de caracteres.
 * 
 * @param c Array de caracteres.
 * @return String* Ponteiro para a nova string alocada.
 */
String * string_create(char * c);

/**
 * @brief Imprime a string.
 *
 * @param string Ponteiro void para a string.
 */
void string_print(void * string);

/**
 * @brief Retorna o tamanho da string.
 * 
 * @param string Ponteiro para a string.
 * @return int Tamanho da string.
 */
int string_get_len(String* string);

/**
 * @brief Converte todos os caracteres da string para letras minúsculas.
 *
 * @param string Ponteiro para a string que será modificada.
 */
void string_tolower(String * string);

//pre-condicao: d < string->len
/**
 * @brief Retorna o caractere na posição d da string.
 * @pre d < string->len
 * * @param string Ponteiro para a string.
 * @param d Índice do caractere desejado.
 * @return char O caractere na posição d.
 */
char  string_get_character(String* string, int d); 

/**
 * @brief Retorna um array a partir do caractere na posição d da string.
 * 
 * @param string Ponteiro para a string.
 * @param d Índice do caractere.
 * @return char* Ponteiro para a substring.
 */
char * string_get_char_pointer(String* string, int d); 

/**
 * @brief Libera a memória alocada para a string.
 * 
 * @param string Ponteiro void para a string a ser destruída.
 */
void string_destroy(void * string);

/**
 * @brief Verifica se duas strings são iguais(case insensitive).
 * 
 * @param s Primeira string.
 * @param t Segunda string.
 * @return int Valor menor, igual ou maior que zero.
 */
int compare(String *s,String *t);

/**
 * @brief Imprime a string no formato padrão de saída.
 * 
 * @param string Ponteiro void para a string.
 */
void string_print_v2(void * string);
#endif