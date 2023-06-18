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


typedef struct
{
   Games* pilha;   
    int cap;       
    int topo;       
}TPilhaLinear;



typedef struct
{
    Games* fila;    
    int cap;       
    int ini;        
    int fim;        
} TFilaLinear;


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
int buscaPorId(int ID, Games* lista, int tam);

TPilhaLinear* criaPilhaLinear(int cap);
int insereNaPilha(Games jogo, TPilhaLinear* pilha);
Games* removeDaPilha(TPilhaLinear* pilha);
void demonstrar_add_pilha(int try1,int ok,TPilhaLinear *pilha);
void demonstrar_rem_pilha(TPilhaLinear *pilha);


TFilaLinear* criaFilaLinear(int cap);
int insereNaFila(Games jogo, TFilaLinear* fila);
Games* removeDaFila(TFilaLinear* fila);
void demonstrar_add_fila(int try1,int ok,TFilaLinear *fila);
void demonstrar_rem_fila(TFilaLinear *fila);


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
int insereNaFilaEnc(Games jogo,TFilaEnc *fila);
Games* removeDaFilaEnc(TFilaEnc *fila);
void imprimFila(TFilaEnc *Fila);