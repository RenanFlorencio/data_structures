#include <stdio.h>
 
void le_vetor (int vetor[], int n){
    // Lê um vetor de tamanho n
    for (int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }
}
 
 
void imprimir (int vetor[], int n){
    //Imprime um vetor de tamanho n
    for (int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}
 
 
void conjunto_banner(int vetor[], int n, int banner[], int B){
    // Realiza a intersecção do vetor dado com o conjunto banner
    // Valores fora da intersecção recebem o valor 0
    int check;
 
    for (int i = 0; i < n; i++){
        check = 0;
        for (int j = 0; j < B; j++){
            if (vetor[i] == banner[j]){
                check = 1;
            }
        }
        if (check == 0){
            vetor[i] = 0;
        }
    }
}
 
 
void multiplicar(int vetor[], int n, int M){
    //Multiplica o vetor por um escalar M
    for (int i = 1; i < n; i += 2){
        vetor[i] *= M;
    }
}
 
 
void ciclico(int vetor[], int n, int P){
    // Realiza um movimento cíclico P vezes no vetor fornecido
    int aux;
 
    for (int i = 0; i < P; i++){
        aux = vetor[n - 1];
 
        for (int j = 0; j < n -+ 1; j++){
            vetor[n - j - 1] = vetor[n - j - 2];
        }
        vetor[0] = aux;
    }
 
}
 
 
void inverter(int vetor[], int n){
    // Inverte um dado vetor
    int i = 0, j = n - 1, aux;
    while(i < n/2){
        aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
        i++;
        j--;
    }    
 
}
 
 
int main(){
    int len_vetor, vetor[1000], n_operacoes, operacao;
    int B, banner[1000], M, P;
 
    scanf("%d", &len_vetor);
    le_vetor(vetor, len_vetor);
    scanf("%d", &n_operacoes);
 
    for (int i = 0; i < n_operacoes; i++){
        scanf("%d", &operacao);
        
        if (operacao == 1){
            scanf("%d", &B);
            le_vetor(banner, B);
            
            conjunto_banner(vetor, len_vetor, banner, B);
        }
 
        else if (operacao == 2){
            scanf("%d", &M);
 
            multiplicar(vetor, len_vetor, M);
        }
 
        else if (operacao == 3){
            scanf("%d", &P);
 
            ciclico(vetor, len_vetor, P);
        }
 
        else{
            inverter(vetor, len_vetor);
        }
 
        imprimir(vetor, len_vetor);
    }
    return 0;
}