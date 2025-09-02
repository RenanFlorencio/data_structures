#include <stdio.h>
#include <stdlib.h>
 
typedef struct elite* p_elite; // Ponteiro para a struct elite
 
struct elite {
    int *sub_tropas;
    int n;
    int alocado;
};
 
p_elite criar_elite(int tamanho){
    /* Cria um ponteiro para a struct elite */
    p_elite p;
    p = malloc(sizeof(struct elite));
    p -> sub_tropas = malloc(tamanho * sizeof(int));
    p -> n = 0;
    p -> alocado = tamanho;
 
    return p;
}
 
void adicionar_subtropa(p_elite elite, int* subtropa, int tam_subtropa){
    /* Adiciona uma subtropa ao vetor de subtropas de elite */
 
    // Verificando se o tamanho do vetor é suficiente
    int *aux;
    if ((elite -> n) + tam_subtropa >= elite -> alocado){
 
        aux = elite -> sub_tropas;
        elite -> sub_tropas = malloc(2 *(elite -> n + tam_subtropa) * sizeof(int));
        elite -> alocado = (elite -> n + tam_subtropa) * 2;
        
        for (int i = 0; i < elite -> n; i++){
            elite -> sub_tropas[i] = aux[i]; 
        }
 
        free(aux);
    }
    // Adicionando a subtropa
    for(int i = 0; i < tam_subtropa; i++){
        elite -> sub_tropas[elite -> n + i] = subtropa[i];
    }
 
    elite -> n += tam_subtropa;
}
 
void imprime_elite(p_elite elite){
    for(int i = 0; i < elite -> n; i++){
        printf("%d ", elite -> sub_tropas[i]);
    }
    printf("\n");
}
 
 
void le_tropas(int *vetor, int n){
 
    for (int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }
    
}
 
void imprime_vetor(int *vetor, int n){
 
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}
 
 
int* subtropa_forte(int *vetor, int n, int* sub_forte, int* tam_sub){
    /* Recebe um vetor, retorna um endereço para o vetor conjunto com maior soma dentro dele e qual seu tamanho */
 
    int intervalo[2], i, soma;
    int soma_maior = 0;
    for (i = 0; i < n; i++){
        soma_maior += vetor[i];
    }
    intervalo[0] = 0;
    intervalo[1] = n - 1;
 
    // Verificando o conjunto de soldados com maior experiência
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            soma = 0;
            for(int k = i; k <= j; k++){
                soma += vetor[k];
            }
            if (soma > soma_maior){
                soma_maior = soma;
                intervalo[0] = i;
                intervalo[1] = j;
            }
        }
    }
    sub_forte = malloc((intervalo[1] - intervalo[0] + 1) * sizeof(int));
    
    // Adicionando os soldados ao vetor
    for (int j = 0; j < intervalo[1] - intervalo[0] + 1; j++){
        sub_forte[j] = vetor[j + intervalo[0]];
    }
 
    *tam_sub = intervalo[1] - intervalo[0] + 1;
    imprime_vetor(sub_forte, intervalo[1] - intervalo[0] + 1);
 
    return sub_forte;
}
 
void elite_forte(int *vetor, int n, int* elite_forte, int media){
    /* Recebe um vetor, retorna um endereço para o vetor conjunto com maior soma dentro dele */
 
    int intervalo[2], i, soma;
    int soma_maior = 0;
    for (i = 0; i < n; i++){
        soma_maior += vetor[i];
    }
    intervalo[0] = 0;
    intervalo[1] = n - 1;
 
    // Verificando o conjunto de soldados com maior experiência
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            soma = 0;
            for(int k = i; k <= j; k++){
                soma += vetor[k];
            }
            if (soma > soma_maior){
                soma_maior = soma;
                intervalo[0] = i;
                intervalo[1] = j;
            }
        }
    }
    elite_forte = malloc((intervalo[1] - intervalo[0] + 1) * sizeof(int));
    
    // Adicionando os soldados ao vetor
    for (int j = 0; j < intervalo[1] - intervalo[0] + 1; j++){
        elite_forte[j] = vetor[j + intervalo[0]] + media;
    }
 
    imprime_vetor(elite_forte, intervalo[1] - intervalo[0] + 1);
    free(elite_forte);
}
 
int normalizar(p_elite elite){
    /* Normaliza o vetor de uma struct usando sua média */
 
    // Obtendo a média
    int soma = 0, media = 0;
    for(int i = 0; i < elite -> n; i++){
        soma += elite -> sub_tropas[i];
    }
    media = soma / elite -> n;
 
    // Normalizando e procurando o maior valor
    for(int i = 0; i < elite -> n; i++){
        elite -> sub_tropas[i] -= media;
    }
    return media;
}
 
 
int main(){
 
    int qtd_tropas, tam_tropa, tam_sub, media;
    int* sub_forte;
    int* sub_elite;
    int** tropas;
    p_elite elite;
 
    // Inicializando os vetores
    scanf("%d", &qtd_tropas);
    tropas = malloc(qtd_tropas * sizeof(int*));    
    
    // Criando um vetor do tipo elite
    elite = criar_elite(1);
 
    for (int i = 0; i < qtd_tropas; i++){
 
        // Alocando a tropa lida
        scanf("%d", &tam_tropa);
        tropas[i] = malloc(tam_tropa * sizeof(int));
 
        // Lendo as tropas
        le_tropas(tropas[i], tam_tropa);
 
        // Verificando a Sub-tropa forte e devolvendo seu vetor
        printf("Sub-tropa Forte %d: ", i + 1);
        tam_sub = 0;
        sub_forte = subtropa_forte(tropas[i], tam_tropa, sub_forte, &tam_sub);
        adicionar_subtropa(elite, sub_forte, tam_sub);
 
        free(sub_forte);
    }
    // Inicializando o ponteiro para um local qualquer
    sub_elite = elite -> sub_tropas;
 
    media = normalizar(elite);
    printf("Sub-tropa Elite: ");
    elite_forte(elite -> sub_tropas, elite -> n, sub_elite, media);
 
    // Liberando os ponteiros
    free(elite -> sub_tropas);
    free(elite);
    for(int i = 0; i < qtd_tropas; i++){
        free(tropas[i]);
    }
    free(tropas);
 
    return 0;
}