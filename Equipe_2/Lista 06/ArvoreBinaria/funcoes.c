#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


Jogos *carregaDados(char *fileName, int *tam)
{

    int i = 0;
    char sep[1], str[2000], *ok;
    sep[0] = ',';
    Jogos *acervo;
    FILE *fp;
    fp = fopen(fileName, "r");
    acervo = criaAcervo(*tam);

    if (fp == NULL)
    {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    ok = fgets(str, 2000, fp); // Pega cabeçalho

    if (!ok)
    {
        printf("Erro ao o cabeçalho do CSV!!!");
        exit(1);
    }

    while (!feof(fp) && i < *tam)
    {
        ok = fgets(str, 2000, fp); // pega a linha do CSV

        if (ok)
        {
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
            acervo[i].title = (char *)malloc(strlen(campo));
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
            acervo[i].LINUX = (char *)malloc(strlen(campo));
            strcpy(acervo[i].LINUX, campo);

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

Jogos *criaAcervo(int capacidade)
{

    Jogos *acervo;

    acervo = (Jogos *)malloc((capacidade + 1) * sizeof(Jogos));

    return acervo;
}


PNoArvBin newNoArvBin()
{
    PNoArvBin arv =  malloc(sizeof(PNoArvBin));
    arv->dir = NULL;
    arv->esq = NULL;
    arv->altura = 0;
    return arv;
}
PNoArvBin insereNoArvBin(PNoArvBin arv, Jogos jogo){
    if(arv == NULL){
        arv = newNoArvBin();
        arv->jogo = jogo.appId;
    }else if(jogo.appId < arv->jogo->appId){
        arv->esq = insereNoArvBin(arv->esq, jogo);
    }else if (jogo.appId> arv->jogo->appId){
        arv->dir = insereNoArvBin(arv->dir, jogo);
    }
    short a = alturaDoNo(arv->esq); 
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    return arv;
}

PNoArvBin insereNoArvAVL(PNoArvBin arv, Jogos jogo){
    if(arv == NULL){
        arv = newNoArvBin();
        arv->jogo = jogo.appId;
    }else if(jogo.appId < arv->jogo->appId){
        arv->esq = insereNoArvAVL(arv->esq, jogo);
    }else if (jogo.appId > arv->jogo->appId){
        arv->dir = insereNoArvAVL(arv->dir, jogo);
    }
    short a = alturaDoNo(arv->esq); 
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    arv = balanceia(arv);
    return arv;
}

PNoArvBin removeDaArv(PNoArvBin arv, int key) {
    if(arv == NULL) {
        return NULL;
    } else if(arv->jogo->appId == key) {
        if(arv->esq == NULL && arv->dir == NULL){
            free(arv);
            return NULL;
        } else if(arv->esq == NULL) {
            PNoArvBin aux = arv->dir;
            free(arv);
            arv = aux;
        } else if(arv->dir == NULL){
            PNoArvBin aux = arv->esq;
            free(arv);
            arv = aux;
        }else{
            PNoArvBin aux = arv->esq;
            while(aux->dir != NULL){
                aux = aux->dir;    
            }
            arv->jogo = aux->jogo;
            arv->esq = removeDaArv(arv->esq, aux->jogo->appId);
        }
    }else if(key < arv->jogo->appId){
        arv->esq = removeDaArv(arv->esq, key);
    }else{
        arv->dir = removeDaArv(arv->dir, key);
    }
    short a = alturaDoNo(arv->esq); 
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    return arv;
}

PNoArvBin buscaNaArvAVL(PNoArvBin arv, int key){
    if(arv == NULL){
        return NULL;
    }else if(arv->jogo->appId == key){
        return arv;
    }else if(key < arv->jogo->appId){
        return buscaNaArv(arv->esq, key);
    }else{
        return buscaNaArv(arv->dir, key);
    }
}

void printArv(PNoArvBin arv, int tipo) {
    if (arv != NULL) {
        if (tipo == 0) {
            printArv(arv->esq, tipo);
            printf("(%d, %.2f, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
            printArv(arv->dir, tipo);
        } else if (tipo == 1) {
            printf("(%d, %.2f, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
        } else if (tipo == 2) {
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
        } else {
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
            printArv(arv->esq, tipo);
        }
    }
}


short int alturaDoNo(PNoArvBin arv){
    if(arv == NULL){
        return -1;
    }else{
        return arv->altura;
    }
}

PNoArvBin balanceia(PNoArvBin arv)
{
    short fb = balanceamento(arv);
    short fb_dir = balanceamento(arv->dir);
    short fb_esq = balanceamento(arv->esq);
    if(fb < -1 && fb_dir <= 0)
        arv = rotacaoEsq(arv);
    else if(fb > 1 && fb_esq >= 0)
        arv = rotacaoDir(arv);
    else if(fb > 1 && fb_esq < 0)
        arv = rotacaoEsqDir(arv);
    else if(fb < -1 && fb_dir > 0)
        arv = rotacaoDirEsq(arv);
    return arv; 
        
}

short balanceamento(PNoArvBin no)
{
    if(no)
        return (alturaDoNo(no->esq) - alturaDoNo(no->dir));
    else
        return 0;
}

PNoArvBin rotacaoEsqDir(PNoArvBin arv)
{
    arv->esq = rotacaoEsq(arv->esq);
    return rotacaoDir(arv);
}   

PNoArvBin rotacaoDirEsq(PNoArvBin arv)
{
    arv->dir = rotacaoDir(arv->dir);
    return rotacaoEsq(arv);
}

PNoArvBin rotacaoDir(PNoArvBin arv)
{
    PNoArvBin esq, dirDoEsq;
    esq = arv->esq;
    dirDoEsq = esq->dir;

    esq->dir = arv;
    arv->esq = dirDoEsq;
    short a = alturaDoNo(arv->esq);
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    a = alturaDoNo(esq->esq);
    b = alturaDoNo(esq->dir);
    esq->altura = ((a > b) ? a : b) + 1;
    return esq;
}


PNoArvBin rotacaoEsq(PNoArvBin arv)
{
    PNoArvBin dir, esqDoDir;
    dir = arv->dir;
    esqDoDir = dir->esq;

    dir->esq = arv;
    arv->dir = esqDoDir;
    short a = alturaDoNo(arv->esq);
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    a = alturaDoNo(dir->esq);
    b = alturaDoNo(dir->dir);
    dir->altura = ((a > b) ? a : b) + 1;
    return dir;
}
