#include <stdio.h>
#include <stdlib.h>
#define N 16

typedef struct
{
    int key;
    float val;
}TInfo;

typedef TInfo *PInfo;

struct noArvBin{
    TInfo info;
    int nivel;
    struct noArvBin *esq;
    struct noArvBin *dir;
};

typedef struct noArvBin TNoArvBin;
typedef TNoArvBin *PNoArvBin;

PNoArvBin newNoArvBin();
PNoArvBin insereNoArvBin(PNoArvBin arv, TInfo info, int nivel);
void printArv(PNoArvBin arv, int tipo);

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

    return 0;
}

PNoArvBin newNoArvBin()
{
    PNoArvBin arv = (PNoArvBin) malloc(sizeof(TNoArvBin));
    arv->dir = NULL;
    arv->esq = NULL;
    return arv;
}

PNoArvBin insereNoArvBin(PNoArvBin arv, TInfo info, int nivel){
    if(arv == NULL){
        arv = newNoArvBin();
        arv->info = info;
        arv->nivel = nivel;
    }else if(info.key < arv->info.key){
        arv->esq = insereNoArvBin(arv->esq, info, ++nivel);
    }else{
        arv->dir = insereNoArvBin(arv->dir, info, ++nivel);
    }
    return arv;
}

void printArv(PNoArvBin arv, int tipo)
{
    if(arv != NULL)
    {
        if (tipo == 0)
        {
            printArv(arv->esq, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
            printArv(arv->dir, tipo);
        }else if (tipo == 1)
        {   
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
        }else if (tipo == 2)
        {
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
        }else{
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->nivel);
            printArv(arv->esq, tipo);
        }
    }       
}

PNoArvBin buscaNaArv(PNoArvBin arv, int key){
    if(arv == NULL){
        return NULL;
    }else if(arv->info.key == key)
    {
        return arv;
    }else if(key < arv->info.key)
    {
        return buscaNaArv(arv->esq, key);
    }else
    {
        return buscaNaArv(arv->dir, key);
    }
}