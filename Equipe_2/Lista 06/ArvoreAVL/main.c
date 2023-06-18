#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"
#define N 16

int main(void)
{
    Jogos *acervo;
    int tamanhoAcervo = 16;
    PNoArvBin arvAVL = NULL;
    
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &tamanhoAcervo );

    printf("\n-------------------------- INSERINDO NA AVL -------------------------------------\n");

    /*arvAVL = insereNoArvAVL(arvAVL, acervo[5]);
    printf("\n %s", arvAVL);*/

    int inseriu = 0;
    for(int i = 0; i < N; i++){
        if(buscaNaArvAVL(arvAVL, acervo[i].appId)){
            printf("\nElemento %d não pode ser inserido\n!", acervo[i].appId);
        }else{
            arvAVL = insereNoArvAVL(arvAVL, acervo[i]);
        }
        if(percorre(arvAVL) == i + 1){  
            printf("\nElemento %d foi inserido\n!", acervo[i].appId);
            inseriu++;
        }
    }

    if(percorre(arvAVL) == inseriu){
        printf("Todos os elementos foram inseridos!\n");
    }else{
        printf("Nem todos os elementos foram inseridos!\n");
    }

    printArv(arvAVL, 0);
    printf("\n");
    printf("------------------\n");
    printArv(arvAVL, 1);
    printf("\n");
    printf("------------------\n");
    printArv(arvAVL, 2);
    printf("\n");
    printf("------------------\n");
    printArv(arvAVL, 3);
    printf("\n");
    printf("------------------\n");

    printf("\n----------------------------- REMOVENDO DA AVL --------------------------------\n");

    int removeu = 0;
    for (int i = 0; i < N; i++){

        if(arvAVL == NULL){
            printf("\n Não há elementos para remover!\n");
        }else{
            arvAVL = removeDaArvAVL(arvAVL, acervo[i].appId);
            if(!buscaNaArvAVL(arvAVL, acervo[i].appId)){
            printf("\n Elemento %d foi removido!\n", acervo[i].appId);
            removeu++;
            
            printArv(arvAVL, 0);
            printf("\n");
            printf("------------------\n");
            }
        }
    }

    if(percorre(arvAVL) == removeu){
        printf("Todos os elementos foram removidos!");
    }else{
        printf("Nem todos os elementos foram removidos!\n");
    }
    
    return 0;
}
