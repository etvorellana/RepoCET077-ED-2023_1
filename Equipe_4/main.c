#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bidefun.h"

int main(void) {
  printf("Ola, vamos criar sua lista, aguarde\n...\n");

  TSongs *acervo;
  int tam = 0;

  acervo = carregaDados("Data/newSongs.csv", &tam);
  //-----------------------------------------------------------
  // Atividade para o dia 10/04
  // cria a lista
  TListaLinear *lista = criaListaLinear(50, 1);
  printf("--- Lista Criada ---\n...\n");
  // insere na lista
  int cont = 0;
  while (cont < 50) {
    int NA = rand() % 1000;
    insereNaLista(acervo[NA], lista);
    cont++;
  }
  printf("--- Lista Populada ---\n...\n");
  // busca
  int pos = 0;
  while (1) {
    printf("\nInsira o ranking da musica que deseja buscar da lista(-1 para "
           "encerrar a busca)\n");
    scanf("%d", &pos);
    if (pos == -1) {
      break;
    }
    buscaNaLista(acervo[pos], lista);
  }
  // remove na lista
  cont = 0;
  while (cont < 50) {
    int NA = rand() % 1000;
    removeDaLista(acervo[NA], lista);

    cont++;
  }
  printf("--- Lista Esvaziada ---");

  //
  //-----------------------------------------------------------
  limpaAcervo(acervo, tam);
  // limpaAcervo(newacervo, newtam);

  return 0;
}
