#include <stdio.h>
#include <stdlib.h>

#include "datafunAvl.h"

typedef struct No
{
  t_Fipe dados;
  struct No *esquerda;
  struct No *direita;
  int altura;
} No;

// Protótipos das funções
void limpaRegistro(t_Fipe fipe);
t_Fipe *carregaDados(char *arquivo, int *tam);
int max(int a, int b);
int altura(No *no);
No *calcularBalanceamento(No *no);
No *criarNo(t_Fipe *chave);
No *inserirNo(No *no, t_Fipe *chave);
No *encontrarNoMinimo(No *no);
No *removerNo(No *raiz, int chave);
No *buscarNo(No *raiz, int chave);
void percursoEmOrdem(No *raiz);
void percursoPreOrdem(No *raiz);
void percursoPosOrdem(No *raiz);
No *rotacaoEsqDir(No *k);
No *rotacaoDirEsq(No *m);
No *rotacaoEsquerda(No *x);

No *rotacaoDireita(No *y);
void cpyt_Fipe(t_Fipe src, t_Fipe *dest);

int main()
{
  No *raiz = NULL;
  int tam = CSVSIZE;

  t_Fipe *fipe = carregaDados("datasetFipe.csv", &tam);

  // Inserindo os elementos na �rvore
  for (int i = 0; i < tam; i++)
  {
    raiz = inserirNo(raiz, &fipe[i]);
  }

  // Exemplo de busca de um nó na árvore
  No *resultadoBusca = buscarNo(raiz, 40);
  if (resultadoBusca != NULL)
  {
    printf("Nó encontrado: %d\n", resultadoBusca->dados.nCdg);
  }
  else
  {
    printf("Nó não encontrado.\n");
  }

  // Exemplo de remoção de um nó na árvore
  raiz = removerNo(raiz, 40);
  resultadoBusca = buscarNo(raiz, 40);
  if (resultadoBusca != NULL)
  {
    printf("Nó encontrado: %d\n", resultadoBusca->dados.nCdg);
  }
  else
  {
    printf("Nó não encontrado.\n");
  }

  // Exemplo de percurso em ordem
  printf("Percurso em ordem: ");
  percursoEmOrdem(raiz);
  printf("\n");

  // Exemplo de percurso em pré-ordem
  printf("Percurso em pré-ordem: ");
  percursoPreOrdem(raiz);
  printf("\n");

  // Exemplo de percurso em pós-ordem
  printf("Percurso em pós-ordem: ");
  percursoPosOrdem(raiz);
  printf("\n");

  return 0;
}

t_Fipe *carregaDados(char *arquivo, int *tam)
{
  t_Fipe *fipe;
  FILE *fp;

  char str[900];
  int i = 0;

  fipe = (t_Fipe *)malloc(CSVSIZE * sizeof(t_Fipe));

  if (fipe == NULL)
  {
    printf("ERRO! Falha ao alocar memoria!\n");
    exit(1);
  }

  fp = fopen(arquivo, "r");

  if (fp == NULL)
  {
    printf("ERRO! Arquivo nao pode ser aberto.\n");
    exit(1);
  }

  char *ok;
  ok = fgets(str, 900, fp);
  if (ok == NULL)
  {
    printf("Erro lendo o cabecalho do CSV!!!\n");
    exit(1);
  }

  i = 0;
  char sep[] = ",";

  while (!feof(fp) && i < CSVSIZE)
  {
    ok = fgets(str, 900, fp);
    if (ok)
    {
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

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int altura(No *no)
{
  if (no == NULL)
  {
    return -1;
  }
  return no->altura;
}

short balanceamento(No *no)
{
  if (no)
    return (altura(no->esquerda) - altura(no->direita));
  else
    return 0;
}

No *calcularBalanceamento(No *no)
{
  short fb = balanceamento(no);
  short fb_dir = balanceamento(no->direita);
  short fb_esq = balanceamento(no->esquerda);

  if (fb < -1 && fb_dir <= 0)
    no = rotacaoEsquerda(no);
  else if (fb > 1 && fb_esq >= 0)
    no = rotacaoDireita(no);
  else if (fb > 1 && fb_esq < 0)
    no = rotacaoEsqDir(no);
  else if (fb < -1 && fb_dir > 0)
    no = rotacaoDirEsq(no);

  return no;
}
No *criarNo(t_Fipe *chave)
{
  No *novoNo = (No *)malloc(sizeof(No));

  novoNo->dados.nCdg = chave;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  novoNo->altura = 0;

  return novoNo;
}

No *rotacaoDireita(No *y)
{

  No *esq, *dirDaesq;

  esq = y->esquerda;

  dirDaesq = esq->direita;

  esq->direita = y;
  short a = altura(y->esquerda);
  short b = altura(y->direita);
  y->altura = ((a > b) ? a : b) + 1;
  a = altura(esq->esquerda);
  b = altura(esq->direita);
  esq->altura = ((a < b) ? a : b) + 1;

  return esq;
}

No *rotacaoEsquerda(No *x)
{

  No *dir, *esqDadir;

  dir = x->direita;

  esqDadir = dir->esquerda;
  dir->esquerda = x;

  short a = altura(x->esquerda);
  short b = altura(x->direita);
  x->altura = ((a > b) ? a : b) + 1;
  a = altura(dir->esquerda);
  b = altura(dir->direita);
  dir->altura = ((a < b) ? a : b) + 1;

  return dir;
}

No *rotacaoEsqDir(No *k)
{
  k->esquerda = rotacaoEsquerda(k->esquerda);
  return rotacaoDireita(k);
}
No *rotacaoDirEsq(No *m)
{
  m->direita = rotacaoDireita(m->direita);
  return rotacaoEsquerda(m);
}

No *inserirNo(No *no, t_Fipe *chave)
{
  if (no == NULL)
  {
    return criarNo(chave);
  }
  else
  {

    if (strcmp(chave->nCdg, no->dados.nCdg) < 0)
    {
      no->esquerda = inserirNo(no->esquerda, chave);
    }
    else if (strcmp(chave->nCdg, no->dados.nCdg) > 0)
    {
      no->direita = inserirNo(no->direita, chave);
    }
  }
  short a = altura(no->esquerda);
  short b = altura(no->direita);
  no->altura = ((a > b) ? a : b) + 1;
  no = calcularBalanceamento(no);
  return no;
}
No *encontrarNoMinimo(No *no)
{
  No *atual = no;
  while (atual && atual->esquerda != NULL)
  {
    atual = atual->esquerda;
  }
  return atual;
}

No *removerNo(No *raiz, int chave)
{
  if (raiz == NULL)
  {
    return NULL;
  }
   else if (raiz->dados.nCdg == chave)
    {
        if (raiz->direita == NULL && raiz->esquerda == NULL)
        {
            limpaRegistro(raiz->dados);
            free(raiz);
            return NULL;
        }
        else if (raiz->esquerda == NULL)
        {
            No *aux = raiz->direita;
            limpaRegistro(raiz->dados);
            free(raiz);
            raiz = aux;
        }
        else if (raiz->direita == NULL)
        {
            No *aux = raiz->esquerda;
            limpaRegistro(raiz->dados);
            free(raiz);
            raiz = aux;
        }
        else
        {
            No *aux = raiz->direita;
            while (aux->esquerda != NULL)
            {
                aux = aux->esquerda;
            }
            cpyt_Fipe(aux->dados, &(raiz->dados));
            raiz->direita = removerNo(raiz->direita, aux->dados.nCdg);
        }
    }
    else if (chave < raiz->dados.nCdg)
    {
        raiz->esquerda = removerNo(raiz->esquerda, chave);
    }
    else if (chave > raiz->dados.nCdg)
    {
        raiz->direita = removerNo(raiz->direita, chave);
    }

    short int a = altura(raiz->esquerda);
    short int b = altura(raiz->direita);

    raiz->altura = ((a > b) ? a : b) + 1;
    raiz = calcularBalanceamento(raiz);
    return raiz;
}

No *buscarNo(No *raiz, int chave)
{
  if (raiz == NULL || raiz->dados.nCdg == chave)
  {
    return raiz;
  }

  if (chave < raiz->dados.nCdg)
  {
    return buscarNo(raiz->esquerda, chave);
  }
  else if (chave > raiz->dados.nCdg)
  {
    return buscarNo(raiz->direita, chave);
  }
  return raiz;
}

void percursoEmOrdem(No *raiz)
{
  if (raiz != NULL)
  {
    percursoEmOrdem(raiz->esquerda);
    printf("%d ", raiz->dados.nCdg);
    percursoEmOrdem(raiz->direita);
  }
}

void percursoPreOrdem(No *raiz)
{
  if (raiz != NULL)
  {
    printf("%d ", raiz->dados.nCdg);
    percursoPreOrdem(raiz->esquerda);
    percursoPreOrdem(raiz->direita);
  }
}

void percursoPosOrdem(No *raiz)
{
  if (raiz != NULL)
  {
    percursoPosOrdem(raiz->esquerda);
    percursoPosOrdem(raiz->direita);
    printf("%d ", raiz->dados.nCdg);
  }
}
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
void limpaRegistro(t_Fipe fipe)
{
    //printf("limpaRegistro\n");
    free(fipe.nCdg);
    free(fipe.modelo);
    free(fipe.marca);
    free(fipe.codigofp);

    // free(fipe);
}

