#ifndef SYSTEM_H
#define SYSTEM_H

typedef struct System System;



System * system_init(char * dir);
void system_execute(System * sys);
void system_destroy(System * sys);


#endif