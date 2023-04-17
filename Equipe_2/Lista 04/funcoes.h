#ifndef FUNCOES_H
#define FUNCOES_H

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

typedef struct {

    Jogos* pilha;
    int capacidade;   
    int topo;       
} TPilhaLinear;

typedef struct {

    Jogos* fila;    
    int capacidade;
    int inicio;
    int fim;
} TFilaLinear;

Jogos* carregaDados( char *fileName, int *tam ); 
Jogos* criaAcervo( int capacidade ); 

void limpaAcervo( Jogos *acervo, int tamanhoAcervo ); 

//Funções FILA
TFilaLinear* criaFilaLinear(int capacidade);
void inicializaFilaLinear(TFilaLinear *FilaLinear, int capacidade);
Jogos* removeDaFila(TFilaLinear* fila);
int insereNaFila(Jogos item, TFilaLinear* filaParametro);
int isFilaCheia(TFilaLinear* fila);
int isFilaVazia(TFilaLinear * fila);

//Funções PILHA
TPilhaLinear* criaPilhaLinear(int capacidade);
void inicializaPilhaLinear(TPilhaLinear *PilhaLinear, int capacidade);
int isPilhaVazia(TPilhaLinear* pilha);
int isPilhaCheia(TPilhaLinear* pilha);
int insereNaPilha(Jogos jogo, TPilhaLinear* pilha);
Jogos* removeDaPilha(TPilhaLinear* pilha);

#endif