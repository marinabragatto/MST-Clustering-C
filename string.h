#ifndef STRING_H
#define STRING_H

typedef struct String String;

String * string_create(char * c);
void string_print(String * string);

int string_get_len(String* string);

//pre-condicao: d < string->len
char string_get_character(String* string, int d); 

#endif