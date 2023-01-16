#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
    int analises;

    scanf("%d ", &analises);

    // Alocando um vetor de represas
    represa *represas = malloc(analises * sizeof(represa));

    for(int i = 0; i < analises; i++){

        represas[i] = nova_represa();

        le_medidas(represas[i]);
        media_niveis(represas[i], &represas[i].media);
        imprime_represa(represas[i]);

        free(represas[i].nome);
        free(represas[i].niveis);
    }

    free(represas);

    return 0;
}