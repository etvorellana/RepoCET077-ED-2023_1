#define CSVSIZE 12000
#define TRUE 1
#define FALSE 0

// Armazenando as informações de um libro de acordo com os campos de CSV
typedef struct
{
    int bookID;             // bookID - 1,
    char *title;            // title - Harry Potter and the Half-Blood Prince (Harry Potter  #6),
    char *authors;          // authors - J.K. Rowling/Mary GrandPré,
    float avgRating;        // average_rating - 4.57,
    char *isbn;          // isbn - 0439785960,
    char *isbn13;        // isbn13 - 9780439785969,
    char *lang;           // language_code - eng,
    int numPages;           // num_pages - 652,
    int ratCounts;          // ratings_count - 2095690,
    int txtRevCounts;       // text_reviews_count - 27591,
    char *pubDate;       // publication_date - 9/16/2006,
    char *publisher;        // publisher - Scholastic Inc.  
} TBook;


TBook* carregaDados(char *fileName, int *tam);
TBook* clonaBook(TBook book);
void cpyTBook(TBook src, TBook *dest);
void limpaAcervo(TBook *acervo, int tam);
void limpaRegistro(TBook book);
void limpaRegistro(TBook book);
void imprimeTBook(TBook book);
void impResumo(TBook book);
TBook* criaAcervo(int cap);

int buscaPorISBN(char *isbn, TBook* lista, int tam);
int incRegistro(TBook book, TBook* lista, int* tam);
int remRegistro(char* isbn, TBook* lista, int* tam);

int buscaOrdLinearPorISBN_(char *isbn, TBook* lista, int tam);
int buscaBinPorISBN(char *isbn, TBook* lista, int tam);
int incRegistroOrd(TBook book, TBook* lista, int* tam);
int remRegistroOrd(char* isbn, TBook* lista, int* tam);

/* 
    Classe para representar uma lista 
    * Lista linear -> lista de tamanho fixo
    * Lista cheia -> cap == tam
    * Lista vazia -> tam == 0
    * Lista ordenada -> eOrd == TRUE
        * Se lista for ordenada o tamanho do array é igual a cap
        * Se lista não for ordenada o tamanho do array é igual a cap + 1
*/
typedef struct
{
    TBook* lista;   //Array para os registros da lista
    int cap;        //Capacidade da lista
    int tam;        //Tamanho da lista
    int eOrd;       //TRUE se for ordenada 
} TListaLinear;

TListaLinear* criaListaLinear(int cap, int eOrd);
int buscaNaLista(char* isbn, TListaLinear* lista);
int insereNaLista(TBook book, TListaLinear* lista);
TBook* removeDaLista(char* isbn, TListaLinear* lista);

struct NoBookSE
{
    TBook book;
    struct NoBookSE *prox;
};

typedef struct NoBookSE TNoBookSE;
typedef TNoBookSE* PNoBookSE;

struct PilhaEnc
{
    PNoBookSE topo;
    int tam;
};

PilhaEnc* criaPilhaEnc();
int pilhaVazia(PilhaEnc* pilha);
int empilha(TBook book, PilhaEnc* pilha);
TBook desempilha(PilhaEnc* pilha);


struct FilaEnc
{
    PNoBookSE ini;
    PNoBookSE fim;
    int tam;
};

FilaEnc* criaFila();
int filaVazia(FilaEnc* fila);
int enfileira(TBook book, FilaEnc* fila);
TBook removeDaFila(FilaEnc* fila);

struct NoBookDE
{
    TBook book;
    struct NoBookDE *ant;
    struct NoBookDE *prox;
};

typedef struct NoBookDE TNoBookDE;
typedef TNoBookDE* PNoBookDE;





