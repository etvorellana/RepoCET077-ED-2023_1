#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    int key;
    char *str;
    float val;
}TInfo;

typedef TInfo *PInfo;

struct noArvBin{
    TInfo info;
    struct noArvBin *esq;
    struct noArvBin *dir;
    int niv; //nível do no
    int prf; // profundidade do no
    int alt; // altura do nó
};

typedef struct noArvBin TNoArvBin;
typedef TNoArvBin *PNoArvBin;

PNoArvBin iniArvBin(TInfo info);
void geraInfo(TInfo *info);
PNoArvBin incArvBin(TInfo info, PNoArvBin raiz);

int main(void)
{
    char arvRep[5][65];
    //inicializando a representação
    
    int i, j;
    int pos; 
    TInfo info;
    PNoArvBin raizArv = NULL;
    

    

    for(i = 0; i < 5; i++)
        printf("%s\n\n", arvRep[i]);


    geraInfo(&info);
    incArvBin(info, raizArv);

    
    return 0;
}

void arv2mat(char **arvRep, PNoArvBin raiz)
{
       
    
}

void clearMat(char **arvRep)
{
    int step = 64;
    int i, j, pos;
    for(i = 0; i < 5; i++)
        for(j = 0; j < 65; j++)        
            arvRep[i][j] = ' ';
    for(i = 0; i < 5; i++)
    {
        pos = step/2;
        while (pos < 64)
        {
            arvRep[i][pos-2] = '[';
            arvRep[i][pos+1] = ']';
            pos += step;
        }
        step /= 2;
        arvRep[i][64] = '\0';
    }
}

PNoArvBin iniArvBin(TInfo info)
{
    PNoArvBin no = (PNoArvBin) malloc(sizeof(TNoArvBin));
    no->info = info;
    no->esq = NULL;
    no->dir = NULL;
    no->niv = 0;
    no-> prf = 0;
    no->alt = 0;
}

void geraInfo(TInfo *info)
{   
    int strSize = (10+rand(5));
    int i = 0;
    int dif = 'z' - 'a' + 1;
    info->key = rand()%100;
    info->str = (char*) malloc(sizeof(char)*(strSize+1));
    info->str[strSize] = '\0';
    for(i = 0; i < strSize; i++)
        info->str[i] = 'a' + rand()%dif;
    info->str[0] = toupper(info->str[0]);
    info->val = rand();
    info->val /= RAND_MAX;
    info->val *= 100; 
    return;
}


/*
    - alt: A altura de um nó é o comprimento do caminho mais longo entre ele e 
    uma folha;
    - prf: A profundidade de um nó é a distância percorrida deste nó até a 
    raiz;
    - niv: O Nível de um nó é o número de nós do caminho da raiz até o nó;
*/
PNoArvBin incArvBin(TInfo info, PNoArvBin raiz)
{
    int niv, alt, prf;
    niv = prf = alt = 0;
    if(raiz == NULL)
    {
        raiz = iniArvBin(info);
        raiz->info = info;
    }
    else
    {   
        PNoArvBin subArv, prox = raiz;
        int dir;
        do
        {
            subArv = prox;
            if(subArv->info.key == info.key)
                return raiz;  // não pode ter nos com a mesma chave
            dir = rand()%2; // escolha uma direção
            if (dir) //dir == 1 or dir = TRUE 
                prox = subArv->dir;
            else
                prox = subArv->esq;
            niv++;
        }while(prox != NULL);
        if(dir)
        {
            subArv->dir = iniArvBin(info);
            subArv->dir->info = info;
            subArv->dir->niv = niv;
        }
        else
        {
            subArv->esq = iniArvBin(info);
            subArv->esq->info = info;
            subArv->esq->niv = niv;
        }
    }
    return raiz;
}