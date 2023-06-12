#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

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
PNoArvBin removeDaArvAVL(PNoArvBin arv, int jogo);
PNoArvBin buscaNaArvAVL(PNoArvBin arv, int key);
short int alturaDoNo(PNoArvBin arv);
PNoArvBin balanceia(PNoArvBin arv);
short balanceamento(PNoArvBin no);
PNoArvBin rotacaoDirEsq(PNoArvBin arv);
PNoArvBin rotacaoEsqDir(PNoArvBin arv);
PNoArvBin rotacaoEsq(PNoArvBin arv);
PNoArvBin rotacaoDir(PNoArvBin arv);
void printArv(PNoArvBin arv, int tipo);
void cpy( Jogos origem, Jogos* destino); 
void limpaRegistro(Jogos *jogo);
int percorre(PNoArvBin arv) ;


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
    PNoArvBin arv = malloc(sizeof(PNoArvBin));
    arv->dir = NULL;
    arv->esq = NULL;
    arv->altura = 0;
    return arv;
}


PNoArvBin insereNoArvAVL(PNoArvBin arv, Jogos jogo){
    if(arv == NULL)
    {
        arv = newNoArvBin();
        cpy(jogo, arv->jogo);
    }
    else if(jogo.appId < arv->jogo->appId)
    {
        arv->esq = insereNoArvAVL(arv->esq, jogo);
    }
    else if (jogo.appId > arv->jogo->appId)
    {
        arv->dir = insereNoArvAVL(arv->dir, jogo);
    }
    short a = alturaDoNo(arv->esq); 
    short b = alturaDoNo(arv->dir);
    arv->altura = ((a > b) ? a : b) + 1;
    arv = balanceia(arv);
    return arv;
}

PNoArvBin removeDaArvAVL(PNoArvBin arv, int key) {
    if(arv == NULL)
    {
        return NULL;
    }else if(arv->jogo->appId == key)
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
            limpaRegistro(arv->jogo);
            free(arv);
            arv = aux;
        }else
        {
            PNoArvBin aux = arv->esq;
            while(aux->dir != NULL){
                aux = aux->dir;
            }
            arv->jogo = aux->jogo;
            arv->esq = removeDaArvAVL(arv->esq, aux->jogo->appId);
        }
    }else if(key < arv->jogo->appId)
    {
        arv->esq = removeDaArvAVL(arv->esq, key);
    }else{
        arv->dir = removeDaArvAVL(arv->dir, key);
    }
    
    // Atualiza a altura do nó e realiza o balanceamento
    short int a = alturaDoNo(arv->esq);
    short int b = alturaDoNo(arv->dir);

    arv->altura = ((a > b) ? a : b) + 1;
    arv = balanceia(arv);
    return arv;
}


void limpaRegistro(Jogos *jogo) {

    free((*jogo).title);
    free((*jogo).dataRelease);
    free((*jogo).win);
    free((*jogo).mac);
    free((*jogo).linux);
    free((*jogo).rating);
}

PNoArvBin buscaNaArvAVL(PNoArvBin arv, int key){
    if(arv == NULL)
    {
        return NULL;
    }
    else if(arv->jogo->appId == key)
    {
        return arv;
    }
    else if(key < arv->jogo->appId)
    {
        return buscaNaArvAVL(arv->esq, key);
    }
    else
    {
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

void cpy(Jogos origem, Jogos* destino) {

    (*destino).appId = origem.appId;

    (*destino).title  = (char*)malloc((strlen(origem.title)));
    strcpy((*destino).title, origem.title); 

    (*destino).dataRelease  = (char*)malloc(strlen(origem.dataRelease));
    strcpy((*destino).dataRelease, origem.dataRelease);
    
    (*destino).win  = (char*)malloc(strlen(origem.win));
    strcpy((*destino).win, origem.win);

    (*destino).mac  = (char*)malloc(strlen(origem.mac));
    strcpy((*destino).mac, origem.mac);

    (*destino).linux  = (char*)malloc(strlen(origem.linux));
    strcpy((*destino).linux, origem.linux);

    (*destino).rating  = (char*)malloc(strlen(origem.rating));
    strcpy((*destino).rating, origem.rating);

    (*destino).positiveRatio = origem.positiveRatio;
    (*destino).userReviews = origem.userReviews;
    (*destino).priceFinal = origem.priceFinal;
    (*destino).priceOriginal = origem.priceOriginal;
    (*destino).discount = origem.discount;   

}

void printArv(PNoArvBin arv, int tipo) {
    if (arv != NULL) {
        if (tipo == 0) {
            printArv(arv->esq, tipo);
            printf("(%d, %s, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
            printArv(arv->dir, tipo);
        } else if (tipo == 1) {
            printf("(%d, %s, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
        } else if (tipo == 2) {
            printArv(arv->esq, tipo);
            printArv(arv->dir, tipo);
            printf("(%d, %s, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
        } else {
            printArv(arv->dir, tipo);
            printf("(%d, %s, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
            printArv(arv->esq, tipo);
        }
    }
}

int percorre(PNoArvBin arv) {
    int contador = 0;
    if (arv != NULL) {
        percorre(arv->dir);
        printf("(%d, %s, %d)  ", arv->jogo->appId, arv->jogo->title, arv->altura);
        contador++;
        percorre(arv->esq);
    }
    return contador;
}

//---------------------------------------------------- MAIN -------------------------------------------------------------------

int main(void)
{
    Jogos *acervo;
    int tamanhoAcervo = 16;
    PNoArvBin arvAVL = NULL;
    
    acervo = carregaDados("../../../Data/dataSetEquipe2.csv", &tamanhoAcervo );

    printf("\n-------------------------- INSERINDO NA AVL -------------------------------------\n");

    /*arvAVL = insereNoArvAVL(arvAVL, acervo[5]);
    printf("\n %s", arvAVL);*/

    int inseriu = 0;
    for(int i = 0; i < N; i++){
        if(buscaNaArvAVL(arvAVL, acervo[i].appId)){
            printf("\nElemento %d não pode ser inserido\n!", acervo[i].appId);
        }else{
            arvAVL = insereNoArvAVL(arvAVL, acervo[i]);
        }
        if(percorre(arvAVL) == i + 1){  
            printf("\nElemento %d foi inserido\n!", acervo[i].appId);
            inseriu++;
        }
    }

    if(percorre(arvAVL) == inseriu){
        printf("Todos os elementos foram inseridos!\n");
    }else{
        printf("Nem todos os elementos foram inseridos!\n");
    }

    printArv(arvAVL, 0);
    printf("\n");
    printf("------------------\n");
    printArv(arvAVL, 1);
    printf("\n");
    printf("------------------\n");
    printArv(arvAVL, 2);
    printf("\n");
    printf("------------------\n");
    printArv(arvAVL, 3);
    printf("\n");
    printf("------------------\n");

    printf("\n----------------------------- REMOVENDO DA AVL --------------------------------\n");

    int removeu = 0;
    for (int i = 0; i < N; i++){

        if(arvAVL == NULL){
            printf("\n Não há elementos para remover!\n");
        }else{
            arvAVL = removeDaArvAVL(arvAVL, acervo[i].appId);
            if(!buscaNaArvAVL(arvAVL, acervo[i].appId)){
            printf("\n Elemento %d foi removido!\n", acervo[i].appId);
            removeu++;
            
            printArv(arvAVL, 0);
            printf("\n");
            printf("------------------\n");
            }
        }
    }

    if(percorre(arvAVL) == removeu){
        printf("Todos os elementos foram removidos!");
    }else{
        printf("Nem todos os elementos foram removidos!\n");
    }
    
    return 0;
}

