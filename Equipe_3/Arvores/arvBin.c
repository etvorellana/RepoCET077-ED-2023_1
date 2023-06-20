#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataFunBin.h"

typedef struct No
{
  t_Fipe *dados;
  struct No *esquerda;
  struct No *direita;
} No;

// Prot�tipos das fun��es
No *criarNo(t_Fipe *chave);
No *inserirNo(No *raiz, t_Fipe *chave);
No *encontraNoMinimo(No *no);
No *removerNo(No *raiz, int chave);
No *buscarNo(No *raiz, int chave);
void percursoEmOrdem(No *raiz);
void percursoPreOrdem(No *raiz);
void percursoPosOrdem(No *raiz);

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

  // Exemplo de busca de um n� na �rvore
  No *resultadoBusca = buscarNo(raiz, 97);
  if (resultadoBusca != NULL)
  {
    printf("No encontrado: %s\n", resultadoBusca->dados->nCdg);
  }
  else
  {
    printf("No nao encontrado.\n");
  }

  // Exemplo de remo��o de um n� na �rvore
  raiz = removerNo(raiz, 910);
  resultadoBusca = buscarNo(raiz, 910);
  if (resultadoBusca != NULL)
  {
    printf("No encontrado: %s\n", resultadoBusca->dados->nCdg);
  }
  else
  {
    printf("No nao encontrado.\n");
  }

  // Exemplo de percurso em Ordem
  printf("Percurso em ordem: ");
  percursoEmOrdem(raiz);
  printf("\n\n\n");

  // Exemplo de percurso pre-ordem
  printf("Percurso pre-ordem: ");
  percursoPreOrdem(raiz);
  printf("\n\n\n");

  // Exemplo de percurso pos-ordem
  printf("Percurso pos-ordem: ");
  percursoPosOrdem(raiz);
  printf("\n\n\n");

  return 0;
}

// Criar n�
No *criarNo(t_Fipe *chave)
{
  No *novoNo = (No *)malloc(sizeof(No));
  novoNo->dados = chave;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  return novoNo;
}

// Inserir n�
No *inserirNo(No *raiz, t_Fipe *chave)
{
  if (raiz == NULL)
  {
    return criarNo(chave);
  }

  if (strcmp(chave->nCdg, raiz->dados->nCdg) < 0)
  {
    raiz->esquerda = inserirNo(raiz->esquerda, chave);
  }
  else if (strcmp(chave->nCdg, raiz->dados->nCdg) > 0)
  {
    raiz->direita = inserirNo(raiz->direita, chave);
  }

  return raiz;
}

// Encontrar o menor n�
No *encontraNoMinimo(No *no)
{
  No *atual = no;
  while (atual && atual->esquerda != NULL)
  {
    atual = atual->esquerda;
  }
  return atual;
}

// Remover n�
No *removerNo(No *raiz, int chave)
{
  if (raiz == NULL)
  {
    return raiz;
  }

  if (chave < atoi(raiz->dados->nCdg))
  {
    raiz->esquerda = removerNo(raiz->esquerda, chave);
  }
  else if (chave > atoi(raiz->dados->nCdg))
  {
    raiz->direita = removerNo(raiz->direita, chave);
  }
  else
  {
    if (raiz->esquerda == NULL)
    {
      No *temp = raiz->direita;
      free(raiz);
      return temp;
    }
    else if (raiz->direita == NULL)
    {
      No *temp = raiz->esquerda;
      free(raiz);
      return temp;
    }

    No *temp = encontraNoMinimo(raiz->direita);
    raiz->dados = temp->dados;
    raiz->direita = removerNo(raiz->direita, atoi(temp->dados->nCdg));
  }

  return raiz;
}

// Buscar n�
No *buscarNo(No *raiz, int chave)
{
  if (raiz == NULL || atoi(raiz->dados->nCdg) == chave)
  {
    return raiz;
  }

  if (chave < atoi(raiz->dados->nCdg))
  {
    return buscarNo(raiz->esquerda, chave);
  }

  return buscarNo(raiz->direita, chave);
}

void percursoEmOrdem(No *raiz)
{
  if (raiz != NULL)
  {
    percursoEmOrdem(raiz->esquerda);
    printf("%s ", raiz->dados->nCdg);
    percursoEmOrdem(raiz->direita);
  }
}

void percursoPreOrdem(No *raiz)
{
  if (raiz != NULL)
  {
    printf("%s ", raiz->dados->nCdg);
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
    printf("%s ", raiz->dados->nCdg);
  }
}