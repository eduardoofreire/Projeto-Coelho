#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stable.h"

#define M 31
#define amax 10
//#define data (insResu->data)

/*
typedef union {
  int i;
  char *str;
  void *p;
} EntryData;

// Return struct for stable_insert.
typedef struct {
  int new;  // Was a new entry created?
  EntryData *data;  // Data associated with entry.
} InsertionResult;
*/
typedef struct reg celula;
struct reg {
  const char *key;
  EntryData *data;
  celula *prox;
  int i;
  int n;
};

struct stable_s{
	int n;
	int m;
  celula *celulas;
  //double a = m/n
};

SymbolTable stable_create(){
  SymbolTable st = malloc(sizeof(SymbolTable));
  st->m = M;
  st->celulas = malloc(sizeof(celula)*st->m);
  st->n = 0;
  return st;
}

celula *getCelula(SymbolTable table, int i) {
  if (i > M-1) return NULL;
  celula *p;
  p = table->celulas;
  return p + i;
}

/*
  Destroy a given symbol table.
*/
void stable_destroy(SymbolTable table){
  free(table);
}


int hash (const char *s, int m) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = (h * 256 + s[i]) % m;
   return h;
}

/*
  Insert a new entry on the symbol table given its key.

  If there is already an entry with the given key, then a struct
  InsertionResult is returned with new == 0 and data pointing to the
  data associated with the entry. Otherwise, a struct is returned with
  new != 0 and data pointing to the data field of the new entry.

  If there is not enough space on the table, or if there is a memory
  allocation error, then crashes with an error message.
*/

InsertionResult stable_insert(SymbolTable table, const char *key){
    InsertionResult *ir = malloc(sizeof(InsertionResult));
    int h = hash(key, M);
    celula *cel = getCelula(table, h);

    while ( cel->key != NULL ) {
      if (strcmp(cel->key,key)==0) {
        ir->new = 0;
        ir->data = cel->data;
        return *ir;
      }
      if (cel->prox == NULL) cel->prox = malloc(sizeof(celula));
      cel = cel->prox;
    }
    //Cria celula
    celula *c = malloc(sizeof(celula)); //Celula auxiliar
    c->data = malloc(sizeof(EntryData));
    c->key = key;
    *cel = *c; //copia para celula
    free(c); //Apaga celula auxiliar
    //Set IR
    ir->new = 1;
    ir->data = cel->data;

    table->n++;
    return *ir;
}

/*
  Find the data associated with a given key.

  Given a key, returns a pointer to the data associated with it, or a
  NULL pointer if the key is not found.
*/
EntryData *stable_find(SymbolTable table, const char *key){
  EntryData *ed;
  int h = hash(key, M);
  celula *cel = getCelula(table, h);
  while ( cel->key != NULL ) {
    if (strcmp(cel->key,key)==0) {
      ed = cel->data;
      return ed;
    }
    cel = cel->prox;
    if (cel == NULL) break;
  }
  ed = malloc(sizeof(EntryData));
  ed = NULL;
  return ed;
}

/*
  Visit each entry on the table.

  The visit function is called on each entry, with pointers to its key
  and data. If the visit function returns zero, then the iteration
  stops.

  Returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
/*
int stable_visit(SymbolTable table, int (*visit)(const char *key, EntryData *data)){

}
*/


void print(SymbolTable st) {
  celula *cel;
  printf("Entries: %d\n", st->n);
  for (int i = 0; i < M; i++) {
    cel = getCelula(st,i);
    printf("%d: ", i);
    while(cel!=NULL) {
      printf("(%s,%d) ", cel->key, cel->data->i);
      cel = cel->prox;
    }
    printf("\n");
  }
}

int main(){
  

	SymbolTable st = stable_create();
  /*
  for (int i = 0; i < st->m; i++) {
    celula *c = getCelula(st, i);
    c->i = i;
  }
  celula *c = getCelula(st, 10);
  for (int i = 0; i < st->m; i++) {
    celula *c = getCelula(st, i);
    printf("%d\n", c->i);
  }*/

  for (int i = 0; i < 90; ++i) {
    char *c = malloc(sizeof(char));
    *c = 33 + i;
    //printf("%s %d %d \n", c , i, hash(c,M));
    InsertionResult ir = stable_insert(st,c);
    ir.data->i = i;
  }

  celula *cel;
  //printf("\n");
  /*
  cel = getCelula(st,10);
  printf("%s %d\n", cel->key, cel->data->i);
  cel = getCelula(st,24);
  printf("%s %d\n", cel->key, cel->data->i);

  InsertionResult ir = stable_insert(st,cel->key);
  ir.data->i = 645;
  */
  InsertionResult ir = stable_insert(st,"projetochato");
  ir.data->i = 10;
  EntryData *ed = stable_find(st,"projetochato");
  ed->i = 999999;
  print(st);
}