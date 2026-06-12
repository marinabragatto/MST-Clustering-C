#include "string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

void string_print(String * string){
    printf("%s",string->c);
}