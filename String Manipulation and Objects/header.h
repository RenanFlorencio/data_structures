#define MAX 100

typedef struct  
{
    char *nome;
    float capacidade;
    int medidas;
    int media;
    double *niveis;
} represa;

represa nova_represa();
/* Cria uma objeto do tipo represa, aloca os vetores de nome e de níveis e obtém os valores
    medidas e capacidade. Ao criar uma nova represa, o nome é padronizado */

void imprime_represa(represa r);
/* Imprime o nome, a quantidade de níveis, a média dos níveis e um alerta, caso algum dos níveis esteja
    acima de 90% da capacidade da represa */

void le_medidas(represa r);
/* Lê as medidas de níveis de uma represa */

void media_niveis(represa r, int* media);
/* Calcula a média dos níveis de uma represa e os armazena no endereço da variável média da represa */

int alerta(represa r);