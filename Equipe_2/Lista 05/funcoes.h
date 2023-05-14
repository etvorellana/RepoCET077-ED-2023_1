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

typedef struct ElementoPilha{

    Jogos* jogo;
    struct ElementoPilha *prox;

} ElementoPilha;

typedef struct Pilha{

    ElementoPilha *topo;
    int tam;

} Pilha;

typedef struct ElementoFila{

    Jogos* jogo;
    struct ElementoFila* prox;

} ElementoFila;

typedef struct Fila{

    struct ElementoFila *inicio;
    struct ElementoFila *fim;

} Fila;

typedef struct ElementoEncadeado{

    Jogos* jogo;
    struct ElementoEncadeado* prox;

} ElementoEncadeado;

typedef struct Encadeado{

    ElementoEncadeado *topo;
    int tam;

} Encadeado;

Jogos* carregaDados( char *fileName, int *tam ); 
Jogos* criaAcervo( int capacidade ); 

//Funções - PILHA
Pilha* inicializaPilha();
int isPilhaVazia(Pilha *pilha);
int isPilhaCheia( Pilha* pilha );
void imprimePilha(Pilha *pilha);
void imprimeElementoPilha( Pilha *pilha );
int empilhar(Jogos* jogo, Pilha *pilha);
Jogos* desempilha(Pilha *pilha);

//Funções - FILA
Fila* inicializaFila();
int insereNaFila(Jogos* jogo, Fila* fila);
Jogos* removeDaFila(Fila* fila);
int isFilaVazia(Fila* fila);
void imprimeElementoFila( Fila *fila );

//Funções - LISTA
int insereEncadeado(Jogos* jogo, Encadeado* listaEncadeada);
Jogos* removeEncadeado( Encadeado* listaEncadeada );
Encadeado* inicializaListaEncadeada();
void imprimeElementoListaEncadeada( Encadeado* listaEncadeada );
void imprimeUltimoElementoListaEncadeada( Encadeado *listaEncadeada );

#endif