#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"
 
p_matriz criar_matriz(){
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
    p_fila f;
    f = malloc(sizeof(struct fila));
    f -> cauda = NULL;
    f -> cabeca = NULL;
    return f;
}
 
void imprimir_matriz_f(p_matriz matriz){
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
 
void apagar_nos(p_no no){
    if (no -> prox != NULL){
        apagar_nos(no -> prox);
    }
    no->ant = NULL;
    free(no);
}
 
void apagar_matriz(p_matriz matriz){
    for(int i = 0; i < matriz->linhas; i++){
        free(matriz -> vetor[i]);
    }
    free(matriz -> vetor);
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
    int x = cobra->cabeca->x;
    int y = cobra->cabeca->y;
 
    if (matriz -> vetor[x][y] == 1){
        return 1;
    }
    return 0;
}
 
int venceu(p_matriz matriz, int x, int y){
 
    for(int i = 0; i < matriz -> linhas; i++){
        for(int j = 0; j < matriz -> colunas; j++){
            if ((i != x || j != y) && matriz -> vetor[i][j] != 1){
                return 1;
            }
        }
    }
    matriz->vetor[matriz->fruta_x][matriz->fruta_y] = 1;
    return 2;
}
 
void ler_fruta(p_matriz matriz){
    char comando[20];
    int x_fruta, y_fruta;
    scanf("%s", comando);
    scanf("%d %d", &x_fruta, &y_fruta);
    matriz -> fruta_x = x_fruta;
    matriz -> fruta_y = y_fruta;
    matriz -> vetor[x_fruta][y_fruta] = -1;
}
 
void atualizar_nos(p_fila cobra, p_matriz matriz){
    p_no atual;
    for(atual = cobra->cauda; atual->prox != NULL; atual = atual->prox){
        atual -> x = atual->prox->x;
        atual -> y = atual->prox->y;
        matriz -> vetor[atual -> x][atual -> y] = 1;
    }
}
 
int mover(p_fila cobra, p_matriz matriz, char move){
    int cauda_x, cauda_y;
 
    // Armazenando a posição da cauda da cobra para alterá-la mais tarde
    cauda_x = cobra->cauda->x;
    cauda_y = cobra->cauda->y;
    // Atualizando todos os nós para as novas posições
    
 
    int x = cobra->cabeca->x;
    int y = cobra->cabeca->y;
    // Verifica se há uma maça no movimento e, se houver, aumenta o tamanho
    // Se o jogador venceu, retorna 2
    if (move == 'w'){
        // Corrigindo a posição
        x = x - 1 < 0 ? matriz->linhas-1 : x - 1;
        if (venceu(matriz, x, y) == 2){
            return 2;
        }
        if (x == matriz->fruta_x && y == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x, y);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
        atualizar_nos(cobra, matriz);
        cobra->cabeca->x = x;
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }
    else if (move == 'a'){
        y = y - 1 < 0 ? matriz->colunas-1 : y - 1;
        if (venceu(matriz, x, y) == 2){ 
            return 2; 
        } 
        if (x == matriz->fruta_x && y == matriz->fruta_y){ 
            aumentar_cobra(cobra, matriz, x, y); 
            imprimir_matriz_f(matriz); 
            ler_fruta(matriz); 
            return 0; 
        } 
        atualizar_nos(cobra, matriz); 
        cobra->cabeca->y = y; 
        if (verificar_colisao(matriz, cobra) == 1){ 
            return 1; 
        } 
    }
    else if (move == 's'){
        x = (x + 1) % matriz->linhas;
        if (venceu(matriz, x, y) == 2){
            return 2;
        }
        if (x == matriz->fruta_x && y == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x, y);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
        atualizar_nos(cobra, matriz);
        cobra->cabeca->x = x;
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }
    else if (move == 'd'){
        y = (y + 1) % matriz->colunas;
        if (venceu(matriz, x, y) == 2){
            return 2;
        }
        if (x == matriz->fruta_x && y == matriz->fruta_y){
            aumentar_cobra(cobra, matriz, x, y);
            imprimir_matriz_f(matriz);
            ler_fruta(matriz);
            return 0;
        }
        atualizar_nos(cobra, matriz);
        cobra->cabeca->y = y;
        if (verificar_colisao(matriz, cobra) == 1){
            return 1;
        }
    }
    // Adicionando a cabeça e removendo a cauda da matriz  
    matriz -> vetor[cobra->cabeca->x][cobra->cabeca->y] = 1;
    matriz -> vetor[cauda_x][cauda_y] = 0;
    return 0;
}