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
    short altura;
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
short alturaNo(NoArv *raiz); //cabeçalho função altura
short maior(short esq, short dir); //cabeçalho função que retorna a maior altura das duas subarvores
short alturaNoArv(NoArv *no); //cabeçalho retorna altura do no
short balanceamento(NoArv *no); //cabeçalho função que retorna o fator de balanceamento
NoArv* rotacaoEsquerda(NoArv *raiz); //rotação a esquerda
NoArv* rotacaoDireita(NoArv *raiz); //rotação a direita
NoArv* rotacaoDirEsq(NoArv *raiz); //rotação direita esquerda
NoArv* rotacaoEsqDir(NoArv *raiz); //rotação esquerda direita
NoArv* balancear(NoArv *raiz); //balancear a arvore
NoArv* inserir_AVL(NoArv *raiz, TSongs song); //inserir balanceada
NoArv* removeNoArv_AVL(NoArv *raiz, TSongs song); //remove balanceado
void menu();

//Manipular TSongs
TSongs *carregaDados(char *fileName, int *tam);
void limpaAcervo(TSongs *acervo, int tam);
void limpaRegistro(TSongs song);
TSongs* cpyTsong(TSongs song, TSongs *end);