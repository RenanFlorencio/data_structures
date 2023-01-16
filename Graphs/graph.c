#include <stdio.h>
#include <stdlib.h>
#include "header.h"

p_fila criar_fila(int n){
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->vetor = malloc(n * sizeof(int));
    fila->usado = 0;
    return fila;
}

p_grafo criar_grafo(int n_c, int n_p){
    p_grafo grafo;
    int i;
    grafo = malloc(sizeof(struct grafo));
    grafo->n_c = n_c;
    grafo->n_p = n_p;
    grafo->tamanho = n_c + n_p;
    grafo->adjacente = malloc(grafo->tamanho * sizeof(struct no));
    for (i = 0; i < grafo->tamanho; i++){
        grafo->adjacente[i] = NULL;
    }
    return grafo;
}

void liberar_nos(p_no atual){
    if (atual == NULL){
    }
    else{
        liberar_nos(atual->prox);
        free(atual);
    }
}

void liberar_grafo(p_grafo grafo){
    liberar_nos(grafo->adjacente[0]);
    free(grafo->adjacente);
    free(grafo);
}

p_grafo aumentar_grafo(p_grafo grafo){
    p_grafo novo;
    novo = malloc(sizeof(struct grafo));
    novo->n_c = grafo->n_c + 1;
    novo->n_p = grafo->n_p;
    novo->tamanho = grafo->tamanho + 1;
    novo->adjacente = malloc(novo->tamanho * sizeof(struct no));
    for (int i = 0; i < grafo->tamanho; i++){
        novo->adjacente[i] = grafo->adjacente[i];
    }
    return novo;
}

void enfileirar(p_fila fila, int vertice){
    fila->vetor[fila->usado] = vertice;
    fila->usado++;
}

int desenfileirar(p_fila fila){
    int r = fila->vetor[0];
    fila->usado--;
    for(int i = 0; i < fila->usado; i++){
        fila->vetor[i] = fila->vetor[i + 1];
    }
    return r;
}

int fila_vazia(p_fila fila){
    if (fila->usado == 0){
        return 1;
    }
    return 0;
}

void destruir_fila(p_fila fila){
    free(fila->vetor);
    free(fila);
}

p_no copiar_lista_ligada(p_no original){
    p_no atual, anterior, novo, inicio;
    novo = malloc(sizeof(struct no));
    novo->id = original->id;
    novo->prox = NULL;
    anterior = novo;
    inicio = novo;

    for (atual = original->prox; atual != NULL; atual = atual->prox){
        novo = malloc(sizeof(struct no));
        novo->id = atual->id;
        anterior->prox = novo;
        novo->prox = NULL;
    }
    return inicio;
}

p_no insere_lista(p_grafo grafo, p_no lista, int vertice){
    p_no novo, atual;
    novo = malloc(sizeof(struct no));
    novo->id = vertice;
    // Inserindo na lista de forma ordenada
    if (lista == NULL || novo->id < lista->id){
        novo->prox = lista;
        return novo;
    }
    else{
        for(atual = lista; atual->prox != NULL; atual = atual->prox){
            if(novo->id < atual->prox->id){
                novo->prox = atual->prox;
                atual->prox = novo;
                return lista;
            }
        }
        atual->prox = novo;
        novo->prox = NULL;
        return lista;
    }
    return 0;
}

p_no remove_lista(p_no lista, int vertice){
    p_no atual;
    p_no anterior = lista;
    if (lista->id == vertice){
        atual = lista->prox;
        free(lista);
        return atual;
    }
    else{
        for(atual = lista; atual != NULL; atual = atual->prox){
            if (atual->id == vertice){
                anterior->prox = atual->prox;
                free(atual);
                break;
            }
        anterior = atual;
        }
    }
    return lista;    
}

void insere_aresta(p_grafo grafo, int v1, int v2){
    grafo->adjacente[v1] = insere_lista(grafo, grafo->adjacente[v1], v2);
    grafo->adjacente[v2] = insere_lista(grafo, grafo->adjacente[v2], v1);
}

p_grafo insere_vertice(p_grafo grafo, int vertice){
    p_grafo novo_grafo;
    novo_grafo = aumentar_grafo(grafo);
    
    novo_grafo->adjacente[grafo->tamanho] = copiar_lista_ligada(grafo->adjacente[vertice]);
    insere_aresta(novo_grafo, vertice, grafo->tamanho);
    return novo_grafo;
}

void remove_aresta(p_grafo grafo, int v1, int v2){
    grafo->adjacente[v1] = remove_lista(grafo->adjacente[v1], v2);
    grafo->adjacente[v2] = remove_lista(grafo->adjacente[v2], v1);
}

int eh_adjacente(p_grafo grafo, int v1, int v2){
    p_no atual;
    for(atual = grafo->adjacente[v1]; atual != NULL; atual = atual->prox){
        if (atual->id == v2){
            return 1;
        }
    }
    return 0;
}

int* busca_largura(p_grafo grafo, int vertice){
    int atual;
    int* visitados, *pai;
    p_fila fila;
    visitados = malloc(grafo->tamanho * sizeof(int));
    pai = malloc(grafo->tamanho * sizeof(int));
    fila = criar_fila(grafo->tamanho);
    for(int i = 0; i < grafo->tamanho; i++){
        pai[i] = -1;
        visitados[i] = 0;
    }
    enfileirar(fila, vertice);
    pai[vertice] = vertice;
    visitados[vertice] = 1;

    while (!fila_vazia(fila)){
        atual = desenfileirar(fila);
        for(int i = 0; i < grafo->tamanho; i++){
            if(eh_adjacente(grafo, atual, i) && !visitados[i]){
                visitados[i] = 1;
                pai[i] = atual;
                enfileirar(fila, i);
            }
        }
    }
    destruir_fila(fila);
    free(visitados);
    return pai;
}

int distancia(int* caminho, int inicio, int fim){
    int contador = 0;
    for(int i = fim; i != inicio; i = caminho[i]){
        contador++;
    }
    return contador;
}

void imprime_adjacentes(p_grafo grafo, int vertice){
    p_no atual;
    printf("%d ADICIONADO E CONECTADO A ", vertice);
    for(atual = grafo->adjacente[vertice]; atual->prox != NULL; atual = atual->prox){
        printf("%d ", atual->id);
    }
    printf("%d\n", atual->id);
}