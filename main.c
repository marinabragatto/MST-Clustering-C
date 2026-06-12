
#include <stdio.h>
#include "search.h"

int main(int argc, char * argv []){
    char * dir = argv[1]; 


    Search * se; 
    while(se = search_read()){
        search_print(se);
    }


    return 0;
}