# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "header.h"

void ordenar_linha(int* vetor, int n){
    /* Ordenando a linha com insertion sort */
    int aux, i, j;
    for(i = 1; i < n; i++){
        aux = vetor[i];
        j = i;
        
        while(j > 0 && vetor[j - 1] > aux){
            vetor[j] = vetor[j - 1];
            j --;
        }
        vetor[j] = aux;
    }
}

p_matriz criar_matriz(int m, int n){
    /* Aloca e lê uma matriz de m por n */
    p_matriz p;
    
    p = malloc(sizeof(struct matriz));
    p -> linhas = m;
    p -> colunas = n;
    p -> vetor = malloc (m * sizeof(int *));
    for (int i = 0; i < m; i++){
        p -> vetor[i] = malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++){
            scanf("%d", &p -> vetor[i][j]);
        }
    }
    p -> linhas_aloc = m;
    p -> colunas_aloc = n;

    return p;
}

void apagar_matriz(p_matriz p){
    /* Desaloca todos os vetores de uma matriz*/
    for(int i = 0; i < p->linhas; i++){
        free(p->vetor[i]);
    }
    free(p -> vetor);
}

void apagar_vetor(int ** vetor, int n){
    /* Desaloca um vetor de vetores */
    for(int i = 0; i < n; i++){
        free(vetor[i]);
    }
    free(vetor);
}

void imprime_matriz(p_matriz p){
    /* Imprime a matriz formatada */
    for(int i = 0; i < p -> linhas; i++){
        for(int j = 0; j < p -> colunas; j++){
            printf("%d ", p -> vetor[i][j]);
        }
        printf("\n");
    }
    printf("###\n");
}

void copiar_matriz(int** velha, int** novo, int m, int n){
    /* Copia um vetor de vetores para outro */
    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            novo[i][j] = velha[i][j];
        }
    }
}

void inserir_linha(p_matriz matriz){
    /* Insere uma nova linha à matriz realocando dinamicamente o vetor */

    //Verificando se o vetor está cheio
    if(matriz -> linhas + 1 > matriz -> linhas_aloc){
        int** temp;
        temp = matriz -> vetor;
        
        // Alocando o dobro do espaço de linhas atual
        matriz -> linhas_aloc *= 2;
        matriz -> vetor = malloc(matriz->linhas_aloc * sizeof(int *));
        for (int i = 0; i < matriz -> linhas_aloc; i++){
            matriz -> vetor[i] = malloc(matriz->colunas_aloc * sizeof(int));
        }
        for(int i = 0; i < matriz->linhas; i++){
            matriz -> vetor[i] = temp[i];
        }
        // Copiando o vetor e liberando a memória (arrumar isso pra copiar só a linha inserida)
        copiar_matriz(temp, matriz -> vetor, matriz -> linhas, matriz -> colunas);
        apagar_vetor(temp, matriz -> linhas);
    }
    
    //Lendo a nova linha
    matriz->linhas ++;

    for (int i = 0; i < matriz -> colunas; i++){
        scanf("%d", &(matriz->vetor[matriz->linhas - 1][i]));
    }
    ordenar_linha(matriz -> vetor[matriz -> linhas - 1], matriz -> colunas);
}

void remover_linha(p_matriz matriz, int i){
    /* Remove uma linha da matriz alterando os ponteiros */
    // Modificando os ponteiros que estão depois do índice removido
    int* aux;
    aux = matriz -> vetor[i];
    for(; i < matriz -> linhas - 1; i++){
        matriz -> vetor[i] = matriz -> vetor[i + 1];
    }
    matriz -> vetor[matriz -> linhas - 1] = aux;
    
    matriz -> linhas --;
    // Verificando se o novo tamanho é de 1/4 do alocado
    if (matriz -> linhas <= (matriz -> linhas_aloc)/ 4){
        int** temp;
        temp = matriz -> vetor;

        matriz -> linhas_aloc /= 2;
        matriz -> vetor = malloc(matriz -> linhas_aloc * sizeof(int *));
        for(int i = 0; i < matriz -> linhas_aloc; i++){
            matriz -> vetor[i] = malloc(matriz -> colunas_aloc * sizeof(int));
        }
        copiar_matriz(temp, matriz -> vetor, matriz -> linhas, matriz -> colunas);
        apagar_vetor(temp, matriz -> linhas);
    }
}

void inserir_coluna(p_matriz matriz){
    /* Insere uma nova linha à matriz realocando dinamicamente o vetor */

    // Verificando se o vetor está cheio
    if(matriz -> colunas + 1 > matriz -> colunas_aloc){
        int* temp;
        
        // Alocando o dobro do espaço de linhas atual
        matriz -> colunas_aloc *= 2;
        for (int i = 0; i < matriz -> linhas_aloc; i++){
            temp = matriz -> vetor[i];
            matriz -> vetor[i] = malloc(matriz -> colunas_aloc * sizeof(int));
            // Copiando as colunas
            for (int j = 0; j < matriz -> colunas; j++){
                matriz -> vetor[i][j] = temp[j];
            }
            free(temp);
        }
    }
    matriz->colunas ++;
    // Lendo a nova coluna
    for (int i = 0; i < matriz -> linhas; i++){
        scanf("%d", &(matriz -> vetor[i][matriz -> colunas - 1]));
        ordenar_linha(matriz -> vetor[i], matriz -> colunas);
    }
}

void remover_coluna(p_matriz matriz, int j){
    /* Remove a coluna de índice j da matriz */

    matriz -> colunas --;
    for(int i = 0; i < matriz -> linhas; i++){
        int indice;
        for(indice = j; indice < matriz -> colunas; indice++){
            matriz -> vetor[i][indice] = matriz -> vetor[i][indice + 1];
        }
    }

    // Verificando se o novo tamanho é de 1/4 do alocado
    if(matriz -> colunas <= (matriz -> colunas_aloc) / 4){
        int *temp;
        matriz -> colunas_aloc /= 2;

        for(int i = 0; i < matriz -> linhas_aloc; i++){
            temp = matriz -> vetor[i];
            matriz -> vetor[i] = malloc(matriz -> colunas_aloc * sizeof(int));
            // Copiando colunas
            for (int j = 0; j < matriz -> colunas; j++){
                matriz -> vetor[i][j] = temp[j];
            }
            free(temp);
        }
    }
}
