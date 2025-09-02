#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
p_mapa criar_mapa(){
    /* Cria uma árvore mapa vazia */
    p_mapa mapa = NULL;
    return mapa;
}
 
p_visitas criar_visitas(){
    /* Cria uma árvore visitas vazia */
    p_visitas visitas = NULL;
    return visitas;
}
 
p_mapa buscar_mapa(p_mapa raiz, char chave[]){
    /* Busca por uma chave (cidade) no mapa recursivamente*/
    if (raiz == NULL || strcmp(chave, raiz->nome) == 0){
        return raiz;
    }
    if (strcmp(chave, raiz->nome) < 0){
        return buscar_mapa(raiz->esq, chave);
    }
    else{
        return buscar_mapa(raiz->dir, chave);
    }
}
 
p_visitas buscar_visitas(p_visitas raiz, int data){
    /* Busca por uma data nas visitas recursivamente */
    if(raiz == NULL || data == raiz->data){
        return raiz;
    }
    if (data < raiz->data){
        return buscar_visitas(raiz->esq, data);
    }
    else{
        return buscar_visitas(raiz->dir, data);
    }
}
 
p_mapa inserir_mapa (p_mapa raiz, char nome[]){
    /* Insere uma cidade no mapa recursivamente */
    p_mapa novo;
    if (raiz == NULL){
        novo = malloc(sizeof(struct mapa));
        strcpy(novo -> nome, nome);
        novo -> qtd_visitas = 1;
        novo -> esq = novo -> dir = NULL;
        return novo;
    }
    if (strcmp(nome, raiz -> nome) < 0){
        raiz -> esq = inserir_mapa(raiz -> esq, nome);
    }
    else{
        raiz -> dir = inserir_mapa(raiz -> dir, nome);
    }
    return raiz;
}
 
p_visitas inserir_visita(p_visitas raiz, int data, char nome[], int pista){
    /* Insere uma visita nas visitas recursivamente */
    p_visitas novo;
    if (raiz == NULL){
        novo = malloc(sizeof(struct visitas));
        strcpy(novo -> nome, nome);
        novo -> data = data;
        novo -> pista = pista;
        novo -> esq = novo -> dir = NULL;
        return novo;
    }
    if (data < raiz->data){
        raiz->esq = inserir_visita(raiz->esq, data, nome, pista);
    }
    else{
        raiz->dir = inserir_visita(raiz->dir, data, nome, pista);
    }
    return raiz;
}
 
void remover_sucessor_cidade(p_mapa raiz){
    /* Caso seja necessário, inverte os nós do mapa de forma que seja possível remover o nó da árvore */
    p_mapa min = raiz->dir;
    p_mapa pai = raiz;
    while (min->esq != NULL){
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min){
        pai->esq = min->dir;
    }
    else{
        pai->dir = min->dir;
    }
    strcpy(raiz->nome, min->nome);
    raiz->qtd_visitas = min->qtd_visitas;
    free(min);
}
 
void remover_sucessor_visita(p_visitas raiz){
    /* Caso seja necessário, inverte os nós da visita de forma que seja possível remover o nó da árvore */
    p_visitas min = raiz->dir;
    p_visitas pai = raiz;
    while (min->esq != NULL){
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min){
        pai->esq = min->dir;
    }
    else{
        pai->dir = min->dir;
    }
    raiz->data = min->data;
    strcpy(raiz->nome, min->nome);
    raiz->pista = min->pista;
}
 
 
p_mapa remover_cidade(p_mapa raiz, char cidade[]){
    /* Remove uma cidade do mapa recursivamente*/
    p_mapa aux;
    if (raiz == NULL){
        return NULL;
    }
    if (strcmp(cidade, raiz->nome) < 0){
        raiz->esq = remover_cidade(raiz->esq, cidade);
    }
    else if (strcmp(cidade, raiz->nome) > 0){
        raiz->dir = remover_cidade(raiz->dir, cidade);
    }
    else if (raiz->esq == NULL){
        aux = raiz->dir;
        free(raiz);
        return aux;
    }
    else if (raiz->dir == NULL){
        aux = raiz->esq;
        free(raiz);
        return aux;
    }
    else{
        remover_sucessor_cidade(raiz);
    }
    return raiz;
}
 
p_visitas exclui_visita (p_visitas raiz, int data){
    /* Exclui uma visita das visitas recursivamente */
    p_visitas aux;
    if (raiz == NULL){
        return NULL;
    }
    if (data < raiz->data){
        raiz->esq = exclui_visita(raiz->esq, data);
    }
    else if (data > raiz->data){
        raiz->dir = exclui_visita(raiz->dir, data);
    }
    else if (raiz->esq == NULL){
        aux = raiz->dir;
        free(raiz);
        return aux;
    }
    else if (raiz->dir == NULL){
        aux = raiz->esq;
        free(raiz);
        return aux;
    }
    else{
        remover_sucessor_visita(raiz);
    }
    return raiz;
}
 
p_mapa liberar_mapa(p_mapa raiz){
    /* Libera o mapa recursivamente debaixo para cima */
    if (raiz == NULL){
        return NULL;
    }
    raiz->esq = liberar_mapa(raiz->esq);
    raiz->dir = liberar_mapa(raiz->dir);
    free(raiz);
    return raiz;
}
 
p_visitas liberar_visitas(p_visitas raiz){
    /* Libera as visitas recursivamente debaixo para cima */
    if (raiz == NULL){
        return NULL;
    }
    raiz->esq = liberar_visitas(raiz->esq);
    raiz->dir = liberar_visitas(raiz->dir);
    free(raiz);
    return raiz;
}
 
void relatorio_mapa(char nome[]){
    printf("ARVORE: MAPA\n");
    printf("CIDADE: %s\n", nome);
    printf("INSERIDO COM SUCESSO!\n");
    printf("####\n");
}
 
void relatorio_visitas(int data, char nome[]){
    printf("ARVORE: VISITA\n");
    printf("DATA: %d\n", data);
    printf("CIDADE: %s\n", nome);
    printf("INSERIDO COM SUCESSO!\n");
    printf("####\n");
}
 
void relatorio_cidade(p_mapa cidade){
    printf("CIDADE: %s\n", cidade->nome);
    printf("QUANTIDADE DE VISITAS RESTANTES: %d\n", cidade->qtd_visitas - 1);
    printf("####\n");
}
 
void relatorio_datas(p_visitas raiz, int inicio, int fim){
    /* Verifica se uma data está no invetervalo e imprime em ordem crescente */
    if (raiz->esq != NULL){
        relatorio_datas(raiz->esq, inicio, fim);
    }
    if (raiz-> data <= fim && raiz->data >= inicio){
        printf("DATA: %d\n", raiz->data);
        printf("CIDADE: %s\n", raiz->nome);
        printf("####\n");
    }
    if (raiz->dir != NULL){
        relatorio_datas(raiz->dir, inicio, fim);
    }
}
 
void relatorio_pistas(p_visitas raiz, int inicio, int fim){
    /* Verifica se há uma pista no intervalo de datas e imprime em ordem decrescente */
    if (raiz->dir != NULL){
        relatorio_pistas(raiz->dir, inicio, fim);
    }
 
    if (raiz->pista == 1 && raiz-> data <= fim && raiz->data >= inicio ){
        printf("DATA: %d\n", raiz->data);
        printf("CIDADE: %s\n", raiz->nome);
        printf("####\n");
    }
 
    if (raiz->esq != NULL){
        relatorio_pistas(raiz->esq, inicio, fim);
    }
}