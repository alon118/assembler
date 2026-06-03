#define HASHSIZE 101

typedef struct {
    struct nlist *next;
    char *name;
    char *defn;
} nlist;

unsigned hash(char *s, nlist *hashtab[]);
nlist *lookup(char *s, nlist *hashtab[]);
nlist *install(char *name, char *defn, nlist *hashtab[]);
/* R type */
RCommand rCommands[] = {
    {"add",  0, 1},
    {"sub",  0, 2},
    {"and",  0, 3},
    {"or",   0, 4},
    {"nor",  0, 5},
    {"move", 1, 1},
    {"mvhi", 1, 2},
    {"mvlo", 1, 3},
    {NULL,   0, 0}
};

/* I type */
ICommand iCommands[] = {
    {"addi", 10},
    {"subi", 11},
    {"andi", 12},
    {"ori",  13},
    {"nori", 14},
    {"bne",  15},
    {"beq",  16},
    {"blt",  17},
    {"bgt",  18},
    {"lb",   19},
    {"sb",   20},
    {"lw",   21},
    {"sw",   22},
    {"lh",   23},
    {"sh",   24},
    {NULL,   0}
};

/* J type */
JCommand jCommands[] = {
    {"jmp",  30},
    {"la",   31},
    {"call", 32},
    {"hlt",  63},
    {NULL,   0}
};
