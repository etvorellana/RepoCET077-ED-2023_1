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
    //printf("limpaFipe -");
    for(int j = 0; j < tam; j++)
    {
        limpaRegistro(fipe[j]);
    }
    free(fipe);
    //printf("limpaFipe concluido\n");
}

void limpaRegistro(t_Fipe fipe)
{
    //printf("limpaRegistro\n");
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

int incRegistro(t_Fipe book, t_Fipe* lista, int* tam)
{
    int pos = buscaPorId(lista, *tam, book.nCdg); // procura o registro na lista

    if (pos != -1) // se o registro já existe na lista
    {
        return 0; // não adiciona o registro
    }

    // copia o registro para a posição *tam
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
    int i = buscIdOrd(idBusca, fipe, (*tam));
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
    // Verificar se a lista está vazia ou se já está cheia
    if (lista == NULL || lista->tam == lista->cap) {
        return 0;
    }

    // Realocar memória se necessário
    if (lista->tam == 0) {
        lista->lista = (t_Fipe *)malloc(sizeof(t_Fipe));
    } else {
        lista->lista = (t_Fipe *)realloc(lista->lista, (lista->tam + 1) * sizeof(t_Fipe));
    }

    // Verificar se a realocação foi bem-sucedida
    if (lista->lista == NULL) {
        return 0;
    }

    /*O loop while continua incrementando a variável posicao enquanto a condição for verdadeira.
    enquanto a posição atual ainda estiver dentro dos limites da lista e o campo nCdg do registro fipe for maior que o campo nCdg do registro na posição atual, o loop continuará avançando e a variável posicao contém a posição correta para inserir o novo registro fipe na lista ordenada.*/
    if (ehOrd) {
        int posicao = 0;
        while (posicao < lista->tam && fipe.nCdg > lista->lista[posicao].nCdg) {
            posicao++;
        }

        // Mover os elementos para a direita para abrir espaço para o novo registro
        for (int i = lista->tam; i > posicao; i--) {
            lista->lista[i] = lista->lista[i - 1];
        }

        // Inserir o novo registro na posição correta
        lista->lista[posicao] = fipe;
    } else {
        // Inserir o novo registro na lista
        lista->lista[lista->tam] = fipe;
    }

    lista->tam++;

    return 1;
}

/////////////////////////////////////
/*Para Apresentação dia 17/04/2023*/
///////////////////////////////////
// Implementação da função criaFilaLinear

t_FilaLinear* criaFilaLinear(int cap) {
    // Alocar memória
    t_FilaLinear *fila = (t_FilaLinear *) malloc(sizeof(t_FilaLinear));

    // Verificar se a memória foi alocada corretamente
    if (fila == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        return NULL;
    }

    // Inicializar os atributos da instância
    fila->cap = cap;
    fila->ini = 0;
    fila->fim = 0;
    fila->dados = (t_Fipe *) malloc(cap * sizeof(t_Fipe));

    // Verificar se a memória foi alocada corretamente para os dados
    if (fila->dados == NULL) {
        printf("Erro ao alocar memória para os dados da fila.\n");
        free(fila);
        return NULL;
    }

    return fila;
}

// Implementação da função criaPilhaLinear
t_pilhaLinear* criaPilhaLinear(int cap) {
    // Alocar memória
    t_pilhaLinear *pilha = (t_pilhaLinear *) malloc(sizeof(t_pilhaLinear));

    // Verificar se a memória foi alocada corretamente
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        return NULL;
    }

    // Inicializar os atributos da instância
    pilha->cap = cap;
    pilha->topo = -1; //Isso indica que a pilha está vazia, ou seja, nenhum elemento foi inserido ainda.
    pilha->pilha = (t_Fipe *) malloc(cap * sizeof(t_Fipe));

    // Verificar se a memória foi alocada corretamente para os dados
    if (pilha->pilha == NULL) {
        printf("Erro ao alocar memória para os dados da pilha.\n");
        free(pilha); // Libera a memória alocada para a estrutura 'pilha' dessa forma eu garanto que a memória alocada foi liberada corretamente mesmo que haja um problema na alocação de memória para os dados da pilha.
        return NULL;
    }

    return pilha;
}

///////////////////////////////////////////////////////////////////////////
//Funções feitas por Henio e Isaac
///////////////////////////////////////////////////////////////////////////
int estacheia (t_pilhaLinear *p)
{

	if (p->topo == p->cap-1)
		return 1;
	else
		return 0;
}

int insereNaPilha(t_Fipe fipe, t_pilhaLinear* pilha)
{
    if (estacheia(pilha))
        return 0;

    pilha->topo++;
    pilha->pilha[pilha->topo] = fipe;
    return 1;
}

t_Fipe* RemoverdaPilha(t_pilhaLinear *p)
{
    if (p->topo == 0){
        printf("Erro: Pilha Vazia\n");
        return NULL;
    }
    t_Fipe* removido = &p->pilha[p->topo];
    p->topo--;
    return removido;
}

///////////////////////////////////////////////////////////////////
///////////////////////// FUNÇÕES DA FILA /////////////////////////

void cpyt_Fipe(t_Fipe src, t_Fipe *dest) {
    dest->nCdg = (char*) malloc(strlen(src.nCdg) + 1);
    strcpy(dest->nCdg, src.nCdg);
    dest->codigofp = (char*) malloc(strlen(src.codigofp) + 1);
    strcpy(dest->codigofp, src.codigofp);
    dest->marca = (char*) malloc(strlen(src.marca) + 1);
    strcpy(dest->marca, src.marca);
    dest->modelo = (char*) malloc(strlen(src.modelo) + 1);
    strcpy(dest->modelo, src.modelo);
    dest->anoModelo = src.anoModelo;
    dest->mesReferencia = src.mesReferencia;
    dest->anoReferencia = src.anoReferencia;
    dest->valor = src.valor;
}


int InserirNaFila (t_FilaLinear *fila, t_Fipe fipe)
{
    if (fila->fim - fila->ini == fila->cap)//checa se a fila esta cheia
        return 0;

    int aux = fila->ini;
    while (aux<fila->fim){      //checa se o elemento já existe na fila
        if (!(strcmp(fila->dados[aux%fila->cap].nCdg, fipe.nCdg))){
            return 0;
        }
        aux++;
    }

    fila->dados[fila->fim%fila->cap] = fipe;
    fila->fim++;
    /*if(fila->fim > 90000 || fila->ini > 90000){
        int aux = fila->fim - fila ->ini;
        fila->ini = fila->ini%fila->cap;
        fila->fim = fila->ini+aux;
    }*/

    return 1;
}

t_Fipe* RemoveDaFila (t_FilaLinear* fila)
{
    if (fila->fim == fila->ini)
        return NULL;

    t_Fipe* removido = &fila->dados[fila->ini%fila->cap];
    fila->ini++;

    return removido;
}

////////////////////////////////////////////////////////////////
//////////////// LISTAS-PILHAS-FILAS ENCADEADAS ////////////////


PNoFipeSE alocaNoFipeSE(void)
{
    PNoFipeSE p = (PNoFipeSE) malloc(sizeof(t_NoFipeSE));
    p->prox = NULL;
    return p;
}

void destroiNoFipeSE(PNoFipeSE p)
{
    free(p);
}

PNoFipeSE criaListaSEDeListaLinear(t_Fipe *lista, int tam) {
    PNoFipeSE head;
    if (tam == 0)
        return NULL;
    else {
        head = alocaNoFipeSE();
        cpyt_Fipe(lista[0], &head->fipe);
        PNoFipeSE p = head;
        for (int i = 1; i < tam; i++) {
            p->prox = alocaNoFipeSE();
            p = p->prox;
            cpyt_Fipe(lista[i], &p->fipe);
        }
        return head;
    }
}

void destroiListaSE(PNoFipeSE head)
{
    PNoFipeSE p = head;
    while (p != NULL)
    {
        PNoFipeSE aux = p;
        p = p->prox;
        destroiNoFipeSE(aux);
    }
}

int incRegistroSE(t_Fipe fipe, PNoFipeSE* head)
{
    PNoFipeSE p = buscaPorIDSE(fipe.nCdg, (*head));
    if (p == NULL)
    {
        p = alocaNoFipeSE();
        cpyt_Fipe(fipe, &p->fipe);
        p->prox = *head;
        *head = p;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

PNoFipeSE buscaPorIDSE(char *nCdg, PNoFipeSE head)
{
    PNoFipeSE p = head;
    while (p != NULL)
    {
        if (strcmp(nCdg, p->fipe.nCdg) <= 0)
            return p;
        p = p->prox;
    }
    return NULL;
}

int incRegistroOrdSE(t_Fipe fipe, PNoFipeSE* head)
{
    PNoFipeSE p = *head;
    if (strcmp(fipe.nCdg, p->fipe.nCdg) < 0){
        PNoFipeSE novo = alocaNoFipeSE();
        cpyt_Fipe(fipe, &novo->fipe);
        novo->prox = *head;
        *head = novo;
        return TRUE;
    }else{
        while (p->prox != NULL && strcmp(fipe.nCdg, p->prox->fipe.nCdg) > 0)
            p = p->prox;
        if (p->prox == NULL || strcmp(fipe.nCdg, p->prox->fipe.nCdg) < 0)
        {
            PNoFipeSE novo = alocaNoFipeSE();
            cpyt_Fipe(fipe, &novo->fipe);
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

int remRegistroOrdSE(char* nCdg, PNoFipeSE* head)
{
    PNoFipeSE p = *head;
    if (strcmp(nCdg, p->fipe.nCdg) == 0){
        *head = p->prox;
        destroiNoFipeSE(p);
        return TRUE;
    }else{
        while (p->prox != NULL && strcmp(nCdg, p->prox->fipe.nCdg) > 0)
            p = p->prox;
        if (p->prox != NULL && strcmp(nCdg, p->prox->fipe.nCdg) == 0)
        {
            PNoFipeSE aux = p->prox;
            p->prox = aux->prox;
            destroiNoFipeSE(aux);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}




//////////////////////////////

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


int empilha(t_Fipe fipe, PilhaEnc* pilha)
{
    PNoFipeSE p = alocaNoFipeSE();
    cpyt_Fipe(fipe, &p->fipe);
    p->prox = pilha->topo;
    pilha->topo = p;
    pilha->tam++;
    return TRUE;
}


t_Fipe desempilha(PilhaEnc* pilha){
    t_Fipe fipe;
    if (pilhaVazia(pilha))
    {
        printf("Pilha vazia!\n");
        return fipe;
    }
    else
    {
        PNoFipeSE p = pilha->topo;
        pilha->topo = p->prox;
        pilha->tam--;
        cpyt_Fipe(p->fipe, &fipe);
        destroiNoFipeSE(p);
        return fipe;
    }
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

int enfileira(t_Fipe fipe, FilaEnc* fila)
{
    PNoFipeSE p = alocaNoFipeSE();
    cpyt_Fipe(fipe, &p->fipe);
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

t_Fipe desemfileira(FilaEnc* fila)
{
    t_Fipe fipe;
    if (filaVazia(fila))
    {
        printf("Fila vazia!\n");
        return fipe;
    }
    else
    {
        PNoFipeSE p = fila->ini;
        fila->ini = p->prox;
        fila->tam--;
        cpyt_Fipe(p->fipe, &fipe);
        destroiNoFipeSE(p);
        return fipe;
    }
}


void imprimeLista(PNoFipeSE head) {
    PNoFipeSE p = head;
    while (p != NULL) {
        printf("-------\n");
        printRegistro(p->fipe);
        p = p->prox;
    }
}

void imprimeFila(FilaEnc* fila) {
    PNoFipeSE p = fila->ini;
    while (p != NULL) {
        printf("------------\n");
        printRegistro(p->fipe);
        p = p->prox;
    }
}

void imprimePilha(PilhaEnc* pilha) {
    if(pilhaVazia(pilha)) {
        printf("Pilha vazia\n");
        return;
    }
    printf("Pilha (do topo ah base):\n");
    for(PNoFipeSE p = pilha->topo; p != NULL; p = p->prox) {
        printf("------------\n");
        printRegistro(p->fipe);
    }
}


