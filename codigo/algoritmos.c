#include "algoritmos.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

#define DEBUGA printf("Debugando\n");

//Função que corrige a posicao quando testamos ao contrario
int tau(int n, int tam_string_tratada, int tam_string_original){
    if(n <= -1) return -1;
    else return ((tam_string_tratada - n)%tam_string_original) +1;
}

//Função para calcular o máximo entre dois números inteiros
int max(int a, int b){
    return (a > b) ? a : b;
}

//Abordagem por força bruta
int forca_bruta(char *texto, char *padrao){
    int tam_texto = strlen(texto);
    int tam_padrao = strlen(padrao);
    
    for(int i = 0; i <=tam_texto-tam_padrao; i++){
        int j;
        
        for(j = 0; j <tam_padrao; j++){
            if(texto[i + j] != padrao[j]){
                break;
            }
        }
        
        if(j == tam_padrao){
            return i+1;
        }
    }
    return -1;
}

//Função para pré-processar o padrão e criar a tabela de saltos
void pre_processamento(char *padrao, int tam_padrao, int *tabela_salto){
    
    for(int i = 0; i < 256; i++){
        tabela_salto[i] = tam_padrao;
    }

    //Preencher a tabela de saltos com o valor correto para cada caractere do padrão
    for(int i = 0; i < tam_padrao - 1; i++){
        tabela_salto[padrao[i]] = tam_padrao - 1 - i;
    }
}

//BMH
int BMH(char *texto, char *padrao){
    int texto_len = strlen(texto), tam_padrao = strlen(padrao);
    int *tabela_salto = (int*)malloc(sizeof(int)*256);
    
    int i, j;

    pre_processamento(padrao, tam_padrao, tabela_salto);

    i = tam_padrao - 1;
    while(i < texto_len){
        j = tam_padrao - 1;

        while(j >= 0 && texto[i] == padrao[j]){
            i--;
            j--;
        }

        if(j == -1){
            free(tabela_salto);
            return i + 2; //Retornar a posição do primeiro casamento
        }

        //Calcular o próximo salto baseado na tabela de saltos
        i += max(tabela_salto[texto[i]], tam_padrao - 1 - j);
    }
    free(tabela_salto);
    return -1; //Caso não haja casamento
}

//Função para construir a tabela de prefixo/sufixo do padrão
void construirTabelaPrefixo(char *padrao, int *tabelaPrefixo){
    int m = strlen(padrao);
    int i = 0, j = -1;
    tabelaPrefixo[0] = -1;

    while(i < m){
        while(j >= 0 && padrao[i] != padrao[j]){
            j = tabelaPrefixo[j];
        }
        i++;
        j++;
        tabelaPrefixo[i] = j;
    }
}

//KMP
int KMP(char *texto, char *padrao){
    int n = strlen(texto);
    int m = strlen(padrao);
    int *tabelaPrefixo = (int*)malloc(sizeof(int)*(m + 1));
    int i = 0, j = 0;

    construirTabelaPrefixo(padrao, tabelaPrefixo);

    while(i < n){
        while(j >= 0 && texto[i] != padrao[j]){
            j = tabelaPrefixo[j];
        }
        i++;
        j++;

        if(j == m){
            free(tabelaPrefixo);
            return i - j; //Retornar a posição do primeiro casamento
        }
    }

    free(tabelaPrefixo);
    return -1; //Caso não haja casamento
}

/*ESSA SEÇÃO CONTÉM CÓDIGOS QUASE IDÊNTICOS, VARIANDO SOMENTE A CHAMADA DOS ALGORITMOS*/
//encapsula os tratamentos de ambiguidades causados pela nossa abordagem
int faz_forBru(char* pedra, char* pedra_ao_contrario, char *seq_poder, FILE* input, FILE *output){
    int resultado, resultado_contrario; 
    double tempo_usuario, tempo_sistema;
    struct rusage comeco, fim;

    getrusage(RUSAGE_SELF, &comeco);                          
    resultado = forca_bruta(pedra, seq_poder);
    resultado_contrario = forca_bruta(pedra_ao_contrario, seq_poder); 
    resultado_contrario = tau(resultado_contrario, strlen(pedra_ao_contrario), strlen(pedra)/2); 
    getrusage(RUSAGE_SELF, &fim);

    tempo_usuario = (double)(fim.ru_utime.tv_sec-comeco.ru_utime.tv_sec)+(double)(fim.ru_utime.tv_usec-comeco.ru_utime.tv_usec)/1000000.0;
    tempo_sistema = (double)(fim.ru_stime.tv_sec-comeco.ru_stime.tv_sec)+(double)(fim.ru_stime.tv_usec-comeco.ru_stime.tv_usec)/1000000.0;          
    printf("Tempo usuario: %lf\tTempo sistema: %lf\n", tempo_usuario, tempo_sistema); 

    if(resultado >= 0){
        fprintf(output,"S %d\n", resultado);
    }
    else if(resultado == -1 && resultado_contrario == -1){
        fprintf(output,"N \n");
    }
    else{
        fprintf(output,"S %d\n", resultado_contrario);
    }
}
//encapsula os tratamentos de erros causados pela nossa abordagem
int faz_BMH(char* pedra, char* pedra_ao_contrario, char *seq_poder, FILE* input, FILE* output){
    int resultado, resultado_contrario; 
    double tempo_usuario, tempo_sistema;
    struct rusage comeco, fim;

    getrusage(RUSAGE_SELF, &comeco);
    resultado = BMH(pedra, seq_poder);
    resultado_contrario = BMH(pedra_ao_contrario, seq_poder); 
    resultado_contrario = tau(resultado_contrario, strlen(pedra_ao_contrario), strlen(pedra)/2); 
    getrusage(RUSAGE_SELF, &fim);

    tempo_usuario = (double)(fim.ru_utime.tv_sec-comeco.ru_utime.tv_sec)+(double)(fim.ru_utime.tv_usec-comeco.ru_utime.tv_usec)/1000000.0;
    tempo_sistema = (double)(fim.ru_stime.tv_sec-comeco.ru_stime.tv_sec)+(double)(fim.ru_stime.tv_usec-comeco.ru_stime.tv_usec)/1000000.0;          
    printf("Tempo usuario: %lf\tTempo sistema: %lf\n", tempo_usuario, tempo_sistema); 

    if(resultado >= 0){
        fprintf(output,"S %d\n", resultado);
    }
    else if(resultado == -1 && resultado_contrario == -1){
        fprintf(output,"N \n");
    }
    else{
        fprintf(output,"S %d\n", resultado_contrario);
    }
}
//encapsula os tratamentos de erros causados pela nossa abordagem
int faz_KMP(char* pedra, char* pedra_ao_contrario, char *seq_poder, FILE* input, FILE *output){
    int resultado, resultado_contrario; 
    double tempo_usuario, tempo_sistema;
    struct rusage comeco, fim;

    getrusage(RUSAGE_SELF, &comeco);
    resultado = forca_bruta(pedra, seq_poder); 
    resultado_contrario = forca_bruta(pedra_ao_contrario, seq_poder); 
    resultado_contrario = tau(resultado_contrario, strlen(pedra_ao_contrario), strlen(pedra)/2); 
    getrusage(RUSAGE_SELF, &fim);

    tempo_usuario = (double)(fim.ru_utime.tv_sec-comeco.ru_utime.tv_sec)+(double)(fim.ru_utime.tv_usec-comeco.ru_utime.tv_usec)/1000000.0;
    tempo_sistema = (double)(fim.ru_stime.tv_sec-comeco.ru_stime.tv_sec)+(double)(fim.ru_stime.tv_usec-comeco.ru_stime.tv_usec)/1000000.0;          
    printf("Tempo usuario: %lf\tTempo sistema: %lf\n", tempo_usuario, tempo_sistema); 

    if(resultado >= 0){
        fprintf(output,"S %d\n", resultado);
    }
    else if(resultado == -1 && resultado_contrario == -1){
        fprintf(output, "N \n");
    }
    else{
        fprintf(output, "S %d\n", resultado_contrario);
    }
}
