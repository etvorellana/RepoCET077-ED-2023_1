#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bidefun.h"

int main(void) {

  TSongs *acervo;
  int tam = 0;

  acervo = carregaDados("Data/newSongs.csv", &tam);

  // Atividada para o dia 27/03
  // INCLUSAO
  int newtam = tam / 3, tamaux = 0; 
  TSongs *newacervo = (TSongs *)malloc(newtam * sizeof(TSongs)); 
  int existe, acertos = 0, tentativas = 0;
  int resp = buscaBinporPOSICAO(14000, acervo, tam, &existe);
  printf("BUSCA: %d", resp);
   printf("\ntamanho original = %d\n",tam);
  if(RemRegistro_nao_ordenado(acervo[tam - 5], acervo , &tam)){
       printf("\nRemoção Feita\nNOVO TAMANHO => %d\n",tam);
  }
  if(RemRegistro_ordenado(acervo[tam - 4], acervo , &tam)){
       printf("\nRemoção Feita\nNOVO TAMANHO => %d\n",tam);
  }
  
/*
  while (tamaux < newtam) {
    int NA = rand() % 20000;
    if (NA >= 0 && NA < tam) {
      tentativas++;
      //printf("Tentativa: %d | Numero: %d\n\n", tentativas, NA);
      if (IncRegistro(acervo[NA], newacervo, &tamaux)) {
        printf("Sucesso inclusao: %d\n\n", acertos);
        acertos++;
      }
    }
  }
  printf("Na inclusão\nForam %d Tentativas!\nForam %d Acertos!\n", tentativas, acertos);


// REMOCAO
  acertos = 0, tentativas = 0;
  while (acertos != newtam){
    int NA = rand() % 20000;
    if (NA >= 0 && NA < tam) {
      tentativas++;
      //printf("Tentativa: %d\n\n", tentativas);
      if (RemRegistro_nao_ordenado(newacervo[NA], newacervo, &tamaux)) {
        //printf("Sucesso remocão: %d\n\n", acertos);
        acertos++;
      }
    }
  }
  printf("Na exclusão\nForam %d Tentativas!\nForam %d Acertos!", tentativas, acertos);
*/
  //-----------------------------------------------------------
  // Atividade para o dia 03/04
  // busca binaria?
  //-----------------------------------------------------------
  limpaAcervo(acervo, tam);
  limpaAcervo(newacervo, newtam);
}
