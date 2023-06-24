#define ALGORITMOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tau(int, int, int);
int forca_bruta(char*, char*);
int BMH(char *, char*); 
void construirTabelaPrefixo(char*, int*);
int KMP(char*, char*);
void pre_processamento(char*, int, int*);

int faz_forBru(char*, char*, char*, FILE*, FILE*);
int faz_BMH(char*, char*, char*, FILE*, FILE*);
int faz_KMP(char*, char*, char*, FILE*, FILE*);
