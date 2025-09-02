#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
 
int main(){
    char op;
    int n_c, n_p, n_arestas, n_op, v1, v2;
    int dist, dist_min, inicio, fim;
    int* menor_caminho;
    p_grafo grafo;
 
    scanf("%d %d", &n_c, &n_p);
    grafo = criar_grafo(n_c, n_p);
    grafo->n_c = 10;
 
    scanf("%d", &n_arestas);
    for(int i = 0; i < n_arestas; i++){
        scanf("%d %d", &v1, &v2);
        insere_aresta(grafo, v1, v2);
    }
    printf("GRAFO AMZ CONSTRUIDO!\n");
 
    scanf("%d", &n_op);
    for(int i = 0; i < n_op; i++){
 
        scanf(" %c ", &op);
 
        if(op == 'D'){
            scanf("%d %d %d", &inicio, &fim, &dist_min);
            menor_caminho = busca_largura(grafo, inicio);
            dist = distancia(menor_caminho, inicio, fim);
            free(menor_caminho);
 
            printf("DISTANCIA %d -> %d = %d\n", inicio, fim, dist);
            if (dist > dist_min){
                grafo = insere_vertice(grafo, fim);
                imprime_adjacentes(grafo, grafo->tamanho - 1);
            }
        }
        else if(op == 'R'){
            scanf("%d %d", &v1, &v2);
            remove_aresta(grafo, v1, v2);
            printf("ARESTA %d -> %d REMOVIDO\n", v1, v2);
        }
    }
    liberar_grafo(grafo);
    return 0;
}
