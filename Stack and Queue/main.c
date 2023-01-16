#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackHeader.h"
#include "queueHeader.h"

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

int main(){
    int tamanho, qntd, comando;
    p_fila fila;
    p_pilha pilha;
    fila = criar_fila();
    pilha = criar_pilha();
    comando = 0;

    char linha[550];
    while(comando != 3){

        fgets(linha, 550, stdin);
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