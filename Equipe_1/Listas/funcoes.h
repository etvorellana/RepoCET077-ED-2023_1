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

typedef struct{
    int capacidade;
    int tam;
    Games *Lista;
    int eOrdenada;
    
}Tlista;



Games* carregaDados(char *fileName, int *tam);
Games* IniciaLista(int capacidade);
void limpaJogos(Games *jogos, int tam);
void limpaJogos02(Games *jogos, int Pos);
void limpaJogos03(Games *jogo);

//Listas Não Ordenadas
int buscaPorId(int ID, Games* lista, int tam);
int remJogo(Games jogo, Games* jogos02, int* tam);
int incJogo(Games jogos, Games* jogos02, int* tam);


//Listas Ordenadas
int buscaBinRecPorId(int ID, Games *lista, int ini, int fim);
int remJogoOrdenado(Games jogo, Games* jogos03, int* tam);
int incJogoOrdenado(Games jogo, Games* jogos03, int* tam)
Games CopyGames(Games jogo);  
Tlista criaListaLinear(int cap, int eOrd);


//Listas Ordenadas ou Não Ordenadas
int Busca_Geral(int ID, Tlista l);
int Inc_Geral(Games jogo, Tlista *l);
int Rem_Geral(Games jogo, Tlista *l);
