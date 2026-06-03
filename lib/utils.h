#define HASHSIZE 101

typedef struct {
    struct nlist *next;
    char *name;
    char *defn;
} nlist;

unsigned hash(char *s, nlist *hashtab[]);
nlist *lookup(char *s, nlist *hashtab[]);
nlist *install(char *name, char *defn, nlist *hashtab[]);

RCommand rCommands[] = {
    {"add",  0, 1},
    {"sub",  0, 2},
    {"and",  0, 3},
    {"or",   0, 4},
    {"nor",  0, 5},
    {"move", 0, 6},
    {"mvhi", 0, 7},
    {"mvlo", 0, 8},
    {NULL,   0, 0} 
};

ICommand iCommands[] = {
    {"addi", 1},
    {"subi", 2},
    {"andi", 3},
    {"ori",  4},
    {"nori", 5},
    {"beq",  6},
    {"bne",  7},
    {"blt",  8},
    {"bgt",  9},
    {"lb",   10},
    {"sb",   11},
    {"lw",   12},
    {"sw",   13},
    {"lh",   14},
    {"sh",   15},
    {NULL,   0}  /* sentinel */
};

/* J type */
JCommand jCommands[] = {
    {"jmp",  1},
    {"la",   2},
    {"call", 3},
    {"hlt",  4},
    {NULL,   0}  /* sentinel */
};
