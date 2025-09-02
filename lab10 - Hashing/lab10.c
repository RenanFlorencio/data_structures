#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
 
int main(){
    p_hash hash;
    int n_processos, id;
    char operacao;
 
    scanf("%d", &n_processos);
    hash = criar_hash(2 * n_processos);
 
    for (int i = 0; i < n_processos; i++){
        scanf(" %c", &operacao);
 
        if (operacao == 'I'){
            inserir_processo(hash);
        }
        else if(operacao == 'C'){
            scanf("%d", &id);
            consultar_nome(hash, id);
        }
        else if(operacao == 'T'){
            scanf("%d", &id);
            consultar_tempo(hash, id);
        }
        else if(operacao == 'R'){
            scanf("%d", &id);
            remover_processo(hash, id);
        }
    }
    destroi_hash(hash);
    printf("FINALIZADO!");
    return 0;
}