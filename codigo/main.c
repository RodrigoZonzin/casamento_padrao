#include <stdio.h>
#include <stdlib.h>

#include "tratastring.h"
#include "algoritmos.h"


int main(int argc, char** argv){ 
    double tempo_usuario, tempo_sistema;
    //nome.txt ==> nome.out
    char *nome_aqr_saida = muda_extensao(argv[1]); 
    
    FILE *input = fopen(argv[1], "r"); 
    FILE *output = fopen(nome_aqr_saida, "w+");
    

    //Lendo a primeira linha para descobrir quanto preciso alocar
    int T; 
    fscanf(input, "%d", &T);    

    //Alocando T pedras e T seququencias do poder
    char **seq_poder = aloca_sequencia(T); 
    char **pedra = aloca_pedra(T), **pedra_ao_contrario = aloca_pedra(T); 
    char **pedra_dobrada;
   
    //Lendo do arquivo
    for(int i = 0; i<T; i++){
        fscanf(input, "%s %s", seq_poder[i], pedra[i]);
    }

    //dobrando uma pedra e revertendo-a para a segunda abordagem
    pedra_dobrada = dobra_sequencia(pedra, T);
    pedra_ao_contrario = reverte_pedra(pedra_dobrada, T); 


    int  abordagem = atoi(argv[2]);     
    int resultado, resultado_contrario; 
    
    //executa o algoritmo e escreve o resultado em output
    if(abordagem == 1){
        for(int i = 0; i<T; i++){
            faz_forBru(pedra_dobrada[i], pedra_ao_contrario[i], seq_poder[i], input, output); 
        }
        
    }
    
    if(abordagem == 2){
        for(int i = 0; i<T; i++){  
            faz_BMH(pedra_dobrada[i], pedra_ao_contrario[i], seq_poder[i], input, output);
        }
    }

    if(abordagem == 3){
        for(int i = 0; i<T; i++){
            faz_KMP(pedra_dobrada[i], pedra_ao_contrario[i], seq_poder[i], input, output); 
        }
    }
        
    destroi_pedra(pedra, T);
    destroi_pedra(pedra_ao_contrario, T);
    destroi_pedra(pedra_dobrada, T);
    destroi_sequencia(seq_poder, T); 
    free(nome_aqr_saida);
    fclose(input);
    fclose(output);
    
    

    return 0; 
}

