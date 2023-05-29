#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h" // contem o struct dos dados

NoArv* newNoArvBin()
{
    NoArv *arv = (NoArv *) malloc(sizeof(NoArv));
    arv->dir = NULL;
    arv->esq = NULL;
    return arv;
}

NoArv* inserir(NoArv *raiz, Tinfo info, int nivel) //corpo da função para inserir elemento
{
    if (!raiz) //se raiz for igual a NULL
    {
        raiz = newNoArvBin(); //alocando espaço na memória
        raiz -> info = info; //atribuição do valor
        raiz -> nivel = nivel;
        return raiz;
    }

    else //caso contrário
    {
        if (info.key < raiz -> info.key) //se value for menor que o valor que estiver no campo
            raiz -> esq = inserir(raiz -> esq, info, ++nivel);
        else //caso seja maior
            raiz -> dir = inserir(raiz -> dir, info, ++nivel);

        return raiz;
    }
}

void imprimir(NoArv *arv, int tipo)
{
    if(arv != NULL)
    {
        if (tipo == 0)
        {
            imprimir(arv->esq, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.value, arv->nivel);
            imprimir(arv->dir, tipo);
        }else if (tipo == 1)
        {   
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.value, arv->nivel);
            imprimir(arv->esq, tipo);
            imprimir(arv->dir, tipo);
        }else if (tipo == 2)
        {
            imprimir(arv->esq, tipo);
            imprimir(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.value, arv->nivel);
        }else{
            imprimir(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.value, arv->nivel);
            imprimir(arv->esq, tipo);
        }
    }       
}

void inserir_i(NoArv **raiz, Tinfo info, int nivel) //corpo do procedimento
{
    NoArv *aux = *raiz;

    while(aux)
    {
        if (info.key < aux -> info.key)
            raiz = &aux -> esq;
        else 
            raiz = &aux -> dir;

        nivel++;
        aux = *raiz;
    }

    aux = newNoArvBin();
    aux -> info = info;
    aux -> nivel = nivel;

    *raiz = aux;
}

NoArv* buscaRec(NoArv *raiz, int key) //corpo da função de busca recursiva
{
    if (raiz) 
    {
        if (key == raiz -> info.key)
            return raiz;
        else if (key < raiz -> info.key)
            return buscaRec(raiz -> esq, key);
        else
            return buscaRec(raiz -> dir, key);
    }

    return NULL;
}

NoArv* buscai(NoArv *raiz, int key) //corpo da função de busca iterativa
{
    NoArv *aux = raiz;
    while (aux) //enquanto aux != NULL
    {
        if (key < aux -> info.key)
            aux = aux -> esq;
        else if (key > aux -> info.key)
            aux = aux -> dir;
        else
            return aux;
    }

    return NULL;
}

NoArv* removeNoArv(NoArv *raiz, Tinfo info) //corpo da função de remoção
{
    if (!raiz) //se raiz == NULL
        return NULL;
    else 
    {
        if (info.key == raiz -> info.key) //encontrei o elemento
        {
            if (raiz -> esq && raiz -> dir) // se as duas sub-arvores são != NULL
            {
                NoArv *aux = raiz -> esq;
                while (aux -> dir)
                    aux = aux -> dir;
                raiz -> info = aux -> info;
                aux -> info = info;
                raiz -> esq = removeNoArv(raiz -> esq, info);
                return raiz;
            }

            else if (raiz -> esq) //se a sub-arvore da esquerda != NULL
            {
                NoArv *aux = raiz -> esq;
                free(raiz);
                return aux;
            }

            else if (raiz -> dir) //se a sub-arvore da direita != NULL
            {
                NoArv *aux = raiz -> dir;
                free(raiz);
                return aux;
            }

            else //se as duas sub-arvores forem nulas
            {
                free(raiz);
                return NULL;
            }
        }
        
        else // caso não tenha encontrado
        {
            if (info.key < raiz -> info.key) //se a key for menor que a key da raiz
                raiz -> esq = removeNoArv(raiz -> esq, info);
            else //se a key for maior que a key da raiz
                raiz -> dir = removeNoArv(raiz -> dir, info);

            return raiz;
        }
    }
}