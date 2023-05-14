#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Jogos *criaAcervo(int capacidade)
{

    Jogos *acervo;

    acervo = (Jogos *)malloc((capacidade + 1) * sizeof(Jogos));

    return acervo;
}

Jogos *carregaDados(char *fileName, int *tam)
{

    int i = 0;
    char sep[1], str[2000], *ok;
    sep[0] = ',';
    Jogos *acervo;
    FILE *fp;
    fp = fopen(fileName, "r");
    acervo = criaAcervo(*tam);

    if (fp == NULL)
    {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    ok = fgets(str, 2000, fp); // Pega cabeçalho

    if (!ok)
    {
        printf("Erro ao o cabeçalho do CSV!!!");
        exit(1);
    }

    while (!feof(fp) && i < *tam)
    {
        ok = fgets(str, 2000, fp); // pega a linha do CSV

        if (ok)
        {
            char *campo;

            // APP ID
            campo = strtok(str, sep); // pega a string até a primeira ','
            acervo[i].appId = atoi(campo);

            // TITLE
            campo = strtok(NULL, sep);
            int pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].title = (char *)malloc(strlen(campo));
            strcpy(acervo[i].title, campo);

            // Data release
            campo = strtok(NULL, sep);
            pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].dataRelease = (char *)malloc(strlen(campo));
            strcpy(acervo[i].dataRelease, campo);

            // WINDOWS
            campo = strtok(NULL, sep);
            acervo[i].win = (char *)malloc(strlen(campo));
            strcpy(acervo[i].win, campo);

            // MAC
            campo = strtok(NULL, sep);
            acervo[i].mac = (char *)malloc(strlen(campo));
            strcpy(acervo[i].mac, campo);

            // LINUX
            campo = strtok(NULL, sep);
            acervo[i].linux = (char *)malloc(strlen(campo));
            strcpy(acervo[i].linux, campo);

            // RATING
            campo = strtok(NULL, sep);
            pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].rating = (char *)malloc(strlen(campo));
            strcpy(acervo[i].rating, campo);

            // POSITIVE RATIO
            campo = strtok(NULL, sep);
            acervo[i].positiveRatio = atoi(campo);

            // USER REVIEWS
            campo = strtok(NULL, sep);
            acervo[i].userReviews = atoi(campo);

            // PRICE FINAL
            campo = strtok(NULL, sep);
            acervo[i].priceFinal = atof(campo);

            // PRICE ORIGINAL
            campo = strtok(NULL, sep);
            acervo[i].priceOriginal = atof(campo);

            // DISCOUNT
            campo = strtok(NULL, sep);
            acervo[i].discount = atof(campo);

            i++;
        }
    }

    return acervo;
}

Pilha *inicializaPilha()
{

    Pilha *pilha = (Pilha *)malloc(100 * sizeof(Pilha));
    pilha->topo == NULL;
    pilha->tam = 0;

    return pilha;
}

int isPilhaVazia(Pilha *pilha)
{

    if (pilha->tam == 0)
    {
        return 1;
    }

    return 0;
}

int isPilhaCheia(Pilha *pilha)
{

    if (pilha->tam == 100)
        return 1;

    return 0;
}

void imprimePilha(Pilha *pilha)
{
    ElementoPilha *ptr = pilha->topo;

    if (isPilhaVazia(pilha))
    {
        printf("Pilha vazia!\n");
    }
    else
    {
        while (ptr != NULL)
        {
            printf("%s\n", ptr->jogo->title);
            ptr = ptr->prox;
        }
    }
}

void imprimeElementoPilha(Pilha *pilha)
{

    printf("%s", pilha->topo->jogo->title);
}

int empilhar(Jogos *jogo, Pilha *pilha)
{

    ElementoPilha *ptr = (ElementoPilha *)malloc(sizeof(ElementoPilha));

    if (ptr == NULL)
    {
        return 0;
    }
    ptr->jogo = jogo;
    ptr->prox = pilha->topo;
    pilha->topo = ptr;
    pilha->tam++;
    return 1;
}

Jogos *desempilha(Pilha *pilha)
{

    if (isPilhaVazia(pilha))
        return NULL;

    ElementoPilha *aux = pilha->topo;
    Jogos *jogo = pilha->topo->jogo;

    pilha->topo = pilha->topo->prox;
    free(aux);
    pilha->tam--;

    return jogo;
}

Fila *inicializaFila()
{

    Fila *fila = (Fila *)malloc(sizeof(Fila));

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

int insereNaFila(Jogos *jogo, Fila *fila)
{

    ElementoFila *elementoFila = (ElementoFila *)malloc(sizeof(ElementoFila));

    if (elementoFila == NULL)
        return 0;

    elementoFila->jogo = jogo;
    elementoFila->prox = NULL;

    if (fila->inicio == NULL)
    {

        fila->inicio = elementoFila;
        fila->fim = elementoFila;
    }
    else
    {
        fila->fim->prox = elementoFila;
    }

    fila->fim = elementoFila;

    return 1;
}

Jogos *removeDaFila(Fila *fila)
{

    // verifica se há elementos para remover
    if (isFilaVazia(fila))
        return NULL;

    ElementoFila *aux = fila->inicio;

    Jogos *itemRemovido = aux->jogo;

    fila->inicio = aux->prox;

    free(aux);

    return itemRemovido;
}

int isFilaVazia(Fila *fila)
{

    if (fila->inicio == NULL)
        return 1;

    return 0;
}

void imprimeElementoFila(Fila *fila)
{

    printf("%s", fila->inicio->jogo->title);
}

int insereEncadeado(Jogos *jogo, Encadeado *listaEncadeada)
{

    ElementoEncadeado *novoElemento = (ElementoEncadeado *)malloc(sizeof(ElementoEncadeado));
    ElementoEncadeado *ultimoNo = listaEncadeada->topo;

    // Verificar se alocou espaço.
    if (novoElemento == NULL)
        return 0;

    // Preenche o novo nó.
    novoElemento->jogo = jogo;
    // copiaJogos( *jogo, novoElemento->jogo );
    novoElemento->prox = NULL;

    // Se a lista estiver vazia, o novo nó será o primeiro nó
    if (listaEncadeada->topo == NULL)
    {
        listaEncadeada->topo = novoElemento;
        listaEncadeada->tam++;
        return 1;
    }

    // Percorre a lista até o último nó
    while (ultimoNo->prox != NULL)
    {

        ultimoNo = ultimoNo->prox;
    }

    // Define o próximo do último nó para o novo nó
    ultimoNo->prox = novoElemento;

    listaEncadeada->tam++;

    return 1;
}

Jogos *removeEncadeado(Encadeado *listaEncadeada)
{

    Jogos *jogo;
    ElementoEncadeado *auxiliar;

    if (listaEncadeada->tam == 0)
        return NULL;

    // copiaJogos( *listaEncadeada->topo->jogo, jogo );
    jogo = listaEncadeada->topo->jogo;

    auxiliar = listaEncadeada->topo;
    listaEncadeada->topo = listaEncadeada->topo->prox;
    // free( auxiliar );

    listaEncadeada->tam--;

    return jogo;
}

Encadeado *inicializaListaEncadeada()
{

    Encadeado *listaEncadeada = (Encadeado *)malloc(sizeof(Encadeado));

    listaEncadeada->topo = NULL;
    listaEncadeada->tam = 0;

    return listaEncadeada;
}

void imprimeElementoListaEncadeada(Encadeado *lista)
{

    ElementoEncadeado *auxiliar = lista->topo;

    printf("%s.", auxiliar->jogo->title);
}

void imprimeUltimoElementoListaEncadeada(Encadeado *listaEncadeada)
{

    ElementoEncadeado *auxiliar = listaEncadeada->topo;

    while (auxiliar->prox != NULL)
    {
        auxiliar = auxiliar->prox;
    }

    printf("%s.\n", auxiliar->jogo->title);
}