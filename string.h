#ifndef STRING_H
#define STRING_H

typedef struct String String;

String * string_create(char * c);
void string_print(String * string);

#endif