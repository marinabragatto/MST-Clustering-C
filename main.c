
#include <stdio.h>
#include "system.h"

// executavel ./test ./exemplo
int main(int argc, char * argv []){
    char * dir = argv[1];
    // printf("(%s)", dir);
    System * sys = system_init(dir);
    system_execute(sys);

    //destroy
    system_destroy(sys);
    return 0;
}