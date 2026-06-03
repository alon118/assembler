#include <string.h>
#include "utils.h"

int gettype(char *s, char *t){
    int i = 0;
    while (*s){
        if(i <= 8 && strcmp(*s, R_commands[i])){
            *t = R_commands[i];
            return 1;
        }
        if(i <= 4 && strcmp(*s, I_commands[i])){
            *t = I_commands[i];
            return 1;
        }
        if(i <= 16 && strcmp(*s, J_commands[i])){
            *t = J_commands[i];
            return 1;
        }
    }
    return 0;
}