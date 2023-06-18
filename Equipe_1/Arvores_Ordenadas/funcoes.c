#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Games *carregaDados(char *fileName, int *tam)
{
    Games *jogos;
    FILE *fp;
    int i = 0;
    char str[900];

    jogos = IniciaLista(CSVSIZE);

    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        printf("Arquivo não pode ser aberto\n");
        return NULL;
    }

    // pegando o cabeçalho
    char header[50];
    fscanf(fp, "%s", header);
    // printf("%s\n",header);

    // lendo o arquivo
    while (!feof(fp))
    {

        // id
        fscanf(fp, "\n%d", &jogos[i].ID);
        // nome
        fscanf(fp, ",%[^,]s", str);
        jogos[i].Name = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(jogos[i].Name, str);
        // plataforma
        fscanf(fp, ",%[^,]s", str);
        jogos[i].Platform = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(jogos[i].Platform, str);
        // ano de lançamento
        fscanf(fp, ",%d", &jogos[i].Year_Of_Release);
        // genero
        fscanf(fp, ",%[^,]s", str);
        jogos[i].Genre = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(jogos[i].Genre, str);
        // Empresa que publicou
        fscanf(fp, ",%[^,]s", str);
        jogos[i].Publisher = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(jogos[i].Publisher, str);
        // vendas
        fscanf(fp, ",%f,%f,%f,%f,%f,", &jogos[i].NA_Sales, &jogos[i].EU_Sales,
               &jogos[i].JP_sales, &jogos[i].Other_Sales, &jogos[i].Global_Sales);
        fscanf(fp, "%[^\n]s", str);

        i++;
    }
    *tam = i;
    int err = fclose(fp);
    if (err) // err != 0
    {
        printf("Arquivo incorretamente fechado!!\n");
    }
    return jogos;
}

Games *IniciaLista(int capacidade)
{
    Games *jogos;
    jogos = (Games *)malloc((capacidade) * sizeof(Games));
    return jogos;
}

void cpyGame(Games jogo, Games *jogo_copia)
{

    (*jogo_copia).ID = jogo.ID;

    (*jogo_copia).Name = (char *)malloc((strlen(jogo.Name) + 1) * sizeof(char));
    strcpy((*jogo_copia).Name, jogo.Name);

    (*jogo_copia).Platform =
        (char *)malloc((strlen(jogo.Platform) + 1) * sizeof(char));
    strcpy((*jogo_copia).Platform, jogo.Platform);

    (*jogo_copia).Year_Of_Release = jogo.Year_Of_Release;

    (*jogo_copia).Genre = (char *)malloc((strlen(jogo.Genre) + 1) * sizeof(char));
    strcpy((*jogo_copia).Genre, jogo.Genre);

    (*jogo_copia).Publisher =
        (char *)malloc((strlen(jogo.Publisher) + 1) * sizeof(char));
    strcpy((*jogo_copia).Publisher, jogo.Publisher);

    (*jogo_copia).NA_Sales = jogo.NA_Sales;

    (*jogo_copia).EU_Sales = jogo.EU_Sales;

    (*jogo_copia).JP_sales = jogo.JP_sales;

    (*jogo_copia).Other_Sales = jogo.Other_Sales;

    (*jogo_copia).Global_Sales = jogo.Global_Sales;
}

void limpaJogo(Games *jogo)
{
    free((*jogo).Name);
    free((*jogo).Platform);
    free((*jogo).Genre);
    free((*jogo).Publisher);
}

void primeiras_letras(char *nome)
{
    printf("(%c%c%c", nome[0], nome[1], nome[2]);
}

// arvore

noArvBin *newNoArvBin()
{
    noArvBin *arv;
    arv = (noArvBin *)malloc(sizeof(noArvBin));
    arv->altura = 0;
    arv->dir = NULL;
    arv->esq = NULL;

    return arv;
}

short int alturaDoNo(noArvBin *arv)
{
    if (arv == NULL)
    {
        return -1;
    }
    else
    {
        return arv->altura;
    }
}

noArvBin *insereNoArvBin(noArvBin *arv, Games jogo)
{
    if (arv == NULL)
    {
        arv = newNoArvBin();
        cpyGame(jogo, &(arv->jogo));
    }
    else if (jogo.ID < arv->jogo.ID)
    {
        arv->esq = insereNoArvBin(arv->esq, jogo);
    }
    else if (jogo.ID > arv->jogo.ID)
    {
        arv->dir = insereNoArvBin(arv->dir, jogo);
    }
    short int a = alturaDoNo(arv->esq);
    short int b = alturaDoNo(arv->dir);

    arv->altura = ((a > b) ? a : b) + 1;
    return arv;
}

void printArv(noArvBin *arv, int tipo)
{
    if (arv != NULL)
    {
        if (tipo == 0)
        {
            printArv(arv->esq, tipo);
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\n", arv->jogo.ID, arv->altura);
            printArv(arv->dir, tipo);
        }
        else if (tipo == 1)
        {
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\n", arv->jogo.ID, arv->altura);
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
        }
        else if (tipo == 2)
        {
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\n", arv->jogo.ID, arv->altura);
        }
        else
        {
            printArv(arv->dir, tipo);
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\n", arv->jogo.ID, arv->altura);
            printArv(arv->esq, tipo);
        }
    }
}

void printArv2(noArvBin *arv, noArvBin *arvAVL, int tipo)
{
    if (arv != NULL && arvAVL != NULL)
    {
        if (tipo == 0)
        {
            printArv2(arv->esq, arvAVL->esq, tipo);
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\t\t", arv->jogo.ID, arv->altura);
            primeiras_letras(arvAVL->jogo.Name);
            printf(", %d, %d)\n", arvAVL->jogo.ID, arvAVL->altura);
            printArv2(arv->dir, arvAVL->dir, tipo);
        }
        else if (tipo == 1)
        {
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\t\t", arv->jogo.ID, arv->altura);
            primeiras_letras(arvAVL->jogo.Name);
            printf(", %d, %d)\n", arvAVL->jogo.ID, arvAVL->altura);
            printArv2(arv->esq, arvAVL->esq, tipo);
            printArv2(arv->dir, arvAVL->dir, tipo);
        }
        else if (tipo == 2)
        {
            printArv2(arv->esq, arvAVL->esq, tipo);
            printArv2(arv->dir, arvAVL->dir, tipo);
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\t", arv->jogo.ID, arv->altura);
            primeiras_letras(arvAVL->jogo.Name);
            printf(", %d, %d)\n", arvAVL->jogo.ID, arvAVL->altura);
        }
        else
        {
            printArv2(arv->dir, arvAVL->dir, tipo);
            primeiras_letras(arv->jogo.Name);
            printf(", %d, %d)\t", arv->jogo.ID, arv->altura);
            primeiras_letras(arvAVL->jogo.Name);
            printf(", %d, %d)\n", arvAVL->jogo.ID, arvAVL->altura);
            printArv2(arv->esq, arvAVL->esq, tipo);
        }
    }
}

noArvBin *removeDaArv(noArvBin *arv, int ID)
{
    if (arv == NULL)
    {
        return NULL;
    }
    else if (arv->jogo.ID == ID)
    {
        if (arv->dir == NULL && arv->esq == NULL)
        {
            free(arv);
            return NULL;
        }
        else if (arv->esq == NULL)
        {
            noArvBin *aux = arv->dir;
            limpaJogo(&(arv->jogo));

            free(arv);
            arv = aux;
        }
        else if (arv->dir == NULL)
        {
            noArvBin *aux = arv->esq;
            limpaJogo(&(arv->jogo));

            free(arv);
            arv = aux;
        }
        else
        {
            noArvBin *aux = arv->dir;
            while (aux->esq != NULL)
            {
                aux = aux->esq;
            }
            cpyGame(aux->jogo, &(arv->jogo));
            arv->dir = removeDaArv(arv->dir, aux->jogo.ID);
        }
    }
    else if (ID < arv->jogo.ID)
    {
        arv->esq = removeDaArv(arv->esq, ID);
    }
    else if (ID > arv->jogo.ID)
    {
        arv->dir = removeDaArv(arv->dir, ID);
    }

    short int a = alturaDoNo(arv->esq);
    short int b = alturaDoNo(arv->dir);

    arv->altura = ((a > b) ? a : b) + 1;
    return arv;
}

noArvBin *buscaNaArv(noArvBin *arv, int ID)
{
    if (arv == NULL)
    {
        return NULL;
    }
    else if (ID < arv->jogo.ID)
    {
        return buscaNaArv(arv->esq, ID);
    }
    else if (ID > arv->jogo.ID)
    {
        return buscaNaArv(arv->dir, ID);
    }
    return arv;
}

noArvBin *insereNoArvAVL(noArvBin *arv, Games jogo)
{
    if (arv == NULL)
    {
        arv = newNoArvBin();
        cpyGame(jogo, &(arv->jogo));
    }
    else
    {
        if (jogo.ID < arv->jogo.ID)
        {
            arv->esq = insereNoArvAVL(arv->esq, jogo);
        }
        else if (jogo.ID > arv->jogo.ID)
        {
            arv->dir = insereNoArvAVL(arv->dir, jogo);
        }
    }
    short a = alturaDoNo(arv->esq);
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    arv = balanceia(arv);
    return arv;
}

noArvBin *removeDaArvAVL(noArvBin *arv, int ID)
{
    if (arv == NULL)
    {
        return NULL;
    }
    else if (arv->jogo.ID == ID)
    {
        if (arv->dir == NULL && arv->esq == NULL)
        {   
            limpaJogo(&(arv->jogo));
            free(arv);
            return NULL;
        }
        else if (arv->esq == NULL)
        {
            noArvBin *aux = arv->dir;
            limpaJogo(&(arv->jogo));
            free(arv);
            arv = aux;
        }
        else if (arv->dir == NULL)
        {
            noArvBin *aux = arv->esq;
            limpaJogo(&(arv->jogo));
            free(arv);
            arv = aux;
        }
        else
        {
            noArvBin *aux = arv->dir;
            while (aux->esq != NULL)
            {
                aux = aux->esq;
            }
            cpyGame(aux->jogo, &(arv->jogo));
            arv->dir = removeDaArvAVL(arv->dir, aux->jogo.ID);
        }
    }
    else if (ID < arv->jogo.ID)
    {
        arv->esq = removeDaArvAVL(arv->esq, ID);
    }
    else if (ID > arv->jogo.ID)
    {
        arv->dir = removeDaArvAVL(arv->dir, ID);
    }

    short int a = alturaDoNo(arv->esq);
    short int b = alturaDoNo(arv->dir);

    arv->altura = ((a > b) ? a : b) + 1;
    arv = balanceia(arv);
    return arv;
}

noArvBin *rotacaoDir(noArvBin *arv)
{
    noArvBin *esq, *dirDoEsq;
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

noArvBin *rotacaoEsq(noArvBin *arv)
{
    noArvBin *dir, *esqDoDir;
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

noArvBin *rotacaoEsqDir(noArvBin *arv)
{
    arv->esq = rotacaoEsq(arv->esq);
    return rotacaoDir(arv);
}

noArvBin *rotacaoDirEsq(noArvBin *arv)
{
    arv->dir = rotacaoDir(arv->dir);
    return rotacaoEsq(arv);
}

short balanceamento(noArvBin *no)
{
    if (no)
        return (alturaDoNo(no->esq) - alturaDoNo(no->dir));
    else
        return 0;
}

noArvBin *balanceia(noArvBin *arv)
{
    short fb = balanceamento(arv);
    short fb_dir = balanceamento(arv->dir);
    short fb_esq = balanceamento(arv->esq);

    if (fb < -1 && fb_dir <= 0)
        arv = rotacaoEsq(arv);
    else if (fb > 1 && fb_esq >= 0)
        arv = rotacaoDir(arv);
    else if (fb > 1 && fb_esq < 0)
        arv = rotacaoEsqDir(arv);
    else if (fb < -1 && fb_dir > 0)
        arv = rotacaoDirEsq(arv);

    return arv;
}