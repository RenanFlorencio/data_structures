#define MAX 1000
 
struct Processo{
    int ID;
    char nome_proc[MAX];
    int tempo;
    int status; // 0 para vazio; 1 para ocupado; -1 para removido
};
 
struct Hash{
    struct Processo* processos;
    int tamanho;
};
 
typedef struct Hash* p_hash;
 
p_hash criar_hash(int n);
 
void inserir_processo(p_hash hash);
// Insere um processo no hash
 
void consultar_nome(p_hash hash, int ID_buscado);
// Consulta o nome vinculado ao ID no hash
 
void consultar_tempo(p_hash hash, int id);
// Consulta o tempo do processo vinculado ao ID no hash
 
void remover_processo(p_hash hash, int id);
// Remove o processo de um dado ID no hash
 
void destroi_hash(p_hash);
// Desaloca o hash