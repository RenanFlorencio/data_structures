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
 
p_fila criar_fila(int n);
 
p_grafo criar_grafo(int n_c, int n_p);
 
void liberar_grafo(p_grafo grafo);
 
void destruir_fila(p_fila fila);
 
p_no copiar_lista_ligada(p_no original);
 
p_grafo insere_vertice(p_grafo grafo, int vertice);
 
void insere_aresta(p_grafo grafo, int v1, int v2);
 
void remove_aresta(p_grafo grafo, int v1, int v2);
 
int* busca_largura(p_grafo grafo, int vertice);
 
int distancia(int* caminho, int inicio, int fim);
 
void imprime_adjacentes(p_grafo grafo, int vertice);