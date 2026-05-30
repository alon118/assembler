#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main/assembler.h"
#include "lib/utils.h"

static nlist *macrotab[HASHSIZE];
int pre_assemble(FILE *f, FILE *write);
void getword(char word[], char line[]);

int pre_assemble(FILE *f, FILE *write){
    char line[MAXLINE], word[MAXLINE], macroName[MAXLINE], *macroContent = (char *) malloc(0);
    unsigned hashed;
    int mcro, line_count = 0;
    nlist *np;
    while(fgets(line, MAXLINE, f)){
        getword(word, line);
        if((np = lookup(word,macrotab))){ /*if first word is a macro name*/
            fwrite(np->defn, sizeof(char), sizeof(*np->defn), write);
            continue;
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
                        continue;
                    }
                    install(macroName, macroContent, macrotab); /*add the macro to macrotab*/
                    mcro = 0;
                    break;
                } 
                continue;
            }
            fprintf(stderr, "macro %s already defined", word);
            return 0;
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