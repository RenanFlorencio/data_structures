#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(){
    int m, n, qnt_op;   
    p_matriz matriz;
    char operacao1[20], operacao2[20];

    scanf("%d %d", &m, &n);
    matriz = criar_matriz(m, n);

    scanf("%d", &qnt_op);
    for (int i = 0; i < qnt_op; i++){
        scanf("%s %s", operacao1, operacao2);
        int indice;

        if (strcmp(operacao1, "IN") == 0){

            if (strcmp(operacao2, "L") == 0){
                inserir_linha(matriz);
            }
            else if (strcmp(operacao2, "C") == 0){
                inserir_coluna(matriz);
            }
        }
        else if (strcmp(operacao1, "OUT") == 0){

            scanf("%d", &indice);
            if (strcmp(operacao2, "L") == 0){
                remover_linha(matriz, indice);
            }
            else if (strcmp(operacao2, "C") == 0){
                remover_coluna(matriz, indice);
            }
        }
        imprime_matriz(matriz);
    }
    apagar_matriz(matriz);
    printf("COMBINACAO MATRICIAL FINALIZADA!");
}
