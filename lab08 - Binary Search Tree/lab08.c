#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(){
    p_mapa mapa, cidade;
    p_visitas visitas, busca;
    char comando[50], nome[MAX];
    int data, inicio, fim, pista, operacoes;
    mapa = criar_mapa();
    visitas = criar_visitas();
 
    scanf("%d", &operacoes);
 
    for(int i = 0; i < operacoes; i++){
        scanf("%s", comando);
 
        if (strcmp(comando, "insere_visita") == 0){
            scanf("%s", nome);
            scanf("%d", &data);
            scanf("%d", &pista);
 
            // Verificando se a cidade a ser inserida já está na árvore de cidades
            cidade = buscar_mapa(mapa, nome);
            if (cidade != NULL){
                cidade -> qtd_visitas ++;
            }
            else{
                mapa = inserir_mapa(mapa, nome);
                relatorio_mapa(nome);
            }
            visitas = inserir_visita(visitas, data, nome, pista);
            relatorio_visitas(data, nome);
        }
 
        else if (strcmp(comando, "exclui_visita") == 0){
            scanf("%d", &data);
 
            // Verificando se a cidade referente à data corresponde a uma cidade que deverá ser excluida
            busca = buscar_visitas(visitas, data);
            cidade = buscar_mapa(mapa, busca->nome);
            relatorio_cidade(cidade);
            if (cidade->qtd_visitas - 1 == 0){
                mapa = remover_cidade(mapa, cidade->nome);
            }
            else{
                cidade->qtd_visitas--;
            }
            visitas = exclui_visita(visitas, data);
        }
 
        else if (strcmp(comando, "relatorio_data") == 0){
            scanf("%d", &inicio);
            scanf("%d", &fim);
            printf("--VISITAS--\n");
            relatorio_datas(visitas, inicio, fim);
        }
 
        else if (strcmp(comando, "relatorio_pista") == 0){
            scanf("%d", &inicio);
            scanf("%d", &fim);
            printf("--PISTAS--\n");
            relatorio_pistas(visitas, inicio, fim);
        }
    }
    liberar_mapa(mapa);
    liberar_visitas(visitas);
 
    return 0;
}