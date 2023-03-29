
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bidefun.h"

int main(void) {

  TSongs *acervo;
  int id = 1, tam = 0;
  int total, t = 100;

  acervo = carregaDados("Data/newSongs.csv", &tam);

  // Atividada para o dia 27/03
  // INCLUSAO
  int newtam = tam / 3, tamaux = 0; // defino o tamanho para 1/3 do acervo
  TSongs *newacervo = (TSongs *)malloc(newtam * sizeof(TSongs)); // nova lista
  int acertos = 0, tentativas = 0;

  while (tamaux < newtam) {
    int NA = rand() % 20000;
    //printf("%d\n\n", tamaux);
    if (NA >= 0 && NA < tam) {
      tentativas++;
      //printf("Tentativa: %d\n\n", tentativas);
      if (IncRegistro(acervo[NA], newacervo, &tamaux)) {
        //printf("Sucesso: %d\n\n", acertos);
        acertos++;
      }
    }
  }
  printf("Na inclusão\nForam %d Tentativas!\nForam %d Acertos!\n", tentativas, acertos);

// ainda nao foi implementado o sistema de remoçao
  acertos = 0, tentativas = 0;
  while (0){
    int NA = rand() % 20000;
    if (NA >= 0 && NA < tam) {
      tentativas++;
      //printf("Tentativa: %d\n\n", tentativas);
      if (RemRegistro(acervo[NA], newacervo, &tamaux)) {
        //printf("Sucesso: %d\n\n", acertos);
        acertos++;
      }
    }
  }
  printf("Na exclusão\nForam %d Tentativas!\nForam %d Acertos!", tentativas, acertos);
  limpaAcervo(acervo, tam);
  limpaAcervo(newacervo, newtam);
}
