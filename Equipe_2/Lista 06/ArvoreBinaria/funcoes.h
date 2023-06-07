#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {

    int appId;
    char *title;
    char *dataRelease;
    char *win;
    char *mac;
    char *LINUX;
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
PNoArvBin insereNoArvBin(PNoArvBin arv, Jogos jogo);
PNoArvBin removeDaArvAVL(PNoArvBin arv, int key);
PNoArvBin buscaNaArvAVL(PNoArvBin arv, int key);

short int alturaDoNo(PNoArvBin arv);
PNoArvBin balanceia(PNoArvBin arv);
short balanceamento(PNoArvBin no);
PNoArvBin rotacaoDirEsq(PNoArvBin arv);
PNoArvBin rotacaoEsqDir(PNoArvBin arv);
PNoArvBin rotacaoEsq(PNoArvBin arv);
PNoArvBin rotacaoDir(PNoArvBin arv);
void printArv(PNoArvBin arv, int tipo) ;

#endif