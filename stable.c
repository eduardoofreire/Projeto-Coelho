#include <stdio.h>
#include <ctype.h>
#include "stable.h"

#define M 31
#define data (insResu->data)

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
typedef struc reg celula;
struct reg {
   InsertionResult val; 
   celula *prox;
}

struct stable_s{
  celula inicio;
  int n;
}

SymbolTable stable_create(){
  SymbolTable st = malloc(sizeof(SymbolTable));
  st->inicio = null;
  st->n = 0;
}
/*
  Destroy a given symbol table.
*/
void stable_destroy(SymbolTable table){
  free(table);
}

typedef char *string;

unsigned convert (string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
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
  InsertionResult insResu = malloc(sizeof(InsertionResult));
  int h = table.lookup(key); //this method returns 0 (zero) if the symbol does not exist in the symbol table (TutorialsPoint)
  if(h != 0){  //the symbol exists!
    insResu->new = 0;
    EntryData entry = malloc(sizeof(EntryData));
    entry->str = key;
    insResu->data = entry;
    /*data = malloc(sizeof(EntryData));
    data->str = key;*/
  }else{
    insResu->new = -1;
    EntryData entry = malloc(sizeof(EntryData));
    entry->str = key;
    insResu->data = entry;
  }
  return insResu;
}

/*
  Find the data associated with a given key.

  Given a key, returns a pointer to the data associated with it, or a
  NULL pointer if the key is not found.
*/
EntryData *stable_find(SymbolTable table, const char *key){

}

/*
  Visit each entry on the table.

  The visit function is called on each entry, with pointers to its key
  and data. If the visit function returns zero, then the iteration
  stops.

  Returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
int stable_visit(SymbolTable table, int (*visit)(const char *key, EntryData *data)){

}

int main(){

}