#include <stdio.h>
#include <stdlib.h>

typedef struct no* p_no;
typedef struct grafo* p_grafo;
typedef struct fila* p_fila;

struct grafo {
    p_no* adjacente;
    int n_p;
    int n_c;
    int tamanho;
};

struct fila {
    int* vetor;
    int usado;
};

struct no {
    int id;
    int tipo; // 1: tipo C; 0: tipo P
    p_no prox;
};

p_fila criar_fila(int n){
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->vetor = malloc(n * sizeof(int));
    fila->usado = 0;
    return fila;
}

p_no criar_no(int tipo, int id){
    p_no novo;
    novo = malloc(sizeof(struct no));
    novo->tipo = tipo;
    novo->id = id;
    novo->prox = NULL;
    return novo;
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
    novo->tamanho = novo->n_c + novo->n_p;
    novo->adjacente = malloc(novo->tamanho * sizeof(int));
    for (int i = 0; i < grafo->tamanho; i++){
        novo->adjacente[i] = grafo->adjacente[i];
    }
    liberar_grafo(grafo);
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
    novo->tipo = original->tipo;
    novo->prox = NULL;
    anterior = novo;
    inicio = novo;

    for (atual = original->prox; atual != NULL; atual = atual->prox){
        novo = malloc(sizeof(struct no));
        novo->id = atual->id;
        novo->tipo = atual->tipo;
        anterior->prox = novo;
        novo->prox = NULL;
    }
    return inicio;
}

p_no insere_lista(p_grafo grafo, p_no lista, int vertice){
    p_no novo, atual;
    novo = malloc(sizeof(struct no));
    novo->id = vertice;
    if (vertice >= grafo->n_p){
        novo->tipo = 1;
    }
    else{
        novo->tipo = 0;
    }
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
    insere_aresta(novo_grafo, vertice, novo_grafo->tamanho - 1);
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

int main(){
    FILE* in_file = fopen("C:/Users/renae/Documents/Estrutura_de_Dados/lab11/t05_in.txt", "r");
    char op;
    int n_c, n_p, n_arestas, n_op, v1, v2;
    int dist, dist_min, inicio, fim;
    int* menor_caminho;
    p_grafo grafo;

    fscanf(in_file, "%d %d", &n_c, &n_p);
    grafo = criar_grafo(n_c, n_p);

    fscanf(in_file, "%d", &n_arestas);
    for(int i = 0; i < n_arestas; i++){
        fscanf(in_file, "%d %d", &v1, &v2);
        insere_aresta(grafo, v1, v2);
    }
    printf("GRAFO AMZ CONSTRUIDO!\n");

    fscanf(in_file, "%d", &n_op);
    for(int i = 0; i < n_op; i++){

        fscanf(in_file, " %c", &op);

        if(op == 'D'){
            fscanf(in_file, "%d %d %d", &inicio, &fim, &dist_min);
            menor_caminho = busca_largura(grafo, inicio);
            dist = distancia(menor_caminho, inicio, fim);

            printf("DISTANCIA %d -> %d = %d\n", inicio, fim, dist);
            if (dist > dist_min){
                grafo = insere_vertice(grafo, fim);
                imprime_adjacentes(grafo, grafo->tamanho - 1);
            }
            free(menor_caminho);
        }
        else if(op == 'R'){
            fscanf(in_file, "%d %d", &v1, &v2);
            remove_aresta(grafo, v1, v2);
            printf("ARESTA %d -> %d REMOVIDO\n", v1, v2);
        }
    }
    liberar_grafo(grafo);
    return 0;
}