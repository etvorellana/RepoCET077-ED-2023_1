#define CSVSIZE 8000
#define TRUE 1
#define FALSE 0
#define EX 100
#define N 16

//TSongs
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

//Tinfo
typedef struct 
{
    int key;
    float value;
}Tinfo;

typedef Tinfo *PInfo;

//estrutura para montar a arvore
typedef struct no
{
    TSongs *song;
    int altura;
    struct no *dir;
    struct no *esq;
}NoArv;

NoArv* newNoArvBin();
NoArv* inserir(NoArv *raiz, TSongs song); //cabeçalho da função para inserir elemento
void inserir_i(NoArv **raiz, TSongs song); //cabeçalho do procedimento para inserir
void imprimir(NoArv *arv, int tipo); //cabeçalho função para imprimir na tela a arvore
NoArv* buscaRec(NoArv *raiz, int key); //cabeçalho funçao de busca
NoArv* buscai(NoArv *raiz, int key); //cabeçalho função de buscai
NoArv* removeNoArv(NoArv *raiz, TSongs song); //cabeçalho função de remover
int alturaNo(NoArv *raiz); //cabeçalho função altura
void menu();

//Manipular TSongs
TSongs *carregaDados(char *fileName, int *tam);
void limpaAcervo(TSongs *acervo, int tam);
void limpaRegistro(TSongs song);
TSongs* cpyTsong(TSongs song, TSongs *end);