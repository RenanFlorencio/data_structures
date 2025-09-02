#include <stdio.h>
#include <stdlib.h>
#include "represa.h"
 
void copiar_str(char str1[], char copia[]){
    /* Copia 'str1' para 'str2' */
    int i = 0;
 
    while (str1[i] != '\000'){
        copia[i] = str1[i];
        i++;
    }
    copia[i] = '\000';
}
 
int tamanho_str(char str[]){
    /* Verifica o tamanho de uma string */
 
    int i;
    for(i = 0; str[i] != '\000'; i++);
 
    return i - 1;
}
 
int alerta(represa r){
    /* Retorna 1 caso exista um alerta e 0 caso o alerta não exista */
 
    for(int i = 0; i < r.medidas; i++){
        if(r.niveis[i] / r.capacidade > 0.9){
            return 1;
        }
    }
    return 0;
}
 
void imprime_represa(represa r){
    /* Imprime um relatório da represa e apresenta um alerta quando adequado */
 
    printf("NOME: %s\n", r.nome);
    printf("QTD NIVEIS: %d\n", r.medidas);
    printf("MEDIA: %d\n", r.media);
       
    if (alerta(r) == 1){
        printf("CAPACIDADE ACIMA DE 90%% DA MAXIMA!\n");
    }
 
    printf("#####\n");
}
 
 
int tem_prefixo(char nome[MAX]){
    /* Verifica se um nome tem o prefixo "represa_de_" */
 
    char prefixo[11] = "represa_de_";
    for(int i = 0; i < 11; i++){
        if (nome[i] != prefixo[i]) {
            return 1;
        }
    }
    return 0;
}
 
void remov_pref(char nome[], char *novo_nome, int* tamanho){
    /* Remove o prefixo represa_de_ da string */
 
    int i;
    if (*tamanho > 10){
 
        int check = tem_prefixo(nome);
        if (check == 0){
            for (i = 0; nome[i] != '\000'; i++){
                novo_nome[i] = nome[11 + i];
            }
            *tamanho -= 11;
        }
        else{
           for (i = 0; nome[i] != '\000'; i++){
                novo_nome[i] = nome[i];
            } 
        }    
    }
    else{
        for (i = 0; nome[i] != '\000'; i++){
            novo_nome[i] = nome[i];
        }
    }
}
 
 
void remov_underl(char *novo_nome){
    /* Troca os caracteres "_" de uma string por " " */
 
    int i = 0;
    for (i = 0; novo_nome[i] != '\000'; i++) {
 
        // Trocando underline por espaço
        if (novo_nome[i] == '_') {
            novo_nome[i] = ' ';
        }
        // Usando a tabela ASCII para converter maiusculas para minusculas
        else if (novo_nome[i] >= 65 && novo_nome[i] <= 90) {
            novo_nome[i] = novo_nome[i] + 32;
        }
    }
 
}
 
 
void remov_num(char *novo_nome, int tamanho){
    /* Remove números no fim de uma string */
 
    for (int k = tamanho; k >= 0; k--){
 
        if (novo_nome[k] >= 48 && novo_nome[k] <= 57){
            novo_nome[k] = '\000';
        }
    }
}
 
 
void padronizar(char nome[MAX]){
    /* Padroniza o nome de modo a remover o prefixo "represa_de_", quando houver, passar todos os
    caracteres para minusculas, trocar "_" por " " e remover números no fim do nome */
    char novo_nome[MAX];
    int tamanho;
    tamanho = tamanho_str(nome);
 
    // Removendo prefixo e copiando a string caso não haja prefixo
    remov_pref(nome, novo_nome, &tamanho);
    // Adicionando o final da string
    novo_nome[tamanho + 1] = '\000';
 
    // Removendo underline
    remov_underl(novo_nome);
 
    // Removendo numeros no final da string
    remov_num(novo_nome, tamanho);
 
    // Copiando o novo nome para o nome do objeto
    copiar_str(novo_nome, nome);
}
 
 
void le_medidas(represa r){
    /* Lê as medidas de uma represa e os armazena no objeto */
    int i;
    for(i = 0; i < r.medidas; i++){
        scanf(" %lf", &r.niveis[i]);
    }
}
 
void media_niveis(represa r, int *endereco){
    /* Calcula a média dos níveis de dada represa */
    double soma = 0;
    int media = 0;
 
    for (int i = 0; i < r.medidas; i++){
        soma += r.niveis[i];
    }
    media = soma / r.medidas;
    *endereco = media;
}
 
 
represa nova_represa(){
    /* Cria um novo objeto do tipo represa */
    represa r;
    char nome[MAX];
 
    scanf("%s ", nome);
    r.nome = malloc(MAX * sizeof(char));
    padronizar(nome);
    copiar_str(nome, r.nome);
 
    scanf("%f", &r.capacidade);
    scanf("%d", &r.medidas);
 
    r.niveis = malloc(r.medidas * sizeof(double));
    
    return r;
}