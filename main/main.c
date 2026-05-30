#include <stdio.h>
#include <string.h>
#include "assembler.h"

int main(int argc, char *argv[]){
    int i;
    FILE *f, *write;
    if(argc < 2){ /*make sure we were given at least one file*/
        fprintf(stderr, "not enough given params");
        return 1;
    }
    for(i=1; i<argc; i++){
        f=fopen(argv[i], "r"), write = fopen(strcat(argv[i],"-PP"),"w");
        if(!pre_assemble(f, write)){ /*call pre assembler and make suer no errors were given*/
            return 1; /* if errors were given we just return 1 since pre_assemble prints errors*/
        }
        /*TODO: once we implement next passes call them*/
    }

}
