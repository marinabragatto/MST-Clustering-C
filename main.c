/**
 * @file main.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto Pereira - 2024102881 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdio.h>
#include "system.h"

int main(int argc, char * argv []){
    char * dir = argv[1];
    System * sys = system_init(dir);
    system_execute(sys);
    system_destroy(sys);
    return 0;
}