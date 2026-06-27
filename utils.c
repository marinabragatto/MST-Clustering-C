#include "utils.h"

char * define_directory_path(char * dir, const char * sub_dir){
    int len = strlen(dir) + strlen(sub_dir) + 1;
    char * ptr_dir = malloc(sizeof(char) * len);
    strcpy(ptr_dir, dir);
    strcat(ptr_dir, sub_dir);

    return ptr_dir;
}


void print_char(void * s){
    char * s_ptr = (char*)s;
    printf("(%s)\n",s_ptr);
}
