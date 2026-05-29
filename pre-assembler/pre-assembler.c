#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib/utils.h"
#define MAXLINE 81

static nlist *macrotab[HASHSIZE];
int pre_assemble(FILE *f, FILE *write);
void getword(char word[], char line[]);

int main(int argc, char *argv[]){

    int i;
    FILE *f, *write;
    if(argc < 2){
        fprintf(stderr, "pre-assembler error: no given files");
    }
    for(i=1; i<argc; i++){
        f = fopen(argv[i],"r"), write = fopen(strcat(argv[i],"-PP"),"w");
        pre_assemble(f, write);
    }
    
}

int pre_assemble(FILE *f, FILE *write){
    char line[MAXLINE], word[MAXLINE], macroName[MAXLINE], *macroContent = (char *) malloc(0);
    unsigned hashed;
    int mcro, line_count = 0;
    nlist *np;
    while(fgets(line, MAXLINE, f)){
        getword(word, line);
        if((np = lookup(word,macrotab))){ /*if first word is a macro name*/
            fwrite(np->defn, sizeof(char), sizeof(*np->defn), write);
        }
        hashed = hash(word, macrotab);
        getword(macroName, line);
        if(hashed == hash("mcro", macrotab)){ /*if first word is a macro decleration*/
            getword(word, line);
            if(!lookup(word, macrotab)){ /*make sure new macro isnt already defined*/
                mcro=1;
                while(fgets(line, MAXLINE, f)){ 
                    getword(word,line);
                    if(mcro && hash(word, macrotab) != "mcroend"){
                        line_count++;
                        realloc(macroContent, MAXLINE * line_count);
                        strcat(macroContent, line);
                    }
                    /*TODO: remove mcroend from file*/
                    install(macroName, macroContent, macrotab); /*add the macro to macrotab*/
                    mcro = 0;
                    continue;
                } 
                continue;
            }
            fprintf(stderr, "macro %s already defined", word);
            mcro = 0;
        }
        fwrite(line, sizeof(char), sizeof(line), write);
    }
    return 1;

}

void getword(char word[], char line[]){
    char c;
    int i = 0, j = 1;
    while(isspace((c = line[i++])))
        ;
    word[1] = c;
    while(!isspace((line[i++]))){
        word[++j] = c;
    }
    word[j] = '\0';
}