#include <stdio.h>
#include "system.h"

int main(int argc, char * argv []){
    char * dir = argv[1];
    System * sys = system_init(dir);
    system_execute(sys);
    system_destroy(sys);
    return 0;
}