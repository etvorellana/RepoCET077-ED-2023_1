#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define N 16

int main() {

    Jogos *acervo;
    int n = 16;
    
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &n );
    
    Jogos *lista = malloc(n * sizeof(Jogos));
    
    printf("Preenchendo a lista");

    for( int tam = 0; tam < n; tam++) {
        incRegistro( acervo[tam], lista, tam ); 
        printf("%d",lista[tam].appId);
    }
    
    
    PNoArvBin arv = NULL;
    for(int i = 0; i < n; i++)
    {
        arv = insereNoArvAVL(arv, lista[i]); 
    }

    printf("Preenchendo a arvore");
    printArv(arv);

    for(int i = 0; i < n; i++)
    {
       arv = removeDaArvAVL(arv, lista[i]);
    }

    printf("Removendo elementos da arvore");
    printArv(arv);

    return 0;

}
