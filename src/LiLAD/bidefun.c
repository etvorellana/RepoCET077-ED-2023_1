// Biblioteca de funções

#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()
 
#include "bidefun.h"

TBook* carregaDados(char *fileName, int *tam)
{
    TBook *acervo;
    FILE *fp;
    char str[900];  // para ler uma linha do arquivo
    int i = 0;
    
    // Vamos abrir um arquivo para leitura e verificar se foi tudo bem
    if(fp == NULL) // Ponteiro nulo significa problemas na abertura do arquivo
    {
        printf("Arquivo não pode ser aberto\n");
        return NULL;
    }
    // Se chegamos até aqui é porque o arquivo está aberto
    
    // Vamos criar um array para armazenar nossos livros
    acervo = (TBook*) malloc(CSVSIZE*sizeof(TBook));

    fp = fopen(fileName, "r");

    // pegando o cabeçalho
    char *ok; // se ok for NULL teve problema na leitura
    ok = fgets(str, 900, fp); // pega a string do arquivo 
    if(!ok) // se ok != NULL (NULL é Falso, diferente de NULL verdadeiro)
    {
        printf("Erro lendo o cabeçalho do CSV!!!", str);
        return NULL;
    }     
    i = 0;
    char sep[] = ",";
    while(!feof(fp) && i < CSVSIZE) // enquanto nâo chegar no final do arquivo ou no tamanho do array
    {   
        ok = fgets(str, 900, fp); // pega a string do arquivo 
        if(ok) // se ok != NULL (NULL é Falso, diferente de NULL verdadeiro)
        {
            char *campo;

            //int bookID
            campo = strtok(str, sep);  // pega a string até a primeira ','
            acervo[i].bookID = atoi(campo); // converte em int
            
            //char *title
            campo = strtok(NULL, sep); // pega a string até a próxima ','
            acervo[i].title = (char*) malloc(strlen(campo)); // aloca uma array 
            strcpy(acervo[i].title, campo); // copia o conteúdo da string

            //char *authors
            campo = strtok(NULL, sep);
            acervo[i].authors = (char*) malloc(strlen(campo));
            strcpy(acervo[i].authors, campo);

            //float avgRating
            campo = strtok(NULL, sep);
            acervo[i].avgRating = atof(campo); // converte em float

            //char *isbn
            campo = strtok(NULL, sep);
            acervo[i].isbn = (char*) malloc(strlen(campo));
            strcpy(acervo[i].isbn, campo);

            //char *isbn13
            campo = strtok(NULL, sep);
            acervo[i].isbn13 = (char*) malloc(strlen(campo));
            strcpy(acervo[i].isbn13, campo);

            //char *lang
            campo = strtok(NULL, sep);
            acervo[i].lang = (char*) malloc(strlen(campo));
            strcpy(acervo[i].lang, campo);

            //int numPages
            campo = strtok(NULL, sep);
            acervo[i].numPages = atoi(campo);

            //int ratCounts
            campo = strtok(NULL, sep);
            acervo[i].ratCounts = atoi(campo);

            //int txtRevCounts
            campo = strtok(NULL, sep);
            acervo[i].txtRevCounts = atoi(campo);

            //char pubDate[11]
            campo = strtok(NULL, sep);
            acervo[i].pubDate = (char*) malloc(strlen(campo));
            strcpy(acervo[i].pubDate, campo);

            //char publisher[100];    // publisher - Scholastic Inc. 
            campo = strtok(NULL, sep);
            // o último campo termina com caractere 10 e pode conter lixo no final
            int pos = 0;
            while(campo[pos] != 10 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0'; // substituir 10 por '\0'
            acervo[i].publisher = (char*) malloc(strlen(campo));
            strcpy(acervo[i].publisher, campo);
            
            i++;  // próximo item 
        }
    }
    *tam = i;
    int err = fclose(fp);
    if (err) // err != 0
    {
        printf("Arquivo incorretamente fechado!!\n");
    }
    return acervo;
}

TBook* clonaBook(TBook book)
{
    TBook *novo = (TBook*) malloc(sizeof(TBook));

    novo->bookID = book.bookID;
    novo->title = (char*) malloc(strlen(book.title));
    strcpy(novo->title, book.title);
    novo->authors = (char*) malloc(strlen(book.authors));
    strcpy(novo->authors, book.authors);
    novo->avgRating = book.avgRating;
    novo->isbn = (char*) malloc(strlen(book.isbn));
    strcpy(novo->isbn, book.isbn);
    novo->isbn13 = (char*) malloc(strlen(book.isbn13));
    strcpy(novo->isbn13, book.isbn13);
    novo->lang = (char*) malloc(strlen(book.lang));
    strcpy(novo->lang, book.lang);
    novo->numPages = book.numPages;
    novo->ratCounts = book.ratCounts;
    novo->txtRevCounts = book.txtRevCounts;
    novo->pubDate = (char*) malloc(strlen(book.pubDate));
    strcpy(novo->pubDate, book.pubDate);
    novo->publisher = (char*) malloc(strlen(book.publisher));
    strcpy(novo->publisher, book.publisher);
    return novo;
}

void cpyTBook(TBook src, TBook *dest)
{
    dest->bookID = src.bookID;
    dest->title = (char*) malloc(strlen(src.title));
    strcpy(dest->title, src.title);
    dest->authors = (char*) malloc(strlen(src.authors));
    strcpy(dest->authors, src.authors);
    dest->avgRating = src.avgRating;
    dest->isbn = (char*) malloc(strlen(src.isbn));
    strcpy(dest->isbn, src.isbn);
    dest->isbn13 = (char*) malloc(strlen(src.isbn13));
    strcpy(dest->isbn13, src.isbn13);
    dest->lang = (char*) malloc(strlen(src.lang));
    strcpy(dest->lang, src.lang);
    dest->numPages = src.numPages;
    dest->ratCounts = src.ratCounts;
    dest->txtRevCounts = src.txtRevCounts;
    dest->pubDate = (char*) malloc(strlen(src.pubDate));
    strcpy(dest->pubDate, src.pubDate);
    dest->publisher = (char*) malloc(strlen(src.publisher));
    strcpy(dest->publisher, src.publisher);
}

void limpaAcervo(TBook *acervo, int tam)
{
    if(acerco == NULL)
        return;
    for(int j = 0; j < tam; j++)
        limpaRegistro(acervo[j]);
    free(acervo);
}

void limpaRegistro(TBook book)
{
    if (book.title != NULL)
        free(book.title);
    if(book.authors != NULL)
        free(book.authors);
    if(book.isbn != NULL)
        free(book.isbn);
    if(book.isbn13 != NULL)
        free(book.isbn13);
    if(book.lang != NULL)
        free(book.lang);
    if(book.pubDate != NULL)
        free(book.pubDate);
    if(book.publisher != NULL)
        free(book.publisher);
}

void imprimeTBook(TBook book)
{
    printf("bookID: %d\n", book.bookID);
    printf("title: %s\n", book.title);
    printf("authors: %s\n", book.authors);
    printf("avgRating: %f\n", book.avgRating);
    printf("isbn: %s\n", book.isbn);
    printf("isbn13: %s\n", book.isbn13);
    printf("lang: %s\n", book.lang);
    printf("numPages: %d\n", book.numPages);
    printf("ratCounts: %d\n", book.ratCounts);
    printf("txtRevCounts: %d\n", book.txtRevCounts);
    printf("pubDate: %s\n", book.pubDate);
    printf("publisher: %s\n", book.publisher);
}

void impResumo(TBook book)  
{
    printf("bookID: %d, ", book.bookID);
    printf("title: %s, ", book.title);
    printf("authors: %s, ", book.authors);
    printf("isbn: %s, ", book.isbn);
    printf("isbn13: %s\n", book.isbn13);
}

void imprimeAcervo(TBook *acervo, int tam)
{
    for(int i = 0; i < tam; i++)
        impResumo(acervo[i]);
}

TBook* criaAcervo(int cap)
{
    TBook* acervo;
    acervo = (TBook*) malloc((cap + 1)*sizeof(TBook));
    return acervo;
}

int buscaPorISBN(char *isbn, TBook* lista, int tam)
{
    strcpy(lista[tam].isbn, isbn);
    int i = 0;
    while(strcmp(isbn, lista[i].isbn) != 0)
        i++;
    return i;
}

int incRegistro(TBook book, TBook* lista, int* tam)
{
    // procura o isbn na lista
    int pos = buscaPorISBN(book.isbn, lista, *tam);
    if(pos == *tam) // se não encontrou
    {
        // copia o registro para a posição tam
        cpyTBook(book, &lista[*tam]);
        *tam += 1;
        return TRUE;
    }else{
        return FALSE;
    }
}

int remRegistro(char* isbn, TBook* lista, int* tam)
{
    int pos = buscaPorISBN(isbn, lista, *tam);
    if(pos != *tam)
    {
        limpaRegistro(lista[pos]);
        if(*tam > 1)
            lista[pos] = lista[*tam - 1];
        *tam -= 1;
        return TRUE;
    }else{
        return FALSE;
    }

}

TBook* criaAcervoOrd(int cap)
{
    TBook* acervo;
    acervo = (TBook*) malloc((cap)*sizeof(TBook));
    return acervo;
}

int buscaOrdLinearPorISBN_(char *isbn, TBook* lista, int tam)
{
    int i = 0;
    strcpy(lista[tam].isbn, isbn);
    while(strcmp(isbn, lista[i].isbn) < 0)
        i++;
    return i;
}

int buscaBinPorISBN(char *isbn, TBook* lista, int tam)
{
    int ini = 0, fim = tam, pos;
    while (ini < fim)
    {
        pos = (ini + fim)/2;
        if (strcmp(isbn, lista[pos].isbn) < 0)
            fim = pos - 1;
        else if(strcmp(isbn, lista[pos].isbn) == 0)
            return pos;
        else
            ini = pos + 1;
    }
    return pos;
}

int incRegistroOrd(TBook book, TBook* lista, int* tam)
{
    // procura o isbn na lista
    int pos = buscaBinPorISBN(book.isbn, lista, *tam);
    if (strcmp(lista[pos].isbn, book.isbn) != 0)
    {
        for (int i = *tam; i > pos; i--)
            lista[i-1] = lista[i];
        cpyTBook(book, &lista[pos]);
        *tam += 1;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int remRegistroOrd(char* isbn, TBook* lista, int* tam)
{
    int pos = buscaBinPorISBN(isbn, lista, *tam);
    if(strcmp(lista[pos].isbn, isbn) == 0)
    {   
        limpaRegistro(lista[pos]);
        for (int i = pos; i < *tam; i++)
            lista[i] = lista[i+1];
        return TRUE;
    }else{
        return FALSE;
    }

}


//===========================

PNoBookSE alocaNoBookSE(void)
{
    PNoBookSE p = (PNoBookSE) malloc(sizeof(TNoBookSE));
    p->prox = NULL;
    return p;
}

void destroiNoBookSE(PNoBookSE p)
{
    free(p);
}

PNoBookSE criaListaSEDeListaLinear(TBook *lista, int tam)
{
    PNoBookSE head;
    if (tam == 0)
        return NULL;
    else
    {
        head = alocaNoBookSE();
        cpyTBook(lista[0], &head->book);
        PNoBookSE p = head;
        for (int i = 1; i < tam; i++)
        {
            p->prox = alocaNoBookSE();
            p = p->prox;
            cpyTBook(lista[i], &p->book);
        }
        return head;
    }
}

void imprimeListaSE(PNoBookSE head)
{
    PNoBookSE p = head;
    while (p != NULL)
    {
        impResumo(p->book);
        p = p->prox;
    }
}

void destroiListaSE(PNoBookSE head)
{
    PNoBookSE p = head;
    while (p != NULL)
    {
        PNoBookSE aux = p;
        p = p->prox;
        destroiNoBookSE(aux);
    }
}



int incRegistroSE(TBook book, PNoBookSE* head)
{
    PNoBookSE p = buscaPorISBNSE(book.isbn, *head);
    if (p == NULL)
    {
        p = alocaNoBookSE();
        cpyTBook(book, &p->book);
        p->prox = *head;
        *head = p;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int remRegistroSE(char* isbn, PNoBookSE* head)
{
    PNoBookSE p = buscaPorISBNSE(isbn, *head);
    if (p != NULL){
        if (p == *head) {
            *head = p->prox;
            destroiNoBookSE(p);
        }else{
            PNoBookSE ant = *head;
            while (ant->prox != p)
                ant = ant->prox;
            ant->prox = p->prox;
            destroiNoBookSE(p);
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

PNoBookSE buscaPorISBNSE(char *isbn, PNoBookSE head)
{
    PNoBookSE p = head;
    while (p != NULL)
    {
        if (strcmp(isbn, p->book.isbn) == 0)
            return p;
        p = p->prox;
    }
    return NULL;
}

PNoBookSE buscaOrdPorISBNSE(char *isbn, PNoBookSE head)
{
    PNoBookSE p = head;
    while (p != NULL)
    {
        if (strcmp(isbn, p->book.isbn) <= 0)
            return p;
        p = p->prox;
    }
    return NULL;
}

int incRegistroOrdSE(TBook book, PNoBookSE* head)
{   
    PNoBookSE p = *head;
    if (strcmp(book.isbn, p->book.isbn) < 0){
        PNoBookSE novo = alocaNoBookSE();
        cpyTBook(book, &novo->book);
        novo->prox = *head;
        *head = novo;
        return TRUE;
    }else{
        while (p->prox != NULL && strcmp(book.isbn, p->prox->book.isbn) > 0)
            p = p->prox;
        if (p->prox == NULL || strcmp(book.isbn, p->prox->book.isbn) < 0)
        {
            PNoBookSE novo = alocaNoBookSE();
            cpyTBook(book, &novo->book);
            novo->prox = p->prox;
            p->prox = novo;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

int remRegistroOrdSE(char* isbn, PNoBookSE* head)
{
    PNoBookSE p = *head;
    if (strcmp(isbn, p->book.isbn) == 0){
        *head = p->prox;
        destroiNoBookSE(p);
        return TRUE;
    }else{
        while (p->prox != NULL && strcmp(isbn, p->prox->book.isbn) > 0)
            p = p->prox;
        if (p->prox != NULL && strcmp(isbn, p->prox->book.isbn) == 0)
        {
            PNoBookSE aux = p->prox;
            p->prox = aux->prox;
            destroiNoBookSE(aux);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

PilhaEnc* criaPilhaEnc()
{
    PilhaEnc* pilha = (PilhaEnc*) malloc(sizeof(PilhaEnc));
    pilha->topo = NULL;
    pilha->tam = 0;
    return pilha;

}

int pilhaVazia(PilhaEnc* pilha)
{
    return (pilha->topo == NULL);
    //return (pilha->tam == 0);
}


int empilha(TBook book, PilhaEnc* pilha)
{
    PNoBookSE p = alocaNoBookSE();
    cpyTBook(book, &p->book);
    p->prox = pilha->topo;
    pilha->topo = p;
    pilha->tam++;
    return TRUE;
}


TBook desempilha(PilhaEnc* pilha){
    TBook book;
    if (pilhaVazia(pilha))
    {
        printf("Pilha vazia!\n");
        return book;
    }
    else
    {
        PNoBookSE p = pilha->topo;
        pilha->topo = p->prox;
        pilha->tam--;
        cpyTBook(p->book, &book);
        destroiNoBookSE(p);
        return book;
    }


FilaEnc* criaFila()
{   
    FilaEnc* fila = (FilaEnc*) malloc(sizeof(FilaEnc));
    fila->ini = NULL;
    fila->fim = NULL;
    fila->tam = 0;
    return fila;
}

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

TBook removeDaFila(FilaEnc* fila)
{
    TBook book;
    if (filaVazia(fila))
    {
        printf("Fila vazia!\n");
        return book;
    }
    else
    {
        PNoBookSE p = fila->ini;
        fila->ini = p->prox;
        fila->tam--;
        cpyTBook(p->book, &book);
        destroiNoBookSE(p);
        return book;
    }
}




