#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    int appId;
    char *title;
    char *dataRelease;
    char *win;
    char *mac;
    char *linux;
    char *rating;
    int positiveRatio;
    int userReviews;
    float priceFinal;
    float priceOriginal;
    float discount;

} Jogos;

typedef struct noArvBin{
    //estrutura da arvore
    Jogos *jogo;
    short int altura;
    struct noArvBin *esq;
    struct noArvBin *dir;
}NoArv;

typedef NoArv *PNoArvBin;

//manipulando jogos
Jogos* carregaDados( char *fileName, int *tam ); 
Jogos* criaAcervo( int capacidade ); 

PNoArvBin newNoArvBin();
PNoArvBin insereNoArvAVL(PNoArvBin arv, Jogos jogo);
PNoArvBin removeDaArvAVL(PNoArvBin arv, int key);
PNoArvBin buscaNaArvAVL(PNoArvBin arv, int key);
short int alturaDoNo(PNoArvBin arv);
PNoArvBin balanceia(PNoArvBin arv);
short balanceamento(PNoArvBin no);
PNoArvBin rotacaoDirEsq(PNoArvBin arv);
PNoArvBin rotacaoEsqDir(PNoArvBin arv);
PNoArvBin rotacaoEsq(PNoArvBin arv);
PNoArvBin rotacaoDir(PNoArvBin arv);
void printArv(PNoArvBin arv);
int incRegistro( Jogos origem, Jogos* destino, int tam ); 


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

    while (!feof(fp) && i < tam)
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
        return buscaNaArvAVL(arv->esq, key);
    }else{
        return buscaNaArvAVL(arv->dir, key);
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

int incRegistro(Jogos origem, Jogos* destino, int tam) {
    
        destino[tam].title  = (char*)malloc((strlen(origem.title)));
        strcpy(destino[tam].title, origem.title); 
        
        destino[tam].dataRelease  = (char*)malloc(strlen(origem.dataRelease));
        strcpy(destino[tam].dataRelease, origem.dataRelease);
        
        destino[tam].win  = (char*)malloc(strlen(origem.win));
        strcpy(destino[tam].win, origem.win);

        destino[tam].mac  = (char*)malloc(strlen(origem.mac));
        strcpy(destino[tam].mac, origem.mac);

        destino[tam].linux  = (char*)malloc(strlen(origem.linux));
        strcpy(destino[tam].linux, origem.linux);

        destino[tam].rating  = (char*)malloc(strlen(origem.rating));
        strcpy(destino[tam].rating, origem.rating);

        destino[tam].positiveRatio = origem.positiveRatio;
        destino[tam].userReviews = origem.userReviews;
        destino[tam].priceFinal = origem.priceFinal;
        destino[tam].priceOriginal = origem.priceOriginal;
        destino[tam].discount = origem.discount;

        return 1;
}
void printArv(PNoArvBin arv)
{
    if(arv != NULL)
    {
        printArv(arv->esq);
        printf("(%d, %s , %d)", arv->jogo->appId, arv->jogo->title, arv->altura);
        printArv(arv->dir);
    }      

    printf("arvore vazia");
}

int main() {

    Jogos *acervo;
    int n = 16;
    //Carregando dados para o acervo
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &n );
    
    Jogos *lista = malloc(n * sizeof(Jogos));
    
    for( int tam = 0; tam < n; tam++) {
        incRegistro( acervo[tam], lista, tam ); 
    }
    
    PNoArvBin arv = NULL;
    for(int i = 0; i < n; i++)
    {   //insereNoArvAVL(PNoArvBin arv, Jogos jogo)
        arv = insereNoArvAVL(arv, lista[i]);
    }

    printArv(arv);

    return 0;

    /*
    PNoArvBin arvore = NULL;

    // Inserção dos nós na árvore AVL
    for (int i = 0; i < tam; i++)
        arvore = insereNoArvAVL(arvore, dados[i]);
*/
}