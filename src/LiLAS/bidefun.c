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
        printf("Erro lendo o cabeçalho do CSV!!!");
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

void limpaAcervo(TBook *acervo, int tam)
{
    for(int j = 0; j < tam; j++)
        limpaRegistro(acervo[j]);
        
    free(acervo);
}

void limpaRegistro(TBook book)
{
        free(book.title);
        free(book.authors);
        free(book.isbn);
        free(book.isbn13);
        free(book.lang);
        free(book.pubDate);
        free(book.publisher);
        
}
    

/*
    Primeira versão na forma recursiva
*/
int buscaPorISBN_(char *isbn, TBook* lista, int tam)
{
    // a list não pode estar vazia
    // comparar o isbn com o primeiro elemento da lista
    int res = strcmp(lista[0].isbn, isbn);
    if(tam == 1) // se a lista tiver apenas um elemento
    {
        if (res != 0) // se diferente de zero então é diferente
            return tam;  
        else // se for zero então é igual
            return 0; // está na posição de índice 0
    }
    else if(res != 0) // se diferente de zero então é diferente
        // chama a função recursivamente com o resto da lista
        return 1 + buscaPorISBN(isbn, &lista[1], tam-1);
    else
        return 0; // está na posição de índice 0
}

/*
    Primeira versão na forma não recursiva
*/
int buscaPorISBN__(char *isbn, TBook* lista, int tam)
{
    int i;
    for(i = 0; i < tam; i++)
        if(strcmp(isbn, lista[i].isbn) == 0)
            return i;
    return i;
}


/*
    Segunda versão na forma recursiva
*/
int buscaPorISBN___(char *isbn, TBook* lista, int tam)
{
    // a list não pode estar vazia
    // comparar o isbn com o primeiro elemento da lista
    int res = strcmp(lista[0].isbn , isbn);
    if(res != 0) // se diferente de zero então é diferente
        // chama a função recursivamente com o resto da lista
        return 1 + buscaPorISBN(isbn, &lista[1], tam-1);
    else
        return 0; // está na posição de índice 0
}

/*
    Segunda versão na forma não recursiva
*/
int buscaPorISBN(char *isbn, TBook* lista, int tam)
{
    int i = 0;
    while(strcmp(isbn, lista[i].isbn) != 0)
        i++;
    return i;
}

TBook* criaAcervo(int cap)
{
    TBook* acervo;
    acervo = (TBook*) malloc((cap + 1)*sizeof(TBook));
    return acervo;
}

void criaAcervo_(int cap, TBook** acervo)
{
    *acervo = (TBook*) malloc((cap + 1)*sizeof(TBook));
}

int incRegistro(TBook book, TBook* lista, int* tam)
{
    // copia o isbn procurado na posição tam
    lista[*tam].isbn = book.isbn;
    // procura o isbn na lista
    int pos = buscaPorISBN(book.isbn, lista, *tam);
    if(pos == *tam) // se não encontrou
    {
        // copia o registro para a posição tam
        //int bookID
        lista[pos].bookID = book.bookID;
        
        //char *title
        lista[pos].title = (char*) malloc(strlen(book.title)); // aloca uma array 
        strcpy(lista[pos].title, book.title); // copia o conteúdo da string
        
        //char *authors
        lista[pos].authors = (char*) malloc(strlen(book.title));
        strcpy(lista[pos].authors, book.authors);

        //float avgRating
        lista[pos].avgRating = book.avgRating; // converte em float

        //char *isbn
        lista[pos].isbn = (char*) malloc(strlen(book.isbn));
        strcpy(lista[pos].isbn, book.isbn);

        //char *isbn13
        lista[pos].isbn13 = (char*) malloc(strlen(book.isbn13));
        strcpy(lista[pos].isbn13, book.isbn13);

        //char *lang
        lista[pos].lang = (char*) malloc(strlen(book.lang));
        strcpy(lista[pos].lang, book.lang);

        //int numPages
        lista[pos].numPages = book.numPages;

        //int ratCounts
        lista[pos].ratCounts = book.ratCounts;

        //int txtRevCounts
        lista[pos].txtRevCounts = book.txtRevCounts;

        //char pubDate[11]
        lista[pos].pubDate = (char*) malloc(strlen(book.pubDate));
        strcpy(lista[pos].pubDate, book.pubDate);

        //char publisher[100];    // publisher - Scholastic Inc. 
        lista[pos].publisher = (char*) malloc(strlen(book.publisher));
        strcpy(lista[pos].publisher, book.publisher);
        
        *tam += 1;
        return TRUE;
    }else{
        return FALSE;
    }
}

int remRegistro(char* isbn, TBook* lista, int* tam)
{
    lista[*tam].isbn = isbn;
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


int buscaOrdPorISBN(char *isbn, TBook* lista, int tam)
{
    int i = 0;
    //while(strcmp(isbn, lista[i].isbn) != 0)
    while(strcmp(isbn, lista[i].isbn) < 0)
    {
        i++;
    }
    if (strcmp(isbn, lista[i].isbn) == 0)
        return i;
    else
        return -i;
}

int buscaBinPorISBN(char *isbn, TBook* lista, int tam)
{
    if (tam == 0)
        return -1;
    int pos = tam / 2;
    if (strcmp(isbn, lista[pos].isbn) < 0)
        return buscaBinPorISBN(isbn, lista, pos);
    else if(strcmp(isbn, lista[pos].isbn) == 0)
        return pos;
    else
        return pos + buscaBinPorISBN(isbn, &lista[pos+1], tam - pos - 1) + 1;
}

int buscaBinPorISBN_(char *isbn, TBook* lista, int tam)
{
    
}

int incRegistroOrd(TBook book, TBook* lista, int* tam)
{
    //lista[*tam].isbn = book.isbn;
    int pos = buscaBinPorISBN(book.isbn, lista, *tam);
    if (strcmp(lista[pos].isbn, book.isbn) != 0)
    {
        for (int i = *tam; i > pos; i--)
            lista[i-1] = lista[i];
        //int bookID
        lista[pos].bookID = book.bookID;
        
        //char *title
        lista[pos].title = (char*) malloc(strlen(book.title)); // aloca uma array 
        strcpy(lista[pos].title, book.title); // copia o conteúdo da string
        
        //char *authors
        lista[pos].authors = (char*) malloc(strlen(book.title));
        strcpy(lista[pos].authors, book.authors);

        //float avgRating
        lista[pos].avgRating = book.avgRating; // converte em float

        //char *isbn
        lista[pos].isbn = (char*) malloc(strlen(book.isbn));
        strcpy(lista[pos].isbn, book.isbn);

        //char *isbn13
        lista[pos].isbn13 = (char*) malloc(strlen(book.isbn13));
        strcpy(lista[pos].isbn13, book.isbn13);

        //char *lang
        lista[pos].lang = (char*) malloc(strlen(book.lang));
        strcpy(lista[pos].lang, book.lang);

        //int numPages
        lista[pos].numPages = book.numPages;

        //int ratCounts
        lista[pos].ratCounts = book.ratCounts;

        //int txtRevCounts
        lista[pos].txtRevCounts = book.txtRevCounts;

        //char pubDate[11]
        lista[pos].pubDate = (char*) malloc(strlen(book.pubDate));
        strcpy(lista[pos].pubDate, book.pubDate);

        //char publisher[100];    // publisher - Scholastic Inc. 
        lista[pos].publisher = (char*) malloc(strlen(book.publisher));
        strcpy(lista[pos].publisher, book.publisher);
        
        *tam += 1;
        return TRUE;
    }else{
        return FALSE;
    }
}

int remRegistroOrd(char* isbn, TBook* lista, int* tam)
{
    lista[*tam].isbn = isbn;
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




