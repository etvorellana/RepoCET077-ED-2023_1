#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#define N 16

PNoArvBin newNoArvBin()
{
    PNoArvBin arv = (PNoArvBin)malloc(sizeof(TNoArvBin));
    arv->dir = NULL;
    arv->esq = NULL;
    return arv;
}

PNoArvBin insereNoArvBin(PNoArvBin arv, TInfo info, int nivel)
{
    if (arv == NULL)
    {
        arv = newNoArvBin();
        arv->info = info;
        arv->nivel = nivel;
    }
    else if (info.key < arv->info.key)
    {
        arv->esq = insereNoArvBin(arv->esq, info, ++nivel);
    }
    else
    {
        arv->dir = insereNoArvBin(arv->dir, info, ++nivel);
    }
    return arv;
}

void printArv(PNoArvBin arv, int tipo)
{
    if (arv != NULL)
    {
        if (tipo == 0)
        {
            printArv(arv->esq, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
            printArv(arv->dir, tipo);
        }
        else if (tipo == 1)
        {
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
        }
        else if (tipo == 2)
        {
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
        }
        else
        {
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
            printArv(arv->esq, tipo);
        }
    }
}

PNoArvBin buscaNaArv(PNoArvBin arv, int key)
{
    if (arv == NULL)
    {
        return NULL;
    }
    else if (arv->info.key == key)
    {
        return arv;
    }
    else if (key < arv->info.key)
    {
        return buscaNaArv(arv->esq, key);
    }
    else
    {
        return buscaNaArv(arv->dir, key);
    }
}

PNoArvBin removeNoArvBin(PNoArvBin arv, TInfo info)
{

    if (arv == NULL)
    {
        return NULL;
    }

    if (arv->info.key == info.key)
    {
        if (arv->dir != NULL && arv->esq != NULL)
        {
            PNoArvBin aux = newNoArvBin();
            aux = arv->dir;
            while (aux->esq != NULL)
            {
                aux = aux->esq;
            }
            arv->info = aux->info;
            arv->dir = removeNoArvBin(arv->dir, aux->info);
            return arv;
        }
        else if (arv->dir == NULL && arv->esq == NULL)
        {
            return NULL;
        }
        else if (arv->dir != NULL)
        {
            return arv->dir;
        }
        else if (arv->esq != NULL)
        {
            return arv->esq;
        }
    }
    else
    {
        if (info.key < arv->info.key)
        {
            arv->esq = removeNoArvBin(arv->esq, info);
            return arv;
        }
        else
        {
            arv->dir = removeNoArvBin(arv->dir, info);
            return arv;
        }
    }
}