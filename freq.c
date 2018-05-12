#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stable.h"

int main(int argc, char **argv[]){ //pra ler arquivos como argumento, preciso desse formato. Argc indica quantidade de argumentos, o argv[index] os arquivos msm
	FILE *input = fopen(argv[1], "r");
	SymbolTable *st = stable_create(sizeof(SymbolTable));
	InsertionResult ir = malloc(sizeof(InsertionResult));
    int c;//, c = cada caractere;
    int tot_chars = 0; //total de caracteres
    char chars[];
    chars = malloc(200);
    //fseek(input, 0, SEEK_END);
	//int length = ftell(input); //descobrir tamanho do arquivo
    while ((c = fgetc(input)) != EOF) {
        if (!isblank(c)) {
        	if(c != '\n'){
        		chars[tot_chars++;] = c;
        	}
        }else{
        	if(tot_chars > 0){
        		char *key[] = malloc(tot_chars + 1);
        		for(int i = 0; i < tot_chars; i++){
        			key[i] = chars[i];
        		}
        		key[tot_chars] = '\0';
        		st.stable_insert(st, key);
        		tot_chars = 0;
        	}
        }
    }
    /*if (last != '\n') {
         count last line if not linefeed terminated 
        tot_lines++;
    }*/
    fclose(input);
}