# include <stdio.h>
# include <stdlib.h>
# include "cobra.h"
 
int main(){
    char move, comando[20];
    int a, b, valido = 0;
    p_matriz matriz;
    p_fila cobra;
    // Criando as estruturas
    matriz = criar_matriz();
    cobra = criar_fila();
    // Lendo a fruta
    ler_fruta(matriz);
    // Lendo a posição, o texto de comando não é necessário
    scanf("%s", comando);
    scanf("%d %d", &a, &b);
    aumentar_cobra(cobra, matriz, a, b);
    //Matriz inicial
    imprimir_matriz_f(matriz);
 
    // Começo do loop de jogo
    while (valido == 0){
        scanf(" %c", &move);
        valido = mover(cobra, matriz, move);
 
        if (valido == 1){
            imprimir_matriz_f(matriz);
            printf("GAME OVER");
            break;
        }
 
        else if(valido == 2){
            imprimir_matriz_f(matriz);
            printf("YOU WIN");
            break;
        }
        imprimir_matriz_f(matriz);
    }
    // Desalocando os vetores utilizados
    apagar_nos(cobra -> cauda);
    apagar_matriz(matriz);
    free(matriz);
    free(cobra);
    return 0;
}