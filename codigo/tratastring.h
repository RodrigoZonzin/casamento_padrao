#define TRATASTRING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char** aloca_pedra(int);
char** aloca_sequencia(int);
char** dobra_sequencia(char**, int);  
char* dobra_e_concatena_pedra(char*);
char** reverte_pedra(char**, int);
char* reverte_string(char*); 
char* muda_extensao(const char*);
void destroi_pedra(char**, int);
void destroi_sequencia(char**, int);