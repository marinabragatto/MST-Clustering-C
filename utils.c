/**
 * @file utils.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief Implementação de funções utilitárias.
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "utils.h"

char * define_directory_path(char * dir, const char * sub_dir){
    int len = strlen(dir) + strlen(sub_dir) + 1;
    char * ptr_dir = malloc(sizeof(char) * len);
    strcpy(ptr_dir, dir);
    strcat(ptr_dir, sub_dir);

    return ptr_dir;
}


