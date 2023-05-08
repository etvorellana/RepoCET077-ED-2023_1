#define CSVSIZE 17000
typedef struct{
    int ID;
    char *Name;
    char *Platform;
    int Year_Of_Release;
    char *Genre;
    char *Publisher;
    float NA_Sales;
    float EU_Sales;
    float JP_sales;
    float Other_Sales;
    float Global_Sales;   
}Games;

struct No{
  Games jogo;
  struct No *prox;
};
typedef struct  No No;

struct TListaEnc{
  No* ini;
  No* fim;
  int tam;
};

typedef  struct TListaEnc TListaEnc;

struct TPilhaEnc{
   No* topo;
   int tam;
};
typedef struct TPilhaEnc TPilhaEnc;

struct TFilaEnc{
  No* ini;
  No* fim;
  int tam;
};
typedef struct TFilaEnc TFilaEnc;

Games* carregaDados(char *fileName, int *tam);

Games* IniciaLista(int capacidade);

void limpaJogos(Games *jogos, int tam);

void limpaJogos02(Games *jogos, int Pos);

void limpaJogos03(Games *jogo);

No* AlocaNo();

No* CriaListaENdeListaLinear(Games *jogos, int tam);
No* FimDaListaEN(No* ini);
void ExcluirNo(No** p);
void imprimirNo(No*p);
Games CopyGames(Games jogo);

TListaEnc *iniListaEnc();
int insereNoFimListaEnc(Games jogo,TListaEnc *lista);
Games* removeDoIniListaEnc(TListaEnc *lista);


TPilhaEnc* iniPilhaEnc();
int empilhar(Games jogo, TPilhaEnc *pilha);
Games* desempilhar(TPilhaEnc *pilha);
void imprimePilha(TPilhaEnc *pilha);


TFilaEnc* iniFilaEnc();
int insereNaFila(Games jogo,TFilaEnc *fila);
Games* removeDaFila(TFilaEnc *fila);
void imprimFila(TFilaEnc *Fila);