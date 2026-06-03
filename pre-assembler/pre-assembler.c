#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main/assembler.h"
#include "lib/utils.h"

static nlist *macrotab[HASHSIZE];
void getword(char word[], char line[]);


/*gets file *f and *write. reads f writes a pre assembled version to write. deployes all macros in f*/
int pre_assemble(FILE *f, FILE *write){
    char line[MAXLINE], word[MAXLINE], macroName[MAXLINE], *macroContent = (char *) malloc(0), *tmp; /*initialize a few char[] and a char* with malloc*/
    unsigned hashed; /*hashed representation for a word for comapring to keywords*/
    int mcro, line_count = 0; /*initialize mcro flag and line count that is set to 0*/
    nlist *np; 
    while(fgets(line, MAXLINE, f)){ /*while f has more lines*/
        getword(word, line); /*get the first word and put it in word*/
        if((np = lookup(word,macrotab))){ /*if first word is a macro name*/
            fwrite(np->defn, sizeof(char), sizeof(*np->defn), write); /*write the content of the macro to the file*/
            continue; 
        }
        hashed = hash(word, macrotab); /*hash the word in macrotab*/
        if(hashed == hash("mcro", macrotab)){ /*if first word is a macro decleration*/
            getword(macroName, line); /*place the next word in macroName*/
            if(gettype(macroName, *tmp)){
                fprintf(stderr, "a macro cannot have the same name as a command");
                return 0;
            }
            if(!lookup(macroName, macrotab)){ /*make sure new macro isnt already defined*/
                mcro=1; /*we set mcro flag to 1*/
                while(fgets(line, MAXLINE, f)){ /*and start another loop to get the content of the macro*/ 
                    getword(word,line); /*we get the first word in word*/
                    if(mcro && hash(word, macrotab) != "mcroend"){ /*and check if mcro flag is true and that the word is not mcroend*/
                        line_count++; /*increment line_count*/
                        strcat(word, line); /*add line to the end of word*/
                        tmp = (char *) realloc(macroContent, MAXLINE * line_count); /*realloc macroContent into tmp*/
                        if(!tmp){ /*check for realloc errors*/
                            fprintf(stderr, "realloc error"); /*if we got errors we print them to stderr*/
                            return 0; 
                        }
                        macroContent = tmp; /*if realloc went well we set macroContent to tmp*/
                        strcat(macroContent, word); /*add word to the end of macroContent to add the current line to the macro*/
                        continue;
                    }
                    install(macroName, macroContent, macrotab); /*add the macro to macrotab*/
                    line_count = 0; /*reset line count*/
                    macroContent = NULL; /*make macroContent point to NULL*/
                    mcro = 0; /*reset mcro flag*/
                    break;
                } 
                continue;
            }
            free(macroContent); /*if we got here the macro was already defined so we free macroContent to avoid a memory leak*/
            fprintf(stderr, "macro %s already defined", word); /*and print an error*/
            return 0;
        }
        strcat(word, line); /*strcat line to word since getword removes it from the line*/
        fwrite(word, sizeof(char), sizeof(word), write); /*write word to the file since we added line to the rest of it*/
    }
    free(macroContent);/*reached EOF so we free the array*/
    return 1; /*and return 1*/

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