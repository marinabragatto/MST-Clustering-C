#ifndef STRING_H
#define STRING_H

typedef struct String String;

String * string_create(char * c);
void string_print(void * string);
int string_get_len(String* string);
void string_tolower(String * string);
//pre-condicao: d < string->len
char  string_get_character(String* string, int d); 
char * string_get_char_pointer(String* string, int d); 
void string_destroy(void * string);
int compare(String *s,String *t);
void string_print_v2(void * string);
#endif