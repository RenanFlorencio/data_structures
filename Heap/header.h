#define PAI(i) ((i - 1) / 2) 
#define F_ESQ(i) (i * 2 + 1)
#define F_DIR(i) (i * 2 + 2)

typedef struct {
    int id;
    int codigo;
} Arquivo;

typedef struct {
    Arquivo *vetor;
    int n;
    int alocado;
} FP;

typedef FP * p_fp;

Arquivo novo_arquivo(int codigo, int id);
/* Cria um objeto do tipo arquivo */

p_fp cria_fila(int tamanho);
/* Cria uma fila */

void troca_v(Arquivo* arq1, Arquivo* arq2);
/* Troca os valores de dois vetores */

void sobe_fila(p_fp fila, int i);
/* Corrige o heap trocando os vetores de posião subindo no heap */

void desce_fila(p_fp fila, int i);
/* Corrige o heap trocando os vetores de posição descendo no heap */

int buscar_processo(p_fp fila, int id);
/* Retorna o índice do processo buscado no heap */ 

void mudar_prio(p_fp fila, int codigo, int id);
/* Muda a prioridade de um processo */

Arquivo maior_arq(p_fp fila);
/* Remove o arquivo de maior prioridade */

void insere_arq(p_fp fila, Arquivo arq);
/* Insere um arquivo no heap */

void inserir_fila(p_fp fila);
/* Cria um novo arquivo e o insere na fila de prioridade */ 

void remover_processos(p_fp fila, int qtd_processos);
/* Remove x processos do heap em ordem de prioridade */

void destroi_fila(p_fp fila);
/* Desaloca o heap */