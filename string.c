#include "string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

 struct String{
    char * c;
    int len;
 };


String * string_create(char * c){
    String * s = (String*)malloc(sizeof(String));
    
    s->c = strdup(c);
    s->len = strlen(c);

    return s;
}

void string_print(void * string){
    printf("(%s)\n",((String*)string)->c);
}

int string_get_len(String* string){
    return string->len;
}

char * string_get_char_pointer(String* string, int d){ // tem que verifcar se ta dentro do len para nao fazer mem
    return string->c + d;
}

char  string_get_character(String* string, int d){ // tem que verifcar se ta dentro do len para nao fazer mem
    return string->c[d];
}

void string_tolower(String * string){

    for(int i = 0; i < string->len ; i++){
        string->c[i] = tolower((unsigned char)string->c[i]);
    }
}

int compare_from(String *s,String *t,int d){
    int min=s->len<t->len?s->len:t->len;
    for(int i=d; i < min; i++){
    if (s->c[i]<t->c[i]){ return-1;}
    if (s->c[i]>t->c[i]){ return 1;}
    }
    return s->len- t->len;
}

int compare(String *s,String *t){
    return compare_from(s,t,0);
}

void string_destroy(void * string){
    String * string_ptr = (String*)string;
    if(string_ptr){
        if(string_ptr->c)
            free(string_ptr->c);
        free(string_ptr);
    }   
}