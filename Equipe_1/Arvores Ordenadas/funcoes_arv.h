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

struct noArvBin{
  Games jogo;
  short int altura;
  struct noArvBin *esq;
  struct noArvBin *dir;
};

typedef struct noArvBin noArvBin;

//da lista
Games* carregaDados(char *fileName, int *tam);

Games* IniciaLista(int capacidade);

void cpyGame(Games jogo, Games* jogo_copia);

void limpaJogo(Games *jogo);

void primeiras_letras(char *nome);

// arvore
noArvBin* newNoArvBin();

noArvBin* insereNoArvBin(noArvBin* arv, Games jogo);

short int alturaDoNo(noArvBin* arv);

void printArv(noArvBin* arv, int tipo);

void printArv2(noArvBin* arv, noArvBin* arvAVL, int distancia);

noArvBin* removeDaArv(noArvBin* arv, int ID);

noArvBin* buscaNaArv(noArvBin *arv, int ID);

// arvore AVL
noArvBin* insereNoArvAVL(noArvBin *arv, Games jogo);

noArvBin* removeDaArvAVL(noArvBin *arv, int ID);

noArvBin* rotacaoDir(noArvBin *arv);

noArvBin* rotacaoEsq(noArvBin *arv);

noArvBin* rotacaoDirEsq(noArvBin *arv);

noArvBin* rotacaoEsqDir(noArvBin *arv);

short balanceamento(noArvBin *no);

noArvBin* balanceia(noArvBin *arv);