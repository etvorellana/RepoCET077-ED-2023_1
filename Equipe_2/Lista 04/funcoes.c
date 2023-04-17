#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define TRUE 1
#define FALSE 0

Jogos *criaAcervo( int capacidade ) {

    Jogos *acervo;

    acervo = (Jogos*) malloc((capacidade + 1) * sizeof(Jogos));

    return acervo;
}

Jogos *carregaDados(char *fileName, int *tam) {

    int i = 0;
    char sep[1], str[2000], *ok;
    sep[0] = ',';
    Jogos *acervo;
    FILE *fp;
    fp = fopen(fileName, "r");
    acervo = criaAcervo(*tam);

    if(fp == NULL) {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    ok = fgets(str, 2000, fp); //Pega cabeçalho

    if (!ok) {
        printf("Erro ao o cabeçalho do CSV!!!");
        exit(1);
    }

    while(!feof(fp) && i < *tam) {
        ok = fgets(str, 2000, fp); // pega a linha do CSV

        if(ok) {
            char *campo;

            // APP ID
            campo = strtok(str, sep); // pega a string até a primeira ','
            acervo[i].appId = atoi(campo);

            // TITLE
            campo = strtok(NULL, sep);
            int pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].title = (char *) malloc( strlen(campo));
            strcpy(acervo[i].title, campo);

            // Data release
            campo = strtok(NULL, sep);
            pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].dataRelease = (char *)malloc(strlen(campo));
            strcpy(acervo[i].dataRelease, campo);

            // WINDOWS
            campo = strtok(NULL, sep);
            acervo[i].win = (char *)malloc(strlen(campo));
            strcpy(acervo[i].win, campo);

            // MAC
            campo = strtok(NULL, sep);
            acervo[i].mac = (char *)malloc(strlen(campo));
            strcpy(acervo[i].mac, campo);

            // LINUX
            campo = strtok(NULL, sep);
            acervo[i].linux = (char *)malloc(strlen(campo));
            strcpy(acervo[i].linux, campo);

            // RATING
            campo = strtok(NULL, sep);
            pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].rating = (char *)malloc(strlen(campo));
            strcpy(acervo[i].rating, campo);

            // POSITIVE RATIO
            campo = strtok(NULL, sep);
            acervo[i].positiveRatio = atoi(campo);

            // USER REVIEWS
            campo = strtok(NULL, sep);
            acervo[i].userReviews = atoi(campo);

            // PRICE FINAL
            campo = strtok(NULL, sep);
            acervo[i].priceFinal = atof(campo);

            // PRICE ORIGINAL
            campo = strtok(NULL, sep);
            acervo[i].priceOriginal = atof(campo);

            // DISCOUNT
            campo = strtok(NULL, sep);
            acervo[i].discount = atof(campo);

            i++;
        }
    }

    return acervo;
}

void limpaAcervo(Jogos *acervo, int tamanhoAcervo) {

    for (int i = 0; i < tamanhoAcervo; i++) {
        free(acervo[i].title);
        free(acervo[i].dataRelease);
        free(acervo[i].win);
        free(acervo[i].mac);
        free(acervo[i].linux);
        free(acervo[i].rating);
    }
    
    free(acervo);
}

int insereNaFila(Jogos item, TFilaLinear* filaParametro) {
    
    if( !isFilaCheia(filaParametro) ) {
        filaParametro->fila[filaParametro->fim] = item;
        filaParametro->fim++;
        return 1;
    }
    
    return 0;
}

int isFilaCheia(TFilaLinear* fila) {

    if((fila->fim - fila->inicio) == fila->capacidade){
        return 1;
    }

    return 0;
}

Jogos* removeDaFila(TFilaLinear* fila) {
    
    if (isFilaVazia(fila)) return 0;
    
    Jogos *item = &fila->fila[fila->inicio];
    fila->inicio++;
    
    return item;
}

int isFilaVazia(TFilaLinear * fila){
    if (fila->inicio == fila->fim) {
        return 1;
    }

    return 0;
}

int isPilhaVazia(TPilhaLinear* pilha) {
    if (pilha->topo == 0) {
        return 1;
    }
    return 0;
}

int isPilhaCheia(TPilhaLinear* pilha) {
    if (pilha->topo == pilha->capacidade) {
        return 1;
    }
    return 0;
}

int insereNaPilha(Jogos jogo, TPilhaLinear* pilha) {
    
    if (isPilhaCheia(pilha)) return 0;
    
    pilha->pilha[pilha->topo] = jogo;
    pilha->topo++;
    return 1;
}

TFilaLinear* criaFilaLinear(int capacidade){
    TFilaLinear *FilaLinear = (TFilaLinear*) malloc( sizeof(TFilaLinear) );
    inicializaFilaLinear( FilaLinear, capacidade );

    return FilaLinear;
}

void inicializaFilaLinear(TFilaLinear *FilaLinear, int capacidade){

    FilaLinear->fila = (Jogos*) malloc( capacidade * sizeof(Jogos) );
    FilaLinear->capacidade = capacidade;
    FilaLinear->inicio = 0;
    FilaLinear->fim = 0;

}

TPilhaLinear* criaPilhaLinear(int capacidade) {
    TPilhaLinear *PilhaLinear = (TPilhaLinear*) malloc( sizeof(TPilhaLinear) );
    inicializaPilhaLinear( PilhaLinear, capacidade );
    
    return PilhaLinear;
}

void inicializaPilhaLinear(TPilhaLinear *PilhaLinear, int capacidade) {

    PilhaLinear->pilha = (Jogos*) malloc( capacidade * sizeof(Jogos) );
    PilhaLinear->capacidade = capacidade;
    PilhaLinear->topo = 0;

}

Jogos* removeDaPilha(TPilhaLinear* PilhaLinear) {
    
    if (isPilhaVazia(PilhaLinear)) return 0;

    Jogos *removido;
    removido = &PilhaLinear->pilha[PilhaLinear->topo];
    PilhaLinear->topo--;
    
    return removido;
}