#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h"

int main(void)
{
    TBook *acervo;
    int id, tam;

    acervo = carregaDados("../../Data/books.csv", &tam);

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

    limpaAcervo(acervo, tam);
    return 0;
}