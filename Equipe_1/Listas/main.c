#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(void)
{
  Games *jogos;
  int tam;
  jogos = carregaDados("../../Data/Grupo1DataSet.csv", &tam);

  // Criando nossa nova lista com 100 jogos
  Games *jogos02;
  int tam02 = 0;          // tamanho de jogos 02
  int capacidade02 = 100; // capacidade de jogos 02
  // alocando espaço para o novo array
  jogos02 = IniciaLista(capacidade02);

  int try = 0, ok = 0;
  while (tam02 < capacidade02)
  { // enquanto não estiver cheia{
    // gera um índice aleatória do jogos
    int idx = rand() % tam;
    try++;
    if (incJogo(jogos[idx], jogos02, &tam02) == 1)
      ok++;
  }

  printf("Foram realizadas %d tentativas de inclusão\n", try);
  printf("Foram incluídos %d registros na lista\n", ok);

  // Buscando jogos por id
  try = 0, ok = 0;
  while (tam02 > ok)
  {
    // gera um índice aleatória do jogos
    int idx = rand() % tam;
    try++;
    jogos02[tam02].ID = jogos[idx].ID;
    if (buscaPorId(jogos[idx].ID, jogos02, tam02) < tam02)
      ok++;
  }

  printf("Foram realizadas %d tentativas de busca\n", try);
  printf("Foram achados %d registros na lista\n", ok);

  // removendo jogos
  try = 0, ok = 0;
  while (tam02 > 0)
  {
    int idx = rand() % tam;
    try++;
    if (remJogo(jogos[idx], jogos02, &tam02) == 1)
      ok++;
  }

  printf("Foram realizadas %d tentativas de remoção\n", try);
  printf("Foram removidos %d registros na lista\n", ok);

  // CRIANDO UMA LISTA COM 100 JOGOS ORDENADOS

  Games *jogos03;
  int tam03 = 0;          // tamanho de jogos 02
  int capacidade03 = 100; // capacidade de jogos 02
  // alocando espaço para o novo array
  jogos03 = IniciaLista(capacidade03);

  int try2 = 0, ok2 = 0;
  while (tam03 < capacidade03)
  { // enquanto não estiver cheia{
    // gera um índice aleatória do jogos
    int idx = rand() % tam;
    try2++;
    if (incJogoOrdenado(jogos[idx], jogos03, &tam03))
      ok2++;
  }

  printf("\n\nForam realizadas %d tentativas de inclusão na lista ordenada\n", try2);
  printf("Foram incluídos %d registros na lista ordenada\n", ok2);

  // Buscando jogos por id
  try2 = 0, ok2 = 0;
  while (tam03 > ok2)
  {
    // gera um índice aleatória do jogos
    int idx = rand() % tam;
    try2++;
    int pos = buscaBinRecPorId(jogos[idx].ID, jogos03, 0, tam03);
    if (jogos03[pos].ID == jogos[idx].ID)
      ok2++;
  }

  printf("Foram realizadas %d tentativas de busca na lista ordenada\n", try2);
  printf("Foram achados %d registros na lista ordenada\n", ok2);

  // removendo jogos
  try2 = 0, ok2 = 0;
  while (tam03 > 0)
  {
    int idx = rand() % tam;
    try2++;
    if (remJogoOrdenado(jogos[idx], jogos03, &tam03) == 1)
      ok2++;
  }

  printf("Foram realizadas %d tentativas de remoção\n", try2);
  printf("Foram removidos %d registros na lista\n", ok2);

  limpaJogos(jogos, tam);
  return 0;
}
