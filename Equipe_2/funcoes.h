#define CSVSIZE 46068

typedef struct {

    int appId;
    char *title;
    char *dataRelease;
    char *win;
    char *mac;
    char *linux;
    char *rating;
    int positiveRatio;
    int userReviews;
    float priceFinal;
    float priceOriginal;
    float discount;
    char *steamDeck;

} Jogos;

Jogos* carregaDados( char *fileName, int *tam );
Jogos* criaAcervo( int capacidade );
void limpaAcervo( Jogos *acervo, int tam );
void imprimeOsDados( Jogos *lista, int i );
int buscaPorId( int idDoApp, Jogos* lista, int tam );
int incRegistro( Jogos origem, Jogos* destino, int* tam );
int remRegistro( int idDoApp, Jogos* lista, int* tam );
int verificaExistencia( Jogos* subColecao, int idDoApp, int tam );