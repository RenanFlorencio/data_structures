#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
 
p_fila criar_fila(){
    /* Cria uma fila de tamanho 500 e retorna o ponteiro */
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila -> vetor = malloc(500 * sizeof (char));
    fila -> inicio = 0;
    fila -> fim = 0;
    fila -> tamanho = 500;
    fila -> usado = 0;
    return fila;
}
 
void enfileirar(p_fila fila, char linha[], int tamanho){
    /* Infileira a linha */
    for (int i = 0; i < tamanho; i++){
        fila -> vetor[fila -> fim] = linha[i];
        fila -> fim = (fila -> fim + 1) % fila -> tamanho; 
        fila -> usado ++;
    }
}
 
char desenfileirar(p_fila fila, int qntd){
    /* Desinfileira o primeiro caractere da fila */
    char c;
    c = fila -> vetor[fila -> inicio];
    fila -> inicio = (fila -> inicio + 1) % fila -> tamanho;
    fila -> usado --;
    return c;
}
 
void imprime_fila(p_fila fila){
    /* Imprime a fila */
    printf("FILA ATUAL: ");
    for(int i = fila->inicio; i < fila->fim; i++){
        printf("%c", fila -> vetor[i]);
    }
    printf("\n");
}
 
void liberar_fila(p_fila fila){
    /* Desaloca a fila */
    free(fila->vetor);
    free(fila);
}