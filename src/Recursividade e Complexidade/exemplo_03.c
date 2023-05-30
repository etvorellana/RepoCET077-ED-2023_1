#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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

int buscaOrdPorISBN(char *isbn, TBook* lista, int tam)
{
    int i = 0;
    while(strcmp(isbn, lista[i].isbn) < 0)
        i++;
    if (strcmp(isbn, lista[i].isbn) == 0)
        return i;
    else
        return -1 - i;
}



void mi(unsigned char* img, int n, int m)
{
    for(int i = 0; i < n; i++)
        zeta(&img[i*m], m);
}

struct NoBookSE
{
    TBook book;
    struct NoBookSE *prox;
};

typedef struct NoBookSE TNoBookSE;
typedef TNoBookSE* PNoBookSE;

typedef struct
{
    PNoBookSE ini;
    PNoBookSE fim;
    int tam;
} FilaEnc;

int filaVazia(FilaEnc* fila)
{
    return (fila->ini == NULL);
    //return (fila->tam == 0);
}

int enfileira(TBook book, FilaEnc* fila)
{
    PNoBookSE p = alocaNoBookSE();
    cpyTBook(book, &p->book);
    p->prox = NULL;
    if (filaVazia(fila))
    {
        fila->ini = p;
        fila->fim = p;
    }
    else
    {
        fila->fim->prox = p;
        fila->fim = p;
    }
    fila->tam++;
    return TRUE;
}

TBook* removeDaFila(FilaEnc* fila)
{
    TBook* book = NULL;
    if (filaVazia(fila))
        return NULL;
    else{
        PNoBookSE p = fila->ini;
        fila->ini = p->prox;
        fila->tam--;
        book = (TBook*) malloc(sizeof(TBook));
        cpyTBook(p->book, book);
        free(p);
        return book;
    }
}









//-----------------------
void alpha(unsigned char* img, int n, int m)
{
    int nm = n*m;
    for(int i0 = 0, im = m; i0 < nm; i0 += m, im += m)
        for(int ij = i0; ij < im; ij++)
            img[ij] = (unsigned char) (rand()%256);
}

void beta(unsigned char* img, int n, int m, int lim)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            img[i*m + j] /= lim;
            img[i*m + j] *= 255;
        }
}

void gamma(unsigned char* img, int n)
{
    if(n == 0)
        return;
    else{
        img[0] = (unsigned char) (rand()%256); 
        gamma(&img[1], n-1);
    }
}

void delta(unsigned char* img, int n)
{
    if(n == 0)
        return;
    else{
        img[--n] = (unsigned char) (rand()%256); 
        delta(img, n);
    }
}

void epsilon(unsigned char* img, int n, int lim){
    for(int i = 0; i < n; i++){
        img[i] /= lim;
        img[i] *= 255;
    }
}

void zeta(unsigned char* img, int n)
{
    for(int i = 0; i < n; i++)
        img[i] = (unsigned char) (rand()%256);
}

void eta(unsigned char* img, int n, int m)
{
    if(n == 0)
        return;
    else{
        delta(img, m);
        eta(&img[m], n-1, m);
    }
}

void teta(unsigned char* img, int n, int m)
{
    int nm = n*m;
    for(int i = 0; i < nm; i++)
        img[i] = (unsigned char) (rand()%256);
}

void iota(unsigned char* img, int n, int m, int lim){
    epsilon(img, n*m, lim);
}

void capa(unsigned char* img, int n, int m, int lim){
    lambda(img, n*m, lim);
}

void lambda(unsigned char* img, int n, int lim){
    if (n == 0)
        return;    
    else{
        img[--n] /= lim;
        img[n] *= 255;
        func_LimLin(img, n, lim);
    }
}


int buscaOrdPorISBN(char *isbn, TBook* lista, int tam)
{
    int i = 0;
    while(strcmp(isbn, lista[i].isbn) < 0)
        i++;
    if (strcmp(isbn, lista[i].isbn) == 0)
        return i;
    else
        return -i;
}