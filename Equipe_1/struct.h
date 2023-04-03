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

Games* IniciaLista(int capacidade);
int buscaPorId(int ID, Games* lista, int *tam);

typedef struct linear{
    int tam;
    int cap;
    int ordenada;
    Games *jogos;
}Tlinear;

