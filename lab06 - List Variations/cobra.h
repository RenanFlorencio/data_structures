typedef struct matriz * p_matriz;
typedef struct no * p_no;
typedef struct fila * p_fila;
 
struct matriz {
    int ** vetor;
    int linhas;
    int colunas;
    int fruta_x;
    int fruta_y;
};
 
struct no {
    int x;
    int y;
    p_no prox;
    p_no ant;
};
 
struct fila{
    p_no cauda;
    p_no cabeca;
};
 
p_matriz criar_matriz();
/* Cria a matriz que mostrará a posição de cada elemento */
 
p_fila criar_fila();
/* Cria uma fila que representará a cobra, com uma cauda e uma cabeça */
 
void aumentar_cobra(p_fila cobra, p_matriz matriz, int x, int y);
/* Aumenta o tamanho da cobra criando um nó cabeça na posição dada */
 
int mover(p_fila cobra, p_matriz matriz, char move);
/* Move a posição da cobra. 
Enquanto isso, também verifica se o jogo foi ganho (retorna 2), foi perdido
(retorna 1) ou se deve continuar (retorna 0). 
Também verifica se uma maçã foi comida a aumenta automaticamente a cobra
*/
 
void ler_fruta(p_matriz matriz);
/* Lê as posições de uma fruta e a coloca na matriz */
 
void imprimir_matriz_f(p_matriz matriz);
/* Imprime a matriz formatada corretamente para o jogo */
 
void apagar_nos(p_no no);
/* Desaloca todos os nós da cobra */
 
void apagar_matriz(p_matriz matriz);
/* Desaloca a matriz */