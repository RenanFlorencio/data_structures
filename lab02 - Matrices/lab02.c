#include <stdio.h>
#define MAX 100
 
void copiar(int matriz[][MAX], int copia[][MAX], int n){
    /* Copia 'matriz' para 'copia' */
 
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            copia[i][j] = matriz[i][j];
        }
    }
}
 
void limpar(int matriz[][MAX], int n){
    /* Transforma todas as posições da matriz em 0*/
 
    for (int i = 0; i < n; i ++){
        for(int j = 0; j < n; j++){
            matriz[i][j] = 0;
        }
    }
}
 
 
void matriz_listrada(int vetor[][MAX],int n){
    /* Cria uma matriz com listras de dada espessura */
    int cor = 1, espessura = 3;
    int i, j;
 
    for(i = 0; i < n; i++){
 
        for(j = 0; j < n; j++){
 
            if (j != 0 && j % espessura == 0){
 
                if (cor == 1){
                    cor = 0;
                }
 
                else{
                    cor = 1;
                }
            }
            vetor[i][j] = cor;
        }
    }
}
 
 
void transpor(int matriz[][MAX], int saida[][MAX], int n){
    /* Tranpõe uma matriz */
 
    int transp[MAX][MAX];
    copiar(matriz, transp, n);
 
    for(int i = 0; i < n; i++){
 
        for(int j = 0; j < n; j++){
 
            if (j <= i){
                transp[i][j] = matriz[j][i];
                transp[j][i] = matriz[i][j];
            }
            else{
                break;
            }
        }
    }
    copiar(transp, saida, n);
}
 
 
void somar(int matriz1[][MAX], int matriz2[][MAX], int saida[][MAX], int n){
    /* Soma de duas matrizes*/
    int valor;
    int soma[MAX][MAX];
 
    for(int i = 0; i < n; i++){
 
        for(int j = 0; j < n; j++){
 
            valor = matriz1[i][j] + matriz2[i][j];
            if (valor > 1){
                valor = 1;
            }
            soma[i][j] = valor;
        }
    }
    copiar(soma, saida, n);
}
 
void mult_elemento(int matriz1[][MAX], int matriz2[][MAX], int saida[][MAX], int n){
    /* Multiplica duas matrizes elemento a elemento */
    int mult[MAX][MAX];
 
    for(int i = 0; i < n; i++){
 
        for(int j = 0; j < n; j++){
 
            mult[i][j] = matriz1[i][j] * matriz2[i][j];
        }
    }
    copiar(mult, saida, n);
}
 
void mult_matriz(int matriz1[][MAX], int matriz2[][MAX], int saida[][MAX], int n){
    /* Função para multiplicar duas matrizes, garantindo que 1 + 1 = 1 */
 
    int mult[MAX][MAX];
    // Removendo o lixo de memória de mult
    limpar(mult, n);
 
    for(int i = 0; i < n; i++){
 
        for(int j = 0; j < n; j++){
 
            for(int k = 0; k < n; k++){
 
                mult[i][j] += matriz1[i][k] * matriz2[k][j];
                
                if (mult[i][j] > 1){
                    mult[i][j] = 1;
                }
            }
        }
    }
    copiar(mult, saida, n);
}
 
 
void bordas(int matriz1[][MAX], int matriz2[][MAX], int n){
    /* Guarda as bordas da imagem representada por matriz1 em matriz2 */
    int adj;
    int borda[MAX][MAX];
 
    // Copiando 'matriz' para 'borda
    copiar(matriz1, borda, n);
 
    // Verificando os pixels adjacentes
    for (int i = 1; i < n - 1; i++){
 
        for (int j = 1; j < n - 1; j++){
 
            adj = 0;
            if (matriz1[i - 1][j - 1] == 1){
                adj += 1;
            }
 
            if (matriz1[i - 1][j] == 1){
                adj += 1;
            }
 
            if (matriz1[i - 1][j + 1] == 1){
                adj += 1;
            }
 
            if (matriz1[i][j - 1] == 1){
                adj += 1;
            }
 
            if (matriz1[i][j + 1] == 1){
                adj += 1;
            }
 
            if (matriz1[i + 1][j - 1] == 1){
                adj += 1;
            }
 
            if (matriz1[i + 1][j] == 1){
                adj += 1;
            }
 
            if (matriz1[i + 1][j + 1] == 1){
                adj += 1;
            }
 
            if (adj == 8 || matriz1[i][j] == 0){
                borda[i][j] = 0;
            }
            else{
                borda[i][j] = 1;
            }
        }
    }
    copiar(borda, matriz2, n);
}
 
 
void imprime_matriz(int matriz[][MAX], int n){
 
    printf("\n");
    for(int i = 0; i < n; i++){
 
        for(int j = 0; j < n; j++){
 
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}
 
int comp_str(char str1[], char str2[]){
    /* Compara duas strings */
 
    for (int i = 0; str1[i] != '\000'; i++){
 
        if (str1[i] != str2[i]) {
            return 1;
        }
 
    }
    return 0;
}
 
int matriz_rep(char entrada, char saida){
    /* Retorna o número equivalente a cada uma das possíveis matrizes escolhidas para operações com única entrada*/
 
    if (entrada == 'A' && saida == 'A'){
        return 1;
    }
    else if (entrada == 'A' && saida == 'B')
    {
        return 2;
    }
    else if (entrada == 'B' && saida == 'B')
    {
        return 3;
    }
    else if (entrada == 'B' && saida == 'A')
    {
        return 4;
    }
    return 0;
}
 
int matriz_rep2(char entrada1, char entrada2, char saida){
    /* Retorna o número equivalente a cada uma das possíveis matrizes escolhidas para operções com duas entradas*/
 
    if (entrada1 == 'A' && entrada2 == 'A' && saida == 'A'){
        return 1;
    }
    else if (entrada1 == 'B' && entrada2 == 'B' && saida == 'B')
    {
        return 2;
    }
    else if (entrada1 == 'A' && entrada2 == 'A' && saida == 'B')
    {
        return 3;
    }
    else if (entrada1 == 'B' && entrada2 == 'B' && saida == 'A')
    {
        return 4;
    }
    else if (entrada1 == 'A' && entrada2 == 'B' && saida == 'A')
    {
        return 5;
    }
    else if (entrada1 == 'A' && entrada2 == 'B' && saida == 'B')
    {
        return 6;
    }
    else if (entrada1 == 'B' && entrada2 == 'A' && saida == 'A')
    {
        return 7;
    }
    else if (entrada1 == 'B' && entrada2 == 'A' && saida == 'B')
    {
        return 8;
    }
    return 0;
}
 
 
void efetuar_transp(int A[][MAX], int B[][MAX], char entrada1, char saida, int n){
    /* Efetua a transposição de acordo com a entrada e saida desejada */
 
    int tipo = matriz_rep(entrada1, saida);
    if (tipo == 1)
    {
        transpor(A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 2)
    {
        transpor(A, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 3)
    {
        transpor(B, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 4)
    {
        transpor(B, A, n);
        imprime_matriz(A, n);
    }        
}
 
void efetuar_bordas(int A[][MAX], int B[][MAX], char entrada1, char saida, int n){
    /* Efetua bordas de acordo com a entrada e saida desejada */
 
    int tipo = matriz_rep(entrada1, saida);
    if (tipo == 1)
    {
        bordas(A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 2)
    {
        bordas(A, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 3)
    {
        bordas(B, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 4)
    {
        bordas(B, A, n);
        imprime_matriz(A, n);
    }        
}
 
void efetuar_soma(int A[][MAX], int B[][MAX], int C[][MAX], char entrada1, char entrada2, char saida, int n){
    /* Efetua soma de acordo com as entradas e a saida desejada */
 
    int tipo = matriz_rep2(entrada1, entrada2, saida);
    if (tipo == 1)
    {
        somar(A, A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 2)
    {
        somar(B, B, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 3)
    {
        somar(A, A, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 4)
    {
        somar(B, B, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 5)
    {
        somar(A, B, A, n);
        imprime_matriz(A, n);
    }    
    else if (tipo == 6)
    {
        somar(A, B, B, n);
        imprime_matriz(B, n);
    }    
    else if (tipo == 7)
    {
        somar(B, A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 8)
    {
        somar(B, A, B, n);
        imprime_matriz(B, n);
    }    
}
 
void efetuar_multE(int A[][MAX], int B[][MAX], int C[][MAX], char entrada1, char entrada2, char saida, int n){
    /* Efetua multiplicação de elementos de acordo com as entradas e a saida desejada */
 
    int tipo = matriz_rep2(entrada1, entrada2, saida);
    if (tipo == 1)
    {
        mult_elemento(A, A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 2)
    {
        mult_elemento(B, B, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 3)
    {
        mult_elemento(A, A, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 4)
    {
        mult_elemento(B, B, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 5)
    {
        mult_elemento(A, B, A, n);
        imprime_matriz(A, n);
    }    
    else if (tipo == 6)
    {
        mult_elemento(A, B, B, n);
        imprime_matriz(B, n);
    }    
    else if (tipo == 7)
    {
        mult_elemento(B, A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 8)
    {
        mult_elemento(B, A, B, n);
        imprime_matriz(B, n);
    }    
}
 
void efetuar_multM(int A[][MAX], int B[][MAX], int C[][MAX], char entrada1, char entrada2, char saida, int n){
    /* Efetua multiplicação de matrizes de acordo com as entradas e a saida desejada */
 
    int tipo = matriz_rep2(entrada1, entrada2, saida);
    if (tipo == 1)
    {
        mult_matriz(A, A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 2)
    {
        mult_matriz(B, B, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 3)
    {
        mult_matriz(A, A, B, n);
        imprime_matriz(B, n);
    }
    else if (tipo == 4)
    {
        mult_matriz(B, B, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 5)
    {
        mult_matriz(A, B, A, n);
        imprime_matriz(A, n);
    }    
    else if (tipo == 6)
    {
        mult_matriz(A, B, B, n);
        imprime_matriz(B, n);
    }    
    else if (tipo == 7)
    {
        mult_matriz(B, A, A, n);
        imprime_matriz(A, n);
    }
    else if (tipo == 8)
    {
        mult_matriz(B, A, B, n);
        imprime_matriz(B, n);
    }    
}
 
 
int main(){
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int colunas, n_operacoes;
    char operacao[MAX], entrada1, entrada2, saida;
 
    scanf("%d", &colunas);
    scanf("%d", &n_operacoes);
 
    matriz_listrada(A, colunas);
    matriz_listrada(B, colunas);
 
    for (int i = 0; i < n_operacoes; i++){
 
        scanf("%s", operacao);
 
        if (comp_str(operacao, "TRANSPOSTA") == 0 || comp_str(operacao, "BORDAS") == 0)
        {
            scanf(" %c", &entrada1);
            scanf(" %c", &saida);
 
            if (comp_str(operacao, "TRANSPOSTA") == 0)
            {
                efetuar_transp(A, B, entrada1, saida, colunas);
            }
 
            else if (comp_str(operacao, "BORDAS") == 0)
            {
                efetuar_bordas(A, B, entrada1, saida, colunas);
            }
        }
 
        else {
            scanf(" %c", &entrada1);
            scanf(" %c", &entrada2);
            scanf(" %c", &saida);
 
            if (comp_str(operacao, "SOMA") == 0)
            {
                efetuar_soma(A, B, C, entrada1, entrada2, saida, colunas);
            }
 
            else if (comp_str(operacao, "MULTI_ELEM") == 0)
            {
                efetuar_multE(A, B, C, entrada1, entrada2, saida, colunas);
            }
 
            else if (comp_str(operacao, "MULTI_MAT") == 0)
            {
                efetuar_multM(A, B, C, entrada1, entrada2, saida, colunas);
            }
        }
    }
    return 0;
}