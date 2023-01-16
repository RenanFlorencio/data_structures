#include <stdio.h>
#include <stdlib.h>
#include "header.h"

p_matriz criar_matriz(){
    /* Cria uma struct de matriz que guarda a quantidade de linhas, colunas, a matriz e a 
    posição da fruta */
    int m, n;
    p_matriz matriz = malloc(sizeof(struct matriz));

    matriz -> fruta_x = -1;
    matriz -> fruta_y = -1;
    scanf("%d %d", &m, &n);
    matriz -> linhas = m;
    matriz -> colunas = n;
    matriz -> vetor = malloc(m * sizeof(int *));
    for(int i = 0; i < m; i++){
        matriz -> vetor[i] = malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            matriz -> vetor[i][j] = 0;
        }
    }
    return matriz;
}

p_fila criar_fila(){
    /* Cria uma fila que represanta a cobra, com cauda e cabeça */
    p_fila f;
    f = malloc(sizeof(struct fila));
    f -> cauda = NULL;
    f -> cabeca = NULL;
    return f;
}

void imprimir_matriz_f(p_matriz matriz){
    /* Imprime a matriz formatada para o jogo */
    for(int i = 0; i < matriz -> linhas; i++){
        for(int j = 0; j < matriz -> colunas; j++){
            
            if(matriz -> vetor[i][j] == 0){
                printf("_ ");
            }
            else if(matriz -> vetor[i][j] == 1){
                printf("# ");
            }
            else{
                printf("* ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void apagar_cobra(p_no no){
    /* Apaga todos os nós da cobra */
    if (no -> prox != NULL){
        apagar_cobra(no -> prox);
        free(no);
    }
}

void aumentar_cobra(p_fila cobra, p_matriz matriz, int x, int y){
    /* Aumenta a cobra pela cabeça */
    p_no novo = malloc(sizeof(struct no));
    novo -> x = x;
    novo -> y = y;
    novo -> prox = NULL;
    novo -> ant = NULL;
    if (cobra -> cauda == NULL){
        cobra -> cauda = novo;
    }
    else{
        cobra->cabeca->prox = novo;
        cobra->cabeca->ant = cobra->cabeca;
    }
    cobra->cabeca = novo;
    matriz -> vetor[x][y] = 1;
}

int verificar_colisao(p_matriz matriz, p_fila cobra){
    /* Verifica se houve colisão da cobra consigo mesmo verificando as posições na matriz*/
    int x = cobra->cabeca->x;
    int y = cobra->cabeca->y;
    if (matriz -> vetor[x][y] == 1){
        return 1;
    }
    return 0;
}

int venceu(p_matriz matriz, int x, int y){
    /* Verifica se todos os locais da matriz, menos o local para o qual a cobra ira se mover,
    são 1. Caso sejam, o jogo foi vencido */
    for(int i = 0; i < matriz -> linhas; i++){
        for(int j = 0; j < matriz -> colunas; j++){
            if (i != x && j != y && matriz -> vetor[i][j] != 1){
                return 1;
            }
        }
    }
    return 2;
}

void ler_fruta(p_matriz matriz){
    /* Lê as posições da fruta e a coloca na matriz */
    char comando[20];
    int x_fruta, y_fruta;
    scanf("%s", comando);
    scanf("%d %d", &x_fruta, &y_fruta);
    matriz -> fruta_x = x_fruta;
    matriz -> fruta_y = y_fruta;
    matriz -> vetor[x_fruta][y_fruta] = -1;
}

int mover_cobra(p_fila cobra, p_matriz matriz, char movimento){
    /* Move a posição da cobra, tanto os nós quanto a matriz */
    p_no atual;
    int cauda_x, cauda_y;

    // Armazenando a posição da cauda da cobra para alterá-la mais tarde
    cauda_x = cobra->cauda->x;
    cauda_y = cobra->cauda->y;
    
    // Atualizando todos os nós para as novas posições
    for(atual = cobra->cauda; atual->prox != NULL; atual = atual->prox){
        atual -> x = atual->prox->x;
        atual -> y = atual->prox->y;
        matriz -> vetor[atual -> x][atual -> y] = 1;
    }

    // Atualizando a posição da cabeça da cobra para a posição desejada
    if (movimento == 'w'){
        if (cobra->cabeca->x - 1 < 0){
            cobra->cabeca->x = matriz->colunas - 1; 
        }
        else{
            cobra->cabeca->x--;
        }
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }

    else if (movimento == 's'){
        cobra->cabeca->x = (cobra->cabeca->x + 1) % matriz->colunas;  
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }

    else if(movimento == 'a'){
        if (cobra->cabeca->y - 1 < 0){
            cobra->cabeca->y = matriz->colunas - 1; 
        }
        else{
            cobra->cabeca->y--;
        }
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }

    else if(movimento == 'd'){
        cobra->cabeca->y = (cobra->cabeca->y + 1) % matriz->colunas;
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }
    
    // Corrigindo as posições da matriz
    matriz -> vetor[cobra->cabeca->x][cobra->cabeca->y] = 1;
    matriz -> vetor[cauda_x][cauda_y] = 0;
    return 0;
}


int mover(p_fila cobra, p_matriz matriz, char move){
    /* Verifica se o jogo foi ganho, se uma fruta foi comida ou se somente houve um movimento
    Retorna 2 caso o jogo tenha sido ganho
    Retorna 1 caso o jogo tenha sido perdido
    Retorna 0 caso o jogo deva continuar */

    int x = cobra->cabeca->x;
    int y = cobra->cabeca->y;
    // Verifica se há uma maça no movimento e, se houver, aumenta o tamanho
    // Se o jogador venceu, retorna 2
    if (move == 'w'){
        if (venceu(matriz, x - 1, y) == 2){
            return 2;
        }
        if (x - 1 == matriz->fruta_x && y == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x - 1, y);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
    }
    else if (move == 'a'){
        if (venceu(matriz, x - 1, y) == 2){
            return 2;
        }
        if (x == matriz->fruta_x && y - 1 == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x, y - 1);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
    }
    else if (move == 's'){
        if (venceu(matriz, x - 1, y) == 2){
            return 2;
        }
        if (x + 1 == matriz->fruta_x && y == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x + 1, y);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
    }
    else if (move == 'd'){
        if (venceu(matriz, x - 1, y) == 2){
            return 2;
        }
        if (x == matriz->fruta_x && y + 1 == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x, y + 1);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
    }
    // Caso não houver maça, move a cobra
    if (mover_cobra(cobra, matriz, move) == 1){
        return 1;
    }
    else{
        return 0;
    }
}
