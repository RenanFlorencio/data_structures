#define MAX 100
 
typedef struct mapa * p_mapa;
typedef struct visitas * p_visitas;
 
struct mapa {
    char nome[MAX];
    int qtd_visitas;
    p_mapa esq;
    p_mapa dir;
};
 
struct visitas {
    int data;
    char nome[MAX];
    int pista;
    p_visitas esq;
    p_visitas dir;
};
 
p_mapa criar_mapa();
/* Cria uma struct mapa vazia */
 
p_visitas criar_visitas();
/* Cria uma struct visitas vazia */
 
p_mapa buscar_mapa(p_mapa raiz, char chave[]);
/* Busca por uma cidade (chave) no mapa */
 
p_visitas buscar_visitas(p_visitas raiz, int data);
/* Busca por uma visita (data) no mapa */
 
p_mapa inserir_mapa (p_mapa raiz, char nome[]);
/* Insere uma cidade no mapa, mantendo-o ordenado por nome de cidade */
 
p_visitas inserir_visita(p_visitas raiz, int data, char nome[], int pista);
/* Insere uma visita nas visitas, mantendo-a ordenada por data */
 
p_mapa remover_cidade(p_mapa raiz, char cidade[]);
/* Remove uma cidade do mapa */
 
p_visitas exclui_visita (p_visitas raiz, int data);
/* Remove uma visita das visitas */
 
p_mapa liberar_mapa(p_mapa raiz);
/* Desaloca todos os nós do mapa */
 
p_visitas liberar_visitas(p_visitas raiz);
/* Desaloca todos os nós das visitas */
 
void relatorio_mapa(char nome[]);
/* Produz um relatório com o nome da cidade e a árvore onde foi inserido */
 
void relatorio_visitas(int data, char nome[]);
/* Produz um relatório com a data da visita e o nome da cidade visitada */
 
void relatorio_datas(p_visitas raiz, int inicio, int fim);
/* Exibe todas as datas de visitas e o nome das cidades da data de inicio à data final */
 
void relatorio_pistas(p_visitas raiz, int inicio, int fim);
/* Exibe todas as pistas encontradas e nome das cidades da data de inicio à data final */
 
void relatorio_cidade(p_mapa cidade);
/* Exibe a cidade em questão e a quantidade de visitas feitas a ela */
 