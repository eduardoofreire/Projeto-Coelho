#include "stable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cmpfunc(const void *a, const void *b) 
{ 
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
}



char *makeword(char* word, int c){
  char* str = malloc(1+strlen(word));
  strcpy(str, word);
  
  strcat(str, &c);
  return str;
}

void numspaces (int count) {
  for(int j = 0; j < count; j++){
    printf(" ");
    }
}

int main(int numargs, char *arg[]) {

  
  FILE *entrada;
  int tam_maior_palavra = 0;
  const char *arq = arg[1];
  entrada = fopen(arq, "r");
  int c;
  char* palavra;
  palavra = malloc(200);
  char* lista[1000000];
  int i = 0;
  SymbolTable st = stable_create(sizeof(SymbolTable));
  InsertionResult ir;
  
  while ((c = fgetc(entrada)) != EOF){
    if(!isblank((char)c) && c != '\n'){
      palavra = makeword(palavra, c);
      // printf("%s ", palavra); //teste se as letras estao sendo colocadas na string
    }
    else if (strlen(palavra)!=0){
      int length = strlen(palavra);
      if(length > tam_maior_palavra) //guarda o tamanho da maior palavra
	tam_maior_palavra = length;
      
      ir = stable_insert(st, palavra); //insere na ST
      if(ir.new == 0){
	ir.data->i++;  //aumenta a ocorrencia se ela ja existir
	//printf("palavra %s e ocorr: %d\n\n", palavra, ir.data->i);
      }
      else    {
	lista[i++] = strdup(palavra);
	ir.data->i++;
	//printf("palavra %s e ocorr: %d\n\n", palavra, ir.data->i);
	//printf("%d - %d\n", ir.data->i, ir.new );
      }
      
      memset(palavra,0,sizeof(palavra));
      char* palavra = malloc(200);
    }

  }
    
  fclose(entrada);

  //imprime as palavras que estao na lista
  for(int j = 0; j < i; j++)
  qsort(lista, i, sizeof(char*), cmpfunc);
  
  for(int j = 0; j < i; j++){
    EntryData *ed = stable_find(st, lista[j]);
    int ap = ed->i;
    int space = tam_maior_palavra - strlen(lista[j]) + 1;

    
    printf("%s",lista[j]);
    numspaces(space);
    printf("%d\n", ap);
    
    // printf("%s", space);
  
  }

  return 1;
  
}
