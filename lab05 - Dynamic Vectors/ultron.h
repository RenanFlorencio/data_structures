typedef struct matriz * p_matriz;
 
struct matriz {
    int** vetor;
    int linhas;
    int colunas;
    int linhas_aloc;
    int colunas_aloc;
};
 
p_matriz criar_matriz(int m, int n);
/* Cria uma scruct do tipo matriz com as linhas ordenadas */
 
void imprime_matriz(p_matriz p);
/* Imprime uma matriz formatada */
 
void inserir_linha(p_matriz matriz);
/* Insere uma linha ordenada à matriz */
 
void remover_linha(p_matriz matriz, int i);
/* Remove uma linha da matriz */
 
void inserir_coluna(p_matriz matriz);
/* Insere uma coluna à matriz e reordena as linhas */
 
void remover_coluna(p_matriz matriz, int j);
/* Remove uma coluna da matriz */
 
void apagar_matriz(p_matriz p);
/* Apaga todos os vetores de uma matriz */
 