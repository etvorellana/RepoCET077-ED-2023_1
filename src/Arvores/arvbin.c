#include <stdio.h>
#include <stdlib.h>
#define N 64

typedef struct
{
    int key;
    float val;
}TInfo;

typedef TInfo *PInfo;

struct noArvBin{
    TInfo info;
    short int altura;
    struct noArvBin *esq;
    struct noArvBin *dir;
};

typedef struct noArvBin TNoArvBin;
typedef TNoArvBin *PNoArvBin;

PNoArvBin newNoArvBin();
PNoArvBin insereNoArvBin(PNoArvBin arv, TInfo info);
PNoArvBin insereNoArvAVL(PNoArvBin arv, TInfo info);
PNoArvBin removeDaArv(PNoArvBin arv, int key);
PNoArvBin buscaNaArv(PNoArvBin arv, int key);
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
        //arv = insereNoArvBin(arv, lista[i]);
        arv = insereNoArvAVL(arv, lista[i]);
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
    printf("------------------\n");
    
    int index = rand() % N;
    printf("Buscando chave : %d\n", lista[index].key);
    PNoArvBin no = buscaNaArv(arv, lista[index].key);
    if(no != NULL)
        printf("(%d, %.2f, %d)\n", no->info.key, no->info.val, no->altura);
    else
        printf("Chave nao encontrada\n");

    index = rand() % 100;
    printf("Buscando chave : %d\n", index);
    no = buscaNaArv(arv, index);
    if(no != NULL)
        printf("(%d, %.2f, %d)\n", no->info.key, no->info.val, no->altura);
    else
        printf("Chave nao encontrada\n");
    printf("\n------------------\n");
    printArv(arv, 1);
    printf("\n------------------\n");
    index = rand() % N;
    printf("Removendo chave : %d\n", lista[index].key);
    arv = removeDaArv(arv, lista[index].key);
    printf("\n------------------\n");
    printArv(arv, 1);
    printf("\n------------------\n");
    printf("Buscando chave : %d\n", lista[index].key);
    no = buscaNaArv(arv, lista[index].key);
    if(no != NULL)
        printf("(%d, %.2f, %d)\n", no->info.key, no->info.val, no->altura);
    else
        printf("Chave nao encontrada\n");

    return 0;
}

PNoArvBin newNoArvBin()
{
    PNoArvBin arv = (PNoArvBin) malloc(sizeof(TNoArvBin));
    arv->dir = NULL;
    arv->esq = NULL;
    arv->altura = 0;
    return arv;
}

short int alturaDoNo(PNoArvBin arv){
    if(arv == NULL){
        return -1;
    }else{
        return arv->altura;
    }
}

PNoArvBin insereNoArvBin(PNoArvBin arv, TInfo info){
    if(arv == NULL){
        arv = newNoArvBin();
        arv->info = info;
    }else if(info.key < arv->info.key){
        arv->esq = insereNoArvBin(arv->esq, info);
    }else if (info.key > arv->info.key){
        arv->dir = insereNoArvBin(arv->dir, info);
    }
    short a = alturaDoNo(arv->esq); 
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    return arv;
}

void printArv(PNoArvBin arv, int tipo)
{
    if(arv != NULL)
    {
        if (tipo == 0)
        {
            printArv(arv->esq, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->altura);
            printArv(arv->dir, tipo);
        }else if (tipo == 1)
        {   
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->altura);
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
        }else if (tipo == 2)
        {
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->altura);
        }else{
            printArv(arv->dir, tipo);
            printf("(%d, %.2f, %d)  ", arv->info.key, arv->info.val, arv->altura);
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

PNoArvBin removeDaArv(PNoArvBin arv, int key)
{
    if(arv == NULL)
    {
        return NULL;
    }else if(arv->info.key == key)
    {
        if(arv->esq == NULL && arv->dir == NULL)
        {
            free(arv);
            return NULL;
        }else if(arv->esq == NULL)
        {
            PNoArvBin aux = arv->dir;
            free(arv);
            arv = aux;
        }else if(arv->dir == NULL)
        {
            PNoArvBin aux = arv->esq;
            free(arv);
            arv = aux;
        }else
        {
            PNoArvBin aux = arv->esq;
            while(aux->dir != NULL)
                aux = aux->dir;
            arv->info = aux->info;
            arv->esq = removeDaArv(arv->esq, aux->info.key);
        }
    }else if(key < arv->info.key)
    {
        arv->esq = removeDaArv(arv->esq, key);
    }else{
        arv->dir = removeDaArv(arv->dir, key);
    }

    short a = alturaDoNo(arv->esq); 
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    return arv;
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

short balanceamento(PNoArvBin no)
{
    if(no)
        return (alturaDoNo(no->esq) - alturaDoNo(no->dir));
    else
        return 0;
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

PNoArvBin insereNoArvAVL(PNoArvBin arv, TInfo info)
{
    if(arv == NULL){
        arv = newNoArvBin();
        arv->info = info;
    }else{
        if(info.key < arv->info.key){
            arv->esq = insereNoArvAVL(arv->esq, info);
        }else if (info.key > arv->info.key){
            arv->dir = insereNoArvAVL(arv->dir, info);
        }
    }
    short a = alturaDoNo(arv->esq);
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    arv = balanceia(arv);
    return arv;
}

