#define CSVSIZE 8000
#define TRUE 1
#define FALSE 0
#define EX 100
#define N 16

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
    Tinfo info;
    int nivel;
    struct no *dir;
    struct no *esq;
}NoArv;

NoArv* newNoArvBin();
NoArv* inserir(NoArv *raiz, Tinfo info, int nivel); //cabeçalho da função para inserir elemento
void inserir_i(NoArv **raiz, Tinfo info, int nivel); //cabeçalho do procedimento para inserir
void imprimir(NoArv *arv, int tipo); //cabeçalho função para imprimir na tela a arvore
NoArv* buscaRec(NoArv *raiz, int key); //cabeçalho funçao de busca
NoArv* buscai(NoArv *raiz, int key); //cabeçalho função de buscai
NoArv* removeNoArv(NoArv *raiz, Tinfo info); //cabeçalho função de remover