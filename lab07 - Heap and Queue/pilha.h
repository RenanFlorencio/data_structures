typedef struct no * p_no;
typedef struct pilha * p_pilha;
 
struct pilha{
    p_no topo;
};
 
struct no{
    char string[50];
    p_no prox;
    int str_usado;
};
 
p_pilha criar_pilha();
/* Cria uma pilha de nós */
 
p_no criar_no();
/* Cria um nó */
 
void empilhar(p_pilha pilha, char c);
/* Empilha um caractere colocando-o dentro do nó no topo da pilha */
 
void desempilhar(p_pilha pilha, int qntd);
/* Desempilha um caractere, removendo-o da lista no topo da pilha */
 
void imprime_pilha(p_no topo);
/* Imprime a pilha de baixo para cima */
 
void liberar_pilha(p_pilha pilha);
/* Libera a pilha */