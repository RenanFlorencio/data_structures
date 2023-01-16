#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Arquivo novo_arquivo(int codigo, int id){
    /* Cria um objeto do tipo arquivo */
    Arquivo arq;
    arq.id = id;
    arq.codigo = codigo;
    return arq;
}

p_fp cria_fila(int tamanho){
    /* Cria uma fila */
    p_fp fila;
    fila = malloc(sizeof(FP));
    fila->n = 0;
    fila->alocado = tamanho;
    fila->vetor = malloc(tamanho * sizeof(Arquivo));
    return fila;
}

void troca_v(Arquivo* arq1, Arquivo* arq2){
    /* Troca os valores de dois vetores */
    int aux;
    aux = arq1->id;
    arq1->id = arq2->id;
    arq2->id = aux;

    aux = arq1->codigo;
    arq1->codigo = arq2->codigo;
    arq2->codigo = aux;
}

void sobe_fila(p_fp fila, int i){
    /* Corrige o heap trocando os vetores de posião subindo no heap */

    if(i > 0){
        if(fila->vetor[PAI(i)].codigo > fila->vetor[i].codigo){
        troca_v(&fila->vetor[PAI(i)], &fila->vetor[i]);
        sobe_fila(fila, PAI(i));
        }
        // Caso tenham mesmo código, verificando o número do processo
        else if(fila->vetor[PAI(i)].codigo == fila->vetor[i].codigo){
            if(fila->vetor[PAI(i)].id < fila->vetor[i].id){
                troca_v(&fila->vetor[PAI(i)], &fila->vetor[i]);
                sobe_fila(fila, PAI(i));
            }
        }
    }
}

void desce_fila(p_fp fila, int i){
    /* Corrige o heap trocando os vetores de posição descendo no heap */
    int maior_filho;

    // Verificando qual é o maior filho
    if(F_ESQ(i) < fila->n){ // Verificando se está dentro da lista
        maior_filho = F_ESQ(i);

        if(F_DIR(i) < fila->n){

            if(fila->vetor[F_ESQ(i)].codigo > fila->vetor[F_DIR(i)].codigo){
                maior_filho = F_DIR(i);
            }
            else if(fila->vetor[F_ESQ(i)].codigo == fila->vetor[F_DIR(i)].codigo){
                
                if(fila->vetor[F_DIR(i)].id > fila->vetor[F_ESQ(i)].id){
                    maior_filho = F_DIR(i);
                }
            }
        }
        // Corrigindo o heap
        if (fila->vetor[i].codigo > fila->vetor[maior_filho].codigo){
            troca_v(&fila->vetor[i], &fila->vetor[maior_filho]);
            desce_fila(fila, maior_filho);
        }
        else if(fila->vetor[i].codigo == fila->vetor[maior_filho].codigo){
            if (fila->vetor[i].id < fila->vetor[maior_filho].id){
                troca_v(&fila->vetor[i], &fila->vetor[maior_filho]);
                desce_fila(fila, maior_filho);
            }
        }
    }
}

int buscar_processo(p_fp fila, int id){
    /* Retorna o índice do processo buscado no heap */ 
    for(int i = 0; i < fila->n; i++){
        if (fila->vetor[i].id == id){
            return i;
        }
    }
    return 1;
}

void mudar_prio(p_fp fila, int codigo, int id){
    /* Muda a prioridade de um processo */
    int indice;
    indice = buscar_processo(fila, id);

    if(fila->vetor[indice].codigo > codigo){
        fila->vetor[indice].codigo = codigo;
        sobe_fila(fila, indice);
    }
    else{
        fila->vetor[indice].codigo = codigo;
        desce_fila(fila, indice);
    }
}

Arquivo maior_arq(p_fp fila){
    /* Remove o arquivo de maior prioridade */
    Arquivo arq;

    arq = fila->vetor[0];
    troca_v(&fila->vetor[0], &fila->vetor[fila->n - 1]);
    fila->n--;
    desce_fila(fila, 0);
    return arq;
}

void insere_arq(p_fp fila, Arquivo arq){
    /* Insere um arquivo no heap */
    fila->vetor[fila->n] = arq;
    fila->n++;
    sobe_fila(fila, fila->n - 1);
}

void inserir_fila(p_fp fila){
    /* Cria um novo arquivo e o insere na fila de prioridade */ 
    Arquivo arquivo;
    int id, codigo;
    scanf("%d %d", &id, &codigo);
    arquivo = novo_arquivo(codigo, id);
    insere_arq(fila, arquivo);
}

void remover_processos(p_fp fila, int qtd_processos){
    /* Remove x processos do heap em ordem de prioridade */
    Arquivo prioridade;
    printf("PROCESSOS REMOVIDOS: ");
    int i;
    for(i = 0; i < qtd_processos - 1; i++){
        prioridade = maior_arq(fila);
        printf("%d ", prioridade.id);
    }
    prioridade = maior_arq(fila);
    printf("%d", prioridade.id);
    printf("\n");
}

void destroi_fila(p_fp fila){
    /* Desaloca o heap */
    free(fila->vetor);
    free(fila);
}