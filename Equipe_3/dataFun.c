#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"dataFun.h"

//Carrega Dados do Arquivo
t_Fipe *carregaDados(char *arquivo, int *tam)
{
    t_Fipe *fipe;
    FILE *fp;

    char str[900];
    int i = 0;

    fipe = (t_Fipe *)malloc(CSVSIZE * sizeof(t_Fipe));

    if (fipe == NULL) {
        printf("ERRO! Falha ao alocar memoria!\n");
        exit(1);
    }

    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("ERRO! Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    char *ok;
    ok = fgets(str, 900, fp);
    if (ok == NULL) {
        printf("Erro lendo o cabecalho do CSV!!!\n");
        exit(1);
    }

    i = 0;
    char sep[] = ",";

    while (!feof(fp) && i < CSVSIZE) {
        ok = fgets(str, 900, fp);
        if (ok) {
            char *campo;
            campo = strtok(str, sep);
            fipe[i].nCdg = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].codigofp = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].marca = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].modelo = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].anoModelo = atoi(campo);
            campo = strtok(NULL, sep);
            fipe[i].mesReferencia = atoi(campo);
            campo = strtok(NULL, sep);
            fipe[i].anoReferencia = atoi(campo);
            campo = strtok(NULL, sep);
            fipe[i].valor = atof(campo);
            i++;
        }
    }
    fclose(fp);
    *tam = i;
    return fipe;
}

void limpaFipe(t_Fipe *fipe, int tam)
{
    for(int j = 0; j < tam; j++)
        limpaRegistro(fipe[j]);

        free(fipe);
}

void limpaRegistro(t_Fipe fipe)
{
    free(fipe.nCdg);
    free(fipe.modelo);
    free(fipe.marca);
    free(fipe.codigofp);

    // free(fipe);
}

//Busca elemento e retorna o indice
int buscaPorId(t_Fipe *fipe, int tam, char *idBusca)
{
    for(int i = 0; i < tam; i++)
    {
        // Comparando o ID de busca 'idBusca' com o ID do elemento atual da lista 'fipe'
        if (strcmp(fipe[i].nCdg, idBusca) == 0)
        {
            // Se os IDs sao iguais, retorna o indice do elemento encontrado
            return i;
        }
    }
    // Se o elemento nao foi encontrado na lista, retorna -1
    return -1;
}

void criaFipe(int cap, t_Fipe** fipe)
{
    *fipe = (t_Fipe*)malloc((cap + 1) * sizeof(t_Fipe));
}

//incluir registros
int incRegistro(t_Fipe fipe, t_Fipe *lista, int *tam)
{
    lista = realloc(lista, (*tam + 1) * sizeof(t_Fipe));
    if(!lista){
        printf("Erro ao realocar memoria para a lista!");
        return -1;
    }

    lista[*tam] = fipe;
    (*tam)++;
    return *tam - 1;
}

//remover registros de forma ordenada
int remRegistro(char *idBusca, t_Fipe *lista, int *tam)
{
    int posicao = buscaPorId(idBusca, lista, *tam);
    if(posicao == -1)
    {
        printf("Registro não Encontrado!");
        return -1;
    }

    for(int i = pos; i < *tam - 1; i++)
    {
        lista[i] = lista[i + 1];
    }

    lista = realloc(lista, (*tam ) * sizeof(t_Fipe));
    if(!lista)
    {
        printf("Erro ao realocar memoria!");
        return -1;
    }

    (*tam)--;
    return posicao;
}

//Busca Oredenada por IDchave
int buscIdOrd(char *idBusca, t_Fipe fipe, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if(strcmp(idBusca, fipe[i].nCdg) == 0)
        {
            return i;
        }
    }
    return -1;
}

//incluir registro ordenado
int incRegOrd(t_Fipe fipe, t_Fipe *lista, int *tam) //parametros (registro, lista geral, tam total)
{
    lista = realloc(lista, (*tam + 1) * sizeof(t_Fipe));
    if(!lista)
    {
        printf("Erro ao realocar memoria na lista!");
        return -1;
    }

    int pos = 0;

    while(pos < *tam && strcmp(fipe.nCdg, lista[pos].nCdg) > 0)
    {
        pos++;
    }

    for(int i = *tam; i > pos; i--)
    {
        lista[i] = lista[i - 1];
    }
    lista[pos] = fipe;
    (*tam)++;
    return pos;
}

void printRegistro(t_Fipe fipe) //fipe é o registro
{
    printf("Num Cdg: %s\n", fipe.nCdg);
    printf("Codigo fp: %s\n", fipe.codigofp);
    printf("Marca: %s\n", fipe.marca);
    printf("Modelo: %s\n", fipe.modelo);
    printf("Valor: %.2f\n", fipe.valor);
    printf("Mes ref: %d\n", fipe.mesReferencia);
    printf("Ano ref: %d\n", fipe.anoReferencia);
    printf("Ano modelo: %d\n", fipe.anoModelo);
}

void printLista(t_Fipe *fipe, int tam) //fipe é o registro
{
    for(int i = 0; i < tam; i++)
    {
        printRegistro(lista[i]);
        printf("\n");
    }
}

//Criar uma lista
t_ListaLinear *criaListaLinear(int cap, int ehOrd)
{
    t_ListaLinear *listaLinear;
    listaLinear->cap = cap;
    listaLinear->ehOrd = ehOrd;

    if (ehOrd)
        listaLinear->lista = (t_Fipe*) malloc(cap * sizeof(t_Fipe));
    else
        listaLinear->lista = (t_Fipe*) malloc((cap+1) * sizeof(t_Fipe));

    if (!listaLinear->lista) {
    printf("ERRO! Falha ao alocar memoria!\n");
    exit(1);
    }
    return listaLinear;
}

int BuscaNaListaLinear(char *idBusca, t_ListaLinear* fipe)
{
    int i = 0;
    while(strcmp(idBusca, fipe->lista[i].nCdg) < 0)
    {
        i++;
    }
    if (strcmp(idBusca, fipe->lista[i].nCdg) == 0)
        return i;
    else
        return -i;
}

int remOrdFipe(char* idBusca, t_Fipe* fipe, int* tam)
{
    fipe[*tam].nCdg = idBusca;
    int i = buscIdOrd(idBusca, fipe, tam);
    i *= -1;
    if (i != *tam){
        limpaRegistro(fipe[i]);
        if (*tam>1)
            fipe[i] = fipe[*tam-1];
        *tam -= 1;
        return 1;
    }else{
    return 0;
    }
}
