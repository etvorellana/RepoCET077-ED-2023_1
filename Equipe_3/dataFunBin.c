#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "dataFunBin.h"

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
    {
        limpaRegistro(fipe[j]);
    }
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

t_Fipe* criaFipe(int cap)
{
    t_Fipe* fipe;
    fipe = (t_Fipe*) malloc((cap + 1)*sizeof(t_Fipe));
    return fipe;
}
///////////////////////////////////////////////////////////////////////
//incluir registros
/*
int incRegistro(t_Fipe fipe, t_Fipe* lista, int* tam)
{
    // copia o nCdg procurado na posi��o tam
    lista[*tam].nCdg = fipe.nCdg;
    // procura o nCdg na lista
    int pos = buscaPorId(lista, *tam, fipe.nCdg);
    if(pos == *tam) // se n�o encontrou
    {
        // copia o registro para a posi��o tam
        lista[pos].nCdg = (char*) malloc(strlen(fipe.nCdg));
        strcpy(lista[pos].nCdg, fipe.nCdg);

        lista[pos].codigofp = (char*) malloc(strlen(fipe.codigofp));
        strcpy(lista[pos].codigofp, fipe.codigofp);

        lista[pos].marca = (char*) malloc(strlen(fipe.marca));
        strcpy(lista[pos].marca, fipe.marca);

        lista[pos].modelo = (char*) malloc(strlen(fipe.modelo));
        strcpy(lista[pos].modelo, fipe.modelo);

        lista[pos].anoModelo = fipe.anoModelo;

        lista[pos].mesReferencia = fipe.mesReferencia;

        lista[pos].anoReferencia = fipe.anoReferencia;

        lista[pos].valor = fipe.valor;

        *tam += 1;
        return TRUE;
    } else {
        return FALSE;
    }
}*/
////////////////////////////////////////////////////////////////////
int incRegistro(t_Fipe book, t_Fipe* lista, int* tam)
{
    int pos = buscaPorId(lista, *tam, book.nCdg); // procura o registro na lista

    if (pos != -1) // se o registro j� existe na lista
    {
        return 0; // n�o adiciona o registro
    }

    // copia o registro para a posi��o *tam
    lista[*tam] = book;

    // incrementa o tamanho da lista
    *tam += 1;

    return 1; // registro adicionado com sucesso
}

////////////////////////////////////////////////////////////////////
//remover registros de forma ordenada
int remRegistro(char *idBusca, t_Fipe *lista, int *tam)
{
    int posicao = buscaPorId(lista, *tam, idBusca);
    if(posicao == -1)
    {
        printf("Registro nao Encontrado!");
        return -1;
    }

    for(int i = posicao; i < *tam - 1; i++)
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
int buscIdOrd(char *idBusca, t_Fipe *fipe, int tam)
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

void printRegistro(t_Fipe fipe) //fipe eh o registro
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

void printLista(t_Fipe *fipe, int tam) //fipe eh o registro
{
    for(int i = 0; i < tam; i++)
    {
        printRegistro(fipe[i]);
        printf("\n");
    }
}

//Criar uma lista
t_ListaLinear *criaListaLinear(int cap, int ehOrd)
{
    t_ListaLinear *listaLinear;
    listaLinear = (t_ListaLinear *)malloc(sizeof(t_ListaLinear));

    if (listaLinear == NULL) {
        printf("ERRO! Falha ao alocar memoria para listaLinear!\n");
        exit(1);
    }

    listaLinear->cap = cap;
    listaLinear->ehOrd = ehOrd;
    listaLinear->tam = 0;

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

//////////////////////////////////////////////////////////////////////////////
void limpaListaLinear(t_ListaLinear *listaLinear) {
    if (listaLinear) {
        if (listaLinear->lista) {
            free(listaLinear->lista);
        }
        free(listaLinear);
    }
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

int insereNaLista(t_Fipe fipe, t_ListaLinear *lista, int ehOrd) {
    // Verificar se a lista est� vazia ou se j� est� cheia
    if (lista == NULL || lista->tam == lista->cap) {
        return 0;
    }

    // Realocar mem�ria se necess�rio
    if (lista->tam == 0) {
        lista->lista = (t_Fipe *)malloc(sizeof(t_Fipe));
    } else {
        lista->lista = (t_Fipe *)realloc(lista->lista, (lista->tam + 1) * sizeof(t_Fipe));
    }

    // Verificar se a realoca��o foi bem-sucedida
    if (lista->lista == NULL) {
        return 0;
    }

    /*O loop while continua incrementando a vari�vel posicao enquanto a condi��o for verdadeira.
    enquanto a posi��o atual ainda estiver dentro dos limites da lista e o campo nCdg do registro fipe for maior que o campo nCdg do registro na posi��o atual, o loop continuar� avan�ando e a vari�vel posicao cont�m a posi��o correta para inserir o novo registro fipe na lista ordenada.*/
    if (ehOrd) {
        int posicao = 0;
        while (posicao < lista->tam && fipe.nCdg > lista->lista[posicao].nCdg) {
            posicao++;
        }

        // Mover os elementos para a direita para abrir espa�o para o novo registro
        for (int i = lista->tam; i > posicao; i--) {
            lista->lista[i] = lista->lista[i - 1];
        }

        // Inserir o novo registro na posi��o correta
        lista->lista[posicao] = fipe;
    } else {
        // Inserir o novo registro na lista
        lista->lista[lista->tam] = fipe;
    }

    lista->tam++;

    return 1;
}

/////////////////////////////////////
/*Para Apresenta��o dia 17/04/2023*/
///////////////////////////////////
// Implementa��o da fun��o criaFilaLinear
t_FilaLinear* criaFilaLinear(int cap) {
    // Alocar mem�ria
    t_FilaLinear *fila = (t_FilaLinear *) malloc(sizeof(t_FilaLinear));

    // Verificar se a mem�ria foi alocada corretamente
    if (fila == NULL) {
        printf("Erro ao alocar mem�ria para a fila.\n");
        return NULL;
    }

    // Inicializar os atributos da inst�ncia
    fila->cap = cap;
    fila->ini = 0;
    fila->fim = 0;
    fila->dados = (int *) malloc(cap * sizeof(int));

    // Verificar se a mem�ria foi alocada corretamente para os dados
    if (fila->dados == NULL) {
        printf("Erro ao alocar mem�ria para os dados da fila.\n");
        free(fila);
        return NULL;
    }

    return fila;
}

// Implementa��o da fun��o criaPilhaLinear
t_pilhaLinear* criaPilhaLinear(int cap) {
    // Alocar mem�ria
    t_pilhaLinear *pilha = (t_pilhaLinear *) malloc(sizeof(t_pilhaLinear));

    // Verificar se a mem�ria foi alocada corretamente
    if (pilha == NULL) {
        printf("Erro ao alocar mem�ria para a pilha.\n");
        return NULL;
    }

    // Inicializar os atributos da inst�ncia
    pilha->cap = cap;
    pilha->topo = -1; //Isso indica que a pilha est� vazia, ou seja, nenhum elemento foi inserido ainda.
    pilha->pilha = (int *) malloc(cap * sizeof(int));

    // Verificar se a mem�ria foi alocada corretamente para os dados
    if (pilha->pilha == NULL) {
        printf("Erro ao alocar mem�ria para os dados da pilha.\n");
        free(pilha); // Libera a mem�ria alocada para a estrutura 'pilha' dessa forma eu garanto que a mem�ria alocada foi liberada corretamente mesmo que haja um problema na aloca��o de mem�ria para os dados da pilha.
        return NULL;
    }

    return pilha;
}

///////////////////////////////////////////////////////////////////////////
//Fun��es feitas por Henio e Isaac
///////////////////////////////////////////////////////////////////////////
int estacheia ( t_pilhaLinear *p ){

	if (p->topo == p->cap - 1)

		return 1;

	else

		return 0;

}

void empilhar(t_Fipe lk, t_pilhaLinear *p, int cap) {

        p->topo++;
        p->pilha[p->topo] = lk;
        printf("Empilhado\n");

    return 0;
}

/*void RemoverdaPilha(t_fipe lk, t_pilhalinear *p, int cap,int topo){
    if (p -> topo == cap - cap){
        printf("Erro: Pilha Vazia");
        exit(-1)
    }else{
        p -> topo--;
    }
}*/
