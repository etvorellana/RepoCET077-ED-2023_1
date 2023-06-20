#define CSVSIZE 17000
typedef struct
{
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
} Games;

typedef struct
{
    int capacidade;
    int tam;
    Games *Lista;
    int eOrdenada;

} Tlista;

typedef struct
{
    Games *pilha;
    int cap;
    int topo;
} TPilhaLinear;

typedef struct
{
    Games *fila;
    int cap;
    int ini;
    int fim;
} TFilaLinear;

//Funções para o Dataset

Games *carregaDados(char *fileName, int *tam);
Games *IniciaLista(int capacidade);
void limpaJogos(Games *jogos, int tam);
void limpaJogos02(Games *jogos, int Pos);
void limpaJogos03(Games *jogo);

//Funções para listas não ordenadas

int buscaPorId(int ID, Games *lista, int tam);
Games CopyGames(Games jogo);
int incJogo(Games jogos, Games *jogos02, int *tam);
int remJogo(Games jogo, Games *jogos02, int *tam);

//Funções para listas ordenadas

int buscaBinPorId(int ID, Games *lista, int tamanho);
int remJogoOrdenado(Games jogo, Games *jogos03, int *tam);
int incJogoOrdenado(Games jogo, Games *jogos03, int *tam);
int buscaBinRecPorId(int ID, Games *lista, int ini, int fim);
Tlista criaListaLinear(int cap, int eOrd);

//Funções gerais de lista

int Busca_Geral(int ID, Tlista l);
int Inc_Geral(Games jogo, Tlista *l);
int Rem_Geral(Games jogo, Tlista *l);
