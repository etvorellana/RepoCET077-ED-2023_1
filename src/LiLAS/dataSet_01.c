#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h"

int main(void)
{
    TBook *acervo;
    int id, tam;

    acervo = carregaDados("../../../Data/books.csv", &tam);

    do
    {
        printf("Entre com índice de um item do acervo (%d < BookID < %d): ", 0, tam);
        scanf("%d", &id);
    } while (id <= 0 && id >= tam);

    printf("%d,", acervo[id].bookID);
    printf("%s,", acervo[id].title);
    printf("%s,", acervo[id].authors);
    printf("%.2f,", acervo[id].avgRating);
    printf("%s,", acervo[id].isbn);
    printf("%s,", acervo[id].isbn13);
    printf("%s,", acervo[id].lang);
    printf("%d,", acervo[id].numPages);
    printf("%d,", acervo[id].ratCounts);
    printf("%d,", acervo[id].txtRevCounts);
    printf("%s,", acervo[id].pubDate);
    printf("%s\n", acervo[id].publisher);

    // Vamos procurar por um isbn existente
    acervo[tam].isbn = acervo[id].isbn;
    int pos = buscaPorISBN(acervo[id].isbn, acervo, tam);
    if (pos < tam)
    {
        printf("%d,", acervo[pos].bookID);
        printf("%s,", acervo[pos].title);
        printf("%s,", acervo[pos].authors);
        printf("%.2f,", acervo[pos].avgRating);
        printf("%s,", acervo[pos].isbn);
        printf("%s,", acervo[pos].isbn13);
        printf("%s,", acervo[pos].lang);
        printf("%d,", acervo[pos].numPages);
        printf("%d,", acervo[pos].ratCounts);
        printf("%d,", acervo[pos].txtRevCounts);
        printf("%s,", acervo[pos].pubDate);
        printf("%s\n", acervo[pos].publisher);
    }else{
        printf("Registro não encontrado\n");
    }

    // Vamos procurar por um isbn existente
    char isbn[8] = "1234567";
    acervo[tam].isbn = isbn;
    pos = buscaPorISBN("1234567", acervo, tam);
    if (pos < tam)
    {
        printf("%d,", acervo[pos].bookID);
        printf("%s,", acervo[pos].title);
        printf("%s,", acervo[pos].authors);
        printf("%.2f,", acervo[pos].avgRating);
        printf("%s,", acervo[pos].isbn);
        printf("%s,", acervo[pos].isbn13);
        printf("%s,", acervo[pos].lang);
        printf("%d,", acervo[pos].numPages);
        printf("%d,", acervo[pos].ratCounts);
        printf("%d,", acervo[pos].txtRevCounts);
        printf("%s,", acervo[pos].pubDate);
        printf("%s\n", acervo[pos].publisher);
    }else{
        printf("Registro não encontrado\n");
    }

    limpaAcervo(acervo, tam);
    return 0;
}




/*
    Como compilar
    * Primeiro compile as partes por separado   
    $> gcc -O2 -o bidefun.o -c bidefun.c
        ^   ^   ^     ^      ^     ^
    $> gcc -O2 -o dataSet_01.o -c dataSet_01.c  
    * Depois juntar tudo
    $> gcc -O2 -o exem_01 bidefun.o dataSet_01.o
        ^    ^  ^    ^       ^         ^
*/