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

typedef struct{

    Jogos* lista;
    int capacidade;
    int tamanho;
    int isOrdenada;
} TListaLinear;

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

// Funções para carregamento de dados
Jogos* carregaDados( char *fileName, int *tam ); 
Jogos* criaAcervo( int capacidade ); 
void limpaAcervo( Jogos *acervo, int tamanhoAcervo ); 

// Funções para listas não ordenadas
int incRegistro( Jogos origem, Jogos* destino, int* tam ); 
int buscaPorId( int idDoApp, Jogos* lista, int tam ); 
int remRegistro( int idDoApp, Jogos* lista, int* tam ); 

// Funções para listas ordenadas
int buscaBinPorId(int idProcurado, Jogos* lista, int tam); 
int incOrdRegistro(Jogos jogo, Jogos* lista, int* tam); 
int remOrdRegistro(int idARemover, Jogos* lista, int* tam); 

// Funções genéricas para listas, sejam elas ordenadas ou não.
void inicializaListaLinear(TListaLinear* linear, int capacidade, int isOrdenada); 
TListaLinear* criaListaLinear(int capacidade, int isOrdenada); 
int buscaNaLista(int idProcurado, TListaLinear* linear);
int insereNaLista(Jogos jogo, TListaLinear* linear);
int isEmpty(TListaLinear* linear);
int removeDaLista(int idARemover, TListaLinear* linear);

// Funções para Filas Lineares
int insereNaFila(Jogos item, TFilaLinear* filaParametro);
int isFull(TFilaLinear* fila);
int emptyFila(TFilaLinear * fila);
Jogos* removeDaFila(TFilaLinear* fila);

// Funções para Pilhas Lineares
TPilhaLinear* iniciarPilha ();
int pilhaVazia(TPilhaLinear* pilha);
int pilhaCheia(TPilhaLinear* pilha);
int insereNaPilha(Jogos jogo, TPilhaLinear* pilha);
int removeDaPilha(TPilhaLinear* pilha);

#endif