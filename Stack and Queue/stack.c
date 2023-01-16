#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackHeader.h"

p_pilha criar_pilha(){
    /* Cria uma pilha vazia */
    p_pilha pilha;
    pilha = malloc(sizeof(struct pilha));
    pilha -> topo = NULL;
    return pilha;
}

p_no criar_no(){
    p_no no;
    no = malloc(sizeof(struct no));
    no -> str_usado = 0;
    no -> prox = NULL;
    return no;
}

void empilhar(p_pilha pilha, char c){
    /* Empilha o caracter tomando cuidado para verificar se a pilha é vazia ou se seu topo está cheio*/
    if (pilha -> topo == NULL){
        p_no novo;
        novo = criar_no();
        novo -> str_usado = 0;
        novo -> prox = NULL;
        pilha -> topo = novo;
    }
    else if (pilha -> topo -> str_usado == 49){
        p_no novo;
        pilha->topo->string[49] = '\000';
        novo = criar_no();
        novo -> str_usado = 0;
        novo -> prox = pilha -> topo;
        pilha -> topo = novo;
    }
    pilha->topo->string [pilha->topo->str_usado] = c;
    pilha->topo->str_usado++;
}

void desempilhar(p_pilha pilha, int qntd){
    /* Desempilha "qntd" caracteres, o contador garante que a posição correta seja removida 
    caso seja removido um nó da pilha */
    p_no aux;
    int contador = 0;
    int atual = pilha->topo->str_usado;
    for(int i = 0; i < qntd; i++){
        if(pilha->topo->str_usado > 1){
            pilha->topo->string[atual - 2 - contador] = '\000';
            pilha->topo->str_usado--;
            contador++;
        }
        else{
            // Se não tiver mais nenhum caractere, basta liberar a memória e passar a
            // desempilhar o próximo da pilha
            aux = pilha->topo;
            pilha->topo = pilha->topo->prox;
            free(aux);
            atual = 50;
            pilha->topo->string[atual - 2] = '\000';
            contador = 1;
        }
    }   
}

void imprime_recursivo(p_no topo){
    /* Auxiliar para a impressão da pilha */
    if (topo == NULL){
    }
    else{
        imprime_recursivo(topo->prox);
        printf("%s", topo->string);
    }
}

void imprime_pilha(p_no topo){
    /* Imprimir recursivamente, primeiro o final */
    printf("PILHA ATUAL: ");
    imprime_recursivo(topo);
    printf("\n####\n");
}

void libera_recursiv(p_no no){
    /* Libera a pilha recursivamente de baixo para cima */
    if (no == NULL){
    }
    else{
        libera_recursiv(no->prox);
        free(no);
    }
}

void liberar_pilha(p_pilha pilha){
    libera_recursiv(pilha->topo);
    free(pilha);
}