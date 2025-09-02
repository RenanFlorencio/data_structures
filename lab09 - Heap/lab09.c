#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
 
int main(){
 
    int qtd_arq, qtd_comandos, k, id, codigo;
    char comando;
    p_fp fila;
    
    scanf("%d", &qtd_arq);
    fila = cria_fila(qtd_arq);
 
    // Inserindo os arquivos na fila
    for(int i = 0; i < qtd_arq; i++){
        inserir_fila(fila);
    }
 
    scanf("%d", &qtd_comandos);
 
    // Realizando os comandos
    for(int i = 0; i < qtd_comandos; i++){
 
        scanf(" %c", &comando);
 
        if (comando == 'R'){
            scanf("%d", &k);
            remover_processos(fila, k);
        }
 
        else if (comando == 'M'){
            scanf("%d %d", &id, &codigo);
            mudar_prio(fila, codigo, id);
        }
    }
    destroi_fila(fila);
    printf("FINALIZADO!\n");
 
    return 0;
}