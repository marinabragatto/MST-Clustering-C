/**
 * @file string.c
 * @author Fabiola Meireles Vilaça - 2024102667
 *         Marina Bragatto ... - 
 * @brief 
 * @version 0.1
 * @date 2026-06-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>



String * string_create(char * c){
    
    char * s = strdup(c);

    return s;
}

void string_print(void * string){
    printf("(%s)\n", (char*)string);
}
void string_print_v2(void * string){
    printf("%s",(char*)string);
}

int string_get_len(String* string){
    return strlen(string);
}

char * string_get_char_pointer(String* string, int d){ // tem que verifcar se ta dentro do len para nao fazer mem
    return string + d;
}

char  string_get_character(String* string, int d){ // tem que verifcar se ta dentro do len para nao fazer mem
    return string[d];
}

void string_tolower(String * string){
    int len = strlen(string);
    for(int i = 0; i < len; i++){
        string[i] = tolower((unsigned char)string[i]);
    }
}

int compare_from(String *s,String *t,int d){
    int min= strlen(s) < strlen(t) ? strlen(s) : strlen(t);
    for(int i=d; i < min; i++){
    if (s[i]<t[i]){ return-1;}
    if (s[i]>t[i]){ return 1;}
    }
    return strlen(s)- strlen(t);
}

int compare(String *s,String *t){
    return compare_from(s,t,0);
}

void string_destroy(void * string){
    String * string_ptr = (String*)string;
    free(string_ptr);
}