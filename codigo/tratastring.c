#include "tratastring.h"

//CONSTRUTOR DE N PEDRAS
char** aloca_pedra(int n){
    char **s = (char**)malloc(sizeof(char*)*n); 

    for(int i = 0; i<n; i++){
        s[i] = (char*)malloc(sizeof(char)*10000); 
    }

    return s; 
}
//DESTRUTOR DAS N PEDRAS
void destroi_pedra(char** pedra, int T){
    for(int i =T-1; i>=0; i--){
        free(pedra[i]);
    }
    free(pedra);
}

//CONSTRUTOR DAS N SEQUENCIAS (UM ARRAY DE SEQUÊNCIAS DE PODER)
char** aloca_sequencia(int n){
    char **s = (char**)malloc(sizeof(char*)*n); 

    for(int i = 0; i<n; i++){
        s[i] = (char*)malloc(sizeof(char)*100); 
    }

    return s; 
}

//DESTROI AS T SEQUÊNCIAS
void destroi_sequencia(char **seq, int T){
    for(int i =T-1; i>=0; i--){
        free(seq[i]);
    }
    free(seq);
}

//DADO UMA STRING s = "ABCD"
//DOBRAMOS O TAMANHO DE s: s = ABCDABCD
char* dobra_e_concatena_pedra(char* s){
    char *seq2 = (char*)malloc(20000*sizeof(char));
    strcpy(seq2, s); 
    strcat(seq2, s);

    //free(s);
    return seq2; 
}

//Seja uma sequencia de strings S = ("abc", "mnp", "uvw")
//Essa função dobra S = ("abcabc", "mnpmnp", "uvwuvw")
char** dobra_sequencia(char** s, int n){
    char **pedra_nova = aloca_pedra(n);

    for(int i =0; i<n; i++){ 
        pedra_nova[i] = dobra_e_concatena_pedra(s[i]);
    }
    

    return pedra_nova; 
}

//Seja a string s = "abcd"
//teremos a reversão da string s' = "dcba"
char* reverte_string(char *str){
    int tam = strlen(str);
    int i, j;
    
    for (i = 0, j = tam -1 ; i < j; i++, j--){
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

//Reverte uma sequencia de strings S = ("abc", "uvw")
// S' = ("cba", "wvu")
char** reverte_pedra(char** pedra, int n){
    char **nova_pedra = aloca_pedra(n);

    for(int i =0; i<n;i++){
        nova_pedra[i] = strcpy(nova_pedra[i], pedra[i]); 
    }


    for(int i =0; i<n; i++){
        nova_pedra[i] = reverte_string(nova_pedra[i]);
    }

    //destroi_pedra(pedra, n);
    return nova_pedra; 
}


//Muda a extensão do arquivo. Exemplo entrada.txt
//teremos entrada.out
char* muda_extensao(const char *arquivo_entrada){
    char ponto_out[] = ".out";
    char *saida = (char*)malloc(sizeof(char)*strlen(arquivo_entrada));
    strcpy(saida, arquivo_entrada);

    char *posicao_ponto = strrchr(saida, '.');  
    if (posicao_ponto != NULL) {
        *posicao_ponto = '\0';  
    }
    strcat(saida, ponto_out); 

    return saida;
}