#define CSVSIZE 13000

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

TSongs* carregaDados(char *filename, int *tam);
void limpaAcervo(TSongs *acervo, int tam);
void limpaRegistro(TSongs song); 
int BuscaPorRank(int R, TSongs *lista, int tam);
int IncRegistro(TSongs song, TSongs *lista, int *tam);
int RemRegistro(TSongs song, TSongs *lista, int *tamaux);
int RemRegistro_nao_ordenado(TSongs song, TSongs *lista, int *tamaux);
int busca_binaria(TSongs *lista, int tamanho, int item);
int buscaBinporPOSICAOi(int position, TSongs* lista, int tam);
int buscaBinporPOSICAO(int position, TSongs *lista, int tam, int *existe);
int IncRegistroOrd(TSongs song, TSongs *lista, int *tamaux);
int RemRegistroOrd(TSongs song, TSongs *lista, int *tamaux);
int RemRegistro_ordenado(TSongs song, TSongs *lista, int *tamaux);
TListaLinear* criaListaLinear(int cap, int eOrd);
int insereNaLista(TSongs song, TListaLinear* listaLinear);
TSongs* removeDaLista(TSongs song, TListaLinear* listaLinear);
int buscaNaLista(TSongs song, TListaLinear* listaLinear);