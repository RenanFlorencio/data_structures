#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
 
int f_hash(p_hash hash, int chave){
    /* Método da divisão para o hash */
    return (chave % (hash->tamanho - 1));
}
 
p_hash criar_hash(int n){
    /* Cria o hash inicializando o campo ´vazio´ das structs como  0 */
    p_hash hash;
    hash = malloc(sizeof(struct Hash));
    hash->processos = malloc(n * sizeof(struct Processo));
    hash->tamanho = n;
 
    for (int i = 0; i < hash->tamanho; i++){
        hash->processos[i].status = 0;
    }
    return hash;
}
 
struct Processo le_processo(){
    struct Processo novo;
    char nome[MAX];
    int ID, tempo;
    
    scanf("%d", &ID);
    scanf(" %s", nome);
    scanf("%d", &tempo);
    
    novo.ID = ID;
    strcpy(novo.nome_proc, nome);
    novo.tempo = tempo;
    novo.status = 1;
    return novo;
}
 
void inserir_processo(p_hash hash){
    /* Insere um processo no hash na primeira posição vazia encontrada */
    int chave_hash;
    struct Processo novo;
    novo = le_processo();
 
    chave_hash = f_hash(hash, novo.ID);
 
    for(int i = 0; i < hash->tamanho; i++){
 
        if (hash->processos[chave_hash].status != 1){
            hash->processos[chave_hash] = novo;
            printf("PROCESSO %d INSERIDO!\n", novo.ID);
            break;
        }
        else{
            chave_hash++;
        }
    }
}
 
void consultar_nome(p_hash hash, int ID_buscado){
    /* Verifica se um processo está no hash e devolve o nome. Caso não esteja, devolve um erro */
    int chave_hash;
    chave_hash = f_hash(hash, ID_buscado);
    for(int i = 0; i < hash->tamanho; i++){
 
        if (hash->processos[chave_hash].status == 1){
            if (hash->processos[chave_hash].ID == ID_buscado){
                printf("PROCESSO %d: %s\n", ID_buscado, hash->processos[chave_hash].nome_proc);
                break;
            }
            else{
                chave_hash++;
            }
        }
        else{
            printf("PROCESSO %d NAO ENCONTRADO!\n", ID_buscado);
            break;
        }
    }
}
 
void consultar_tempo(p_hash hash, int id){
    /* Consulta o tempo de um processo no hash */
    int chave, tempo;
    
    chave = f_hash(hash, id);
 
    for (int i = 0; i < hash->tamanho; i++){
        if (hash->processos[chave].ID == id){
            tempo = hash->processos[chave].tempo;
        }
        else{
            chave++;
        }
    }
    printf("TEMPO DO PROCESSO %d: %d DIAS.\n", id, tempo);
}
 
int buscar_processo(p_hash hash, int id){
    /* Busca um processo no hash */
    int chave;
 
    chave = f_hash(hash, id);
    for(int i = 0; i < hash->tamanho; i++){
        if (hash->processos[chave].ID == id){
            return chave;
        }
        else{
            chave++;
        }
    }
    return -1;
}
 
void remover_processo(p_hash hash, int id){
    /* Remove o processo do hash alterando o seu status */
    int chave;
    chave = buscar_processo(hash, id);
    hash->processos[chave].status = -1;
    printf("PROCESSO %d REMOVIDO!\n", id);
}
 
void destroi_hash(p_hash hash){
    // Destroi o hash 
    free(hash->processos);
    free(hash);
}