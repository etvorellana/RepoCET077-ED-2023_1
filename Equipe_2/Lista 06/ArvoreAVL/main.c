#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"
#define N 16

int main() {

    Jogos *acervo;
    int n = 16;
    PNoArvBin arv = NULL;
    
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &n );
    
    Jogos *lista = malloc(n * sizeof(Jogos));
    
    printf("Preenchendo a lista");
    for( int tam = 0; tam < n; tam++)
    {
        incRegistro( acervo[tam], lista, tam ); 
        printf("%d",lista[tam].appId);
    }
    
    printf("Preenchendo a arvore");
    for(int i = 0; i < n; i++)
    {
        arv = insereNoArvAVL(arv, lista[i]); 
    }

    
    printf("Impressão dos elementos da arvore:\n");
    printArv(arv, 0);
    printf("\n");
    printf("------------------\n");
    printArv(arv, 1);
    printf("\n");
    printf("------------------\n");
    printArv(arv, 2);
    printf("\n");
    printf("------------------\n");
    printArv(arv, 3);
    printf("\n");
    printf("------------------\n");

    for(int i = 0; i < n; i++)
    {
       arv = removeDaArvAVL(arv, lista[i]);
    }

    printf("Removendo elementos da arvore");
    printf("Impressão:\n");
    printArv(arv, 0);
    printf("\n");
    printf("------------------\n");
    printArv(arv, 1);
    printf("\n");
    printf("------------------\n");
    printArv(arv, 2);
    printf("\n");
    printf("------------------\n");
    printArv(arv, 3);
    printf("\n");
    printf("------------------\n");

    return 0;

}
