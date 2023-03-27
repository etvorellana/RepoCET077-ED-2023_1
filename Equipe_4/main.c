
#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h"

int main(void) {

  TSongs *acervo, *subacervo;
  int id = 1, tam;
  char *nome;
  int total, t = 100;

  acervo = carregaDados("Data/songs.csv", &tam);
  subacervo = sub_lista(acervo, t, &total);
  int i = 1;
  while (i < t) {
    printf("Dado %d \n", i + 1);
    printf("Position: %d\n", subacervo[i].Position);
    printf("Artista: %s\n", subacervo[i].ArtistName);
    printf("Musica: %s\n", subacervo[i].SongName);
    printf("Dias no top 10: %d\n", subacervo[i].Days);
    printf("Vezes no top 10: %2.f\n", subacervo[i].Top10Times);
    printf("Maior Posicao: %d\n", subacervo[i].PeakPosition);
    printf("Maior Posicao x vezes: %s\n", subacervo[i].PeakPositionXtimes);
    printf("Pico de reproducao: %d\n", subacervo[i].PeakStreams);
    printf("Total de Reproducoes: %d\n\n\n", subacervo[i].TotalStreams);
    i++;
  }
  
  //BUSCA POR POSICAO NO ACERVO
   // while (id > 0 && id <= tam){
   //   printf("Entre com índice de um item do acervo (%d < BookID < %d): ", 0,
   //   tam); scanf("%d\n", &id);
   //   id--;
   //   setbuf(stdin, NULL); printf("Position: %d\n",
   //   acervo[id].Position); printf("Artista: %s\n", acervo[id].ArtistName);
   //   printf("Musica: %s\n", acervo[id].SongName);
   //   printf("Dias no top 10: %d\n", acervo[id].Days);
   //   printf("Vezes no top 10: %2.f\n", acervo[id].Top10Times);
   //   printf("Maior Posicao: %d\n", acervo[id].PeakPosition);
   //   printf("Maior Posicao x vezes: %s\n", acervo[id].PeakPositionXtimes);
   //   printf("Pico de reproducao: %d\n", acervo[id].PeakStreams);
   //   printf("Total de Reproducoes: %d\n\n\n", acervo[id].TotalStreams);
   //   }

  limpaAcervo(acervo, tam);
}