#define HASHSIZE 101

typedef struct {
    struct nlist *next;
    char *name;
    char *defn;
} nlist;

unsigned hash(char *s);
nlist *lookup(char *s);
nlist *install(char *name, char *defn);