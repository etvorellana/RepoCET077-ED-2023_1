#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#define N 16

int main(void)
{
    PInfo lista;
    
    lista = (PInfo) malloc(N * sizeof(TInfo));
    // Criando uma lista
    for(int i = 0; i < N; i++)
    {
        lista[i].key = rand() % 100;
        lista[i].val = 5.0*rand()/RAND_MAX;
        //todo: verificar para nao ter chaves repetidas
        printf("(%d, %.2f)  ", lista[i].key, lista[i].val);
    }

    printf("\n------------------\n");

    PNoArvBin arv = NULL;
    for(int i = 0; i < N; i++)
    {
        arv = insereNoArvBin(arv, lista[i], 0);
    }


    printArv(arv, 0);
    printf("\n\n------------------\n");
    printArv(arv, 1);
    printf("\n\n------------------\n");
    printArv(arv, 2);
    printf("\n\n------------------\n");
    printArv(arv, 3);
    printf("\n\n");
    int i;

    printf("Remoção\n\n");

    for(i = 0; i < N; i++){
        printArv(arv,1);
        printf("\n\n------------------\n\n");
        printf("Valor na iteração: %d\n",i);
        printf("Item que vai ser removido: %d\n", lista[i].key);
        arv = removeNoArvBin(arv, lista[i]);
        printf("\n");
    }

    return 0;
}