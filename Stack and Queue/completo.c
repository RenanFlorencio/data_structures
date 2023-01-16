#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no * p_no;
typedef struct pilha * p_pilha;
typedef struct fila * p_fila;

struct no{
    char string[50];
    p_no prox;
    int str_usado;
};

struct pilha{
    p_no topo;
};

struct fila{
    char *vetor;
    int inicio, fim, tamanho, usado;
};

p_fila criar_fila(){
    /* Cria uma fila de tamanho 500 e retorna o ponteiro */
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila -> vetor = malloc(500 * sizeof (char));
    fila -> inicio = 0;
    fila -> fim = 0;
    fila -> tamanho = 500;
    fila -> usado = 0;
    return fila;
}

p_pilha criar_pilha(){
    /* Cria uma pilha vazia */
    p_pilha pilha;
    pilha = malloc(sizeof(struct pilha));
    pilha -> topo = NULL;
    return pilha;
}

p_no criar_no(){
    p_no no;
    no = malloc(sizeof(struct no));
    no -> str_usado = 0;
    no -> prox = NULL;
    return no;
}

void empilhar(p_pilha pilha, char c){
    /* Empilha o caracter tomando cuidado para verificar se a pilha é vazia ou se seu topo está cheio*/
    if (pilha -> topo == NULL){
        p_no novo;
        novo = criar_no();
        novo -> str_usado = 0;
        novo -> prox = NULL;
        pilha -> topo = novo;
    }
    else if (pilha -> topo -> str_usado == 49){
        p_no novo;
        pilha->topo->string[49] = '\000';
        novo = criar_no();
        novo -> str_usado = 0;
        novo -> prox = pilha -> topo;
        pilha -> topo = novo;
    }
    pilha->topo->string [pilha->topo->str_usado] = c;
    pilha->topo->str_usado++;
}

void desempilhar(p_pilha pilha, int qntd){
    /* Desempilha "qntd" caracteres */
    p_no aux;
    int contador = 0;
    int atual = pilha->topo->str_usado;
    for(int i = 0; i < qntd; i++){
        if(pilha->topo->str_usado > 1){
            pilha->topo->string[atual - 2 - contador] = '\000';
            pilha->topo->str_usado--;
            contador++;
        }
        else{
            // Se não tiver mais nenhum caractere, basta liberar a memória e passar a
            // desempilhar o próximo da pilha
            aux = pilha->topo;
            pilha->topo = pilha->topo->prox;
            free(aux);
            atual = 50;
            pilha->topo->string[atual - 2] = '\000';
            contador = 1;
        }
    }   
}

void enfileirar(p_fila fila, char linha[], int tamanho){
    /* Infileira a linha */
    for (int i = 0; i < tamanho; i++){
        fila -> vetor[fila -> fim] = linha[i];
        fila -> fim = (fila -> fim + 1) % fila -> tamanho; 
        fila -> usado ++;
    }
}

char desenfileirar(p_fila fila, int qntd){
    /* Desinfileira o primeiro caractere da fila */
    char c;
    c = fila -> vetor[fila -> inicio];
    fila -> inicio = (fila -> inicio + 1) % fila -> tamanho;
    fila -> usado --;
    return c;
}

void imprime_fila(p_fila fila){
    /* Imprime a fila */
    printf("FILA ATUAL: ");
    for(int i = fila->inicio; i < fila->fim; i++){
        printf("%c", fila -> vetor[i]);
    }
    printf("\n");
}

void imprime_recursivo(p_no topo){
    if (topo == NULL){
    }
    else{
        imprime_recursivo(topo->prox);
        printf("%s", topo->string);
    }
}

void imprime_pilha(p_no topo){
    /* Imprimir recursivamente, primeiro o final */
    printf("PILHA ATUAL: ");
    imprime_recursivo(topo);
    printf("\n####\n");
}

void consolidar(p_pilha pilha, p_fila fila, int qntd){
    /* Passa os "qntd" caracteres da fila para a pilha */
    char c;
    if(pilha->topo != NULL){
        // Desconsiderando o ○ \000
        pilha->topo->str_usado--;
    }
    for (int i = 0; i < qntd; i++){
        c = desenfileirar(fila, qntd);
        empilhar(pilha, c);
    }
    empilhar(pilha, '\000');
}

int verif_comando(char comando[]){
    /* Verifica se a linha é um comando, caso não seja, retorna 0
    Caso seja, retorna 1 para Executar; 2 para Deletar e 3 para Sair
    A linha enviada é alterada para caso seja um comando somente fique nela o valor */
    int i;
    char aux[5];
    for(i = 0; comando[i] != ' ' && comando[i] != '\n' && i < 5; i++){
        aux[i] = comando[i];
    }
    int comeco = i + 1;
    aux[i] = '\000';
    if (strcmp(aux, "EXEC") == 0){
        i = 0;
        // Obtendo o número de linhas a serem passadas para a pilha
        for(i = comeco; comando[i] != '\n'; i++){
            comando[i - comeco] = comando[i];
        }
        comando[i - comeco] = '\000';
        return 1;
    }
    else if (strcmp(aux, "DEL") == 0){
        i = 0;
        // Obtendo o número de linhas a serem deletadas
        for(i = comeco; comando[i] != '\n'; i++){
            comando[i - comeco] = comando[i];
        }
        comando[i - comeco] = '\000';
        return 2;
    }
    else if (strcmp(aux, "EXIT") == 0){
        return 3;
    }
    return 0;
}

void liberar_fila(p_fila fila){
    free(fila->vetor);
    free(fila);
}

void libera_recursiv(p_no no){
    if (no == NULL){
    }
    else{
        libera_recursiv(no->prox);
        free(no);
    }
}

void liberar_pilha(p_pilha pilha){
    libera_recursiv(pilha->topo);
    free(pilha);
}

int main(){
    int tamanho, qntd, comando;
    FILE *in_file = fopen("C:/Users/renae/Documents/Estrutura_de_Dados/lab07/t04_in.txt", "r");
    p_fila fila;
    p_pilha pilha;
    fila = criar_fila();
    pilha = criar_pilha();
    comando = 0;

    char linha[550];
    while(comando != 3){

        fgets(linha, 550, in_file);
        comando = verif_comando(linha);
        if(comando == 1){
            // Convertendo a string para int
            qntd = atoi(linha);
            // Enviando da fila para a pilha
            consolidar(pilha, fila, qntd);
        }
        else if(comando == 2){
            // Removendo do topo da pilha
            qntd = atoi(linha);
            desempilhar(pilha, qntd);
        }
        else if(comando == 3){
            // Termina o programa
            break;
        }
        else{
            tamanho = strlen(linha) - 1;
            enfileirar(fila, linha, tamanho);
        }
        imprime_fila(fila);
        imprime_pilha(pilha->topo);
    }
    liberar_fila(fila);
    liberar_pilha(pilha);
    return 0;
}