typedef struct fila * p_fila;

struct fila{
    char *vetor;
    int inicio, fim, tamanho, usado;
};

p_fila criar_fila();
/* Cria uma fila vazia */

void enfileirar(p_fila fila, char linha[], int tamanho);
/* Enfileira uma linha */

char desenfileirar(p_fila fila, int qntd);
/* Desenfileira um caractere */

void imprime_fila(p_fila fila);
/* Imprime a fila */

void liberar_fila(p_fila fila);
/* Desaloca a fila */