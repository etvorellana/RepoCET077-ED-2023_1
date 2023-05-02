#define CSVSIZE 13000
#define TRUE 1
#define FALSE 0
#define EX 100

typedef struct {
  int Position;
  long long int Key;
  char *ArtistName;
  char *SongName;
  int Days;
  float Top10Times;
  int PeakPosition;
  char *PeakPositionXtimes;
  int PeakStreams;
  int TotalStreams;
} TSongs;

typedef struct {
  TSongs* lista;    
  int cap;        
  int tam;        
  int eOrd;        
} TListaLinear;

typedef struct {
  TSongs* pilha;   
  int cap;        
  int topo;       
} TPilhaLinear;

typedef struct {
  TSongs* fila;    
  int cap;        
  int ini;        
  int fim;        
} TFilaLinear;

typedef struct no{
  TSongs song;
  struct no *proximo;
}No;

typedef struct {
  No *topo;
  int tam;
}Tpilha;

typedef struct {
  No *inicio;
  No *fim;
  int tam;
}Tfila;

// Principal
TSongs* carregaDados(char *filename, int *tam);
void limpaAcervo(TSongs *acervo, int tam);
void limpaRegistro(TSongs song); 

// ---------
int BuscaPorRank(int R, TSongs *lista, int tam);
int RemRegistro(TSongs song, TSongs *lista, int *tamaux);
int busca_binaria(TSongs *lista, int tamanho, int item);
int buscaBinporPOSICAOi(int position, TSongs* lista, int tam);
int buscaBinporPOSICAO(int position, TSongs *lista, int tam, int *existe);
int RemRegistro_ordenado(TSongs song, TSongs *lista, int *tamaux);

// Lista
TListaLinear* criaListaLinear(int cap, int eOrd);
int IncRegistroOrd(TSongs song, TSongs *lista, int *tamaux, int pos);
int IncRegistro(TSongs song, TSongs *lista, int *tamaux, int pos);
int insereNaLista(TSongs song, TListaLinear* listaLinear);
TSongs* RemRegistroOrd(TSongs song, TSongs *lista, int *tamaux, int pos);
TSongs* RemRegistro_nao_ordenado(TSongs song, TSongs *lista, int *tamaux, int pos);
TSongs* removeDaLista(TSongs song, TListaLinear* listaLinear);
int buscaNaLista(TSongs song, TListaLinear* listaLinear);
int menu(void);
TSongs* removeDaLista(TSongs song, TListaLinear* listaLinear);
int buscaNaLista(TSongs song, TListaLinear* listaLinear);
int menu(void);

// Pilha
TPilhaLinear* criaPilhaLinear(int cap);
int inicioPilhalinear(TPilhaLinear *pilha, int cap);
int pushTSongs(TSongs song, TPilhaLinear *pilha);
int popTSongs(TPilhaLinear *pilha);
// Fila
TFilaLinear* criaFila(int cap);
int enqueue(TSongs song, TFilaLinear *fila);
TSongs* dequeue(TFilaLinear *fila); 

//listas encadeadas

//pilha
int cpyTsong(TSongs song, TSongs *end);
int cria_pilha(Tpilha *p);
int empilhaEnc(TSongs song, Tpilha *p);
No* desempilhaEnc(Tpilha *p);
void printPilhaEnc(Tpilha *p);

//fila
int cria_fila(Tfila *f);
int insere_fila(TSongs song, Tfila *f);
No *remove_fila(Tfila *f);
void print_fila(Tfila *f);

//menu
void menu_lista5(TSongs *acervo, TListaLinear *l, Tpilha *p, Tfila *f, int *tam);