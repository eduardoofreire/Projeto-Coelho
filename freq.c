#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stable.h"

int cmpfunc (const void * a, const void * b) {
   return (a - b);
}

int main(int argc, char **argv){ //Argc indica quantidade de argumentos, o argv[index] os arquivos em si
	FILE *input = fopen(argv[1], "r");
	SymbolTable st = stable_create(sizeof(SymbolTable));
	InsertionResult ir;
    int c;//, c = cada caractere;
    int tot_chars = 0; //total de caracteres
    int tam_maior_palavra = 0;
    char *chars = malloc(200);
    char *words = malloc(1000 * sizeof(char));
    int n = 0;
	// le char por char e armazena num vetor enquanto nao achar espaco(logo, forma uma palavra)
    while ((c = fgetc(input)) != EOF) {
        if (!isblank(c)) {
        	if(c != '\n'){
        		chars[tot_chars++] = c;
        	}
        }else{
        	if(tot_chars > 0){
        		if(tot_chars > tam_maior_palavra){ //guarda o tamanho da maior palavra
        			tam_maior_palavra = tot_chars;
        		}
        		char *key = malloc(tot_chars + 1); //criei vetor com tamanho 200, supondo que nao existe palavra com mais de 200 chars
        		for(int i = 0; i < tot_chars; i++){//armazeno num vetor de tamanho ideal
        			key[i] = chars[i];
        		}
        		key[tot_chars] = '\0';
        		if(stable_find(st, key) == NULL){ //se nao tiver a palavra, insere
        			ir = stable_insert(st, key);
        			words[n++] = *key;			  //
        			tot_chars = 0;
        		}else{							  //se ela ja existir, aumenta a quantidade de vezes que ela aparece
        			ir.data->i++;
        		}
        	}
        }
    }
    char *print = malloc(n * sizeof(char));
    for(int i = 0; i < n; i++){
    	print[i] = words[i];
    }
    qsort(print, n, sizeof(char), cmpfunc);
    /*for(int i = 0 ; i < n; i++ ) {   
      printf("%c ", print[i]);
   }*/
    fclose(input);
}