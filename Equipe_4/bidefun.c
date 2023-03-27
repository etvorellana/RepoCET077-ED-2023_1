#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h" // contem o struct dos dados das musicas

TSongs *carregaDados(char *fileName, int *tam) {
  TSongs *acervo;
  FILE *fp;
  char str[900];
  int i = 0;

  // Criando o Array para armazenar as musicas
  acervo = (TSongs *)malloc(CSVSIZE * sizeof(TSongs));

  fp = fopen("Data/songs.csv", "r");

  // Verificar se a leitura ocorreu bem
  if (fp == NULL) {
    printf("Error");
    return NULL;
  }

  // Pegando o cabeçalho
  char *ok;
  ok = fgets(str, 900, fp);
  if (!ok) {
    printf("Erro ao ler o cabecalho: %s", str);
    return NULL;
  }

  i = 0;
  char sep[] = ",";
  while (!feof(fp) && i < CSVSIZE) // enquanto nâo chegar no final do arquivo ou
                                   // no tamanho do array
  {
    ok = fgets(str, 900, fp);
    if (ok) {
      char *campo;

      // int Posicao
      campo = strtok(str, sep);
      acervo[i].Position = atoi(campo);

      // char ArtistName
      campo = strtok(NULL, sep);
      acervo[i].ArtistName = (char *)malloc(strlen(campo)+1);
      strcpy(acervo[i].ArtistName, campo);

      // char NameSong
      campo = strtok(NULL, sep);
      acervo[i].SongName = (char *)malloc(strlen(campo)+1);
      strcpy(acervo[i].SongName, campo);

      // int Days
      campo = strtok(NULL, sep);
      acervo[i].Days = atoi(campo);

      // float Top10Times
      campo = strtok(NULL, sep);
      acervo[i].Top10Times = atof(campo);

      // int PeakPosition
      campo = strtok(NULL, sep);
      acervo[i].PeakPosition = atoi(campo);

      // int PeakPositionxtimes
      campo = strtok(NULL, sep);
      acervo[i].PeakPositionXtimes = (char *)malloc(strlen(campo)+1);
      strcpy(acervo[i].PeakPositionXtimes, campo);

      // int PeakStreams
      campo = strtok(NULL, sep);
      acervo[i].PeakStreams = atoi(campo);

      // int TotalStreams
      campo = strtok(NULL, sep);

      int pos = 0;
      while (campo[pos] != 10 && pos < strlen(campo)) 
        pos++;
      
        campo[pos] = '\0';
        acervo[i].TotalStreams = atoi(campo);
        i++;
      
      
    }
  }
  
  *tam = i;
  int err = fclose(fp);
  if (err)
    printf("Aqruivo fechado incorretamente!\n");

  return acervo;
}

void limpaAcervo(TSongs *acervo, int tam) {
  for (int i = 0; i < tam; i++) {
    free(acervo[i].ArtistName);
    free(acervo[i].SongName);
    free(acervo[i].PeakPositionXtimes);
  }
  free(acervo);
}

TSongs *sub_lista( TSongs *ponteiro, int tam, int *total)
{
    //tam é o tamanho da sub lista a ser criada
    // total é o numero de interacoes totais
    int num,cont = 0, i = 1, falha, acerto;
    TSongs *sub = (TSongs *)malloc(tam * sizeof(TSongs));

    while(i <= tam)
    {
        // gerar um numero aleatorio de 0 a 20000
        num = rand() % 20000;
        if(num > 0 && num < CSVSIZE && ponteiro[num].Position != NULL)
        {
            i++;
            sub[i].Position = ponteiro[num].Position;

            sub[i].ArtistName = (char *)malloc(strlen(ponteiro[num].ArtistName));
            sub[i].ArtistName = ponteiro[num].ArtistName;

            sub[i].SongName = (char *)malloc(strlen(ponteiro[num].SongName));
            sub[i].SongName = ponteiro[num].SongName;

            sub[i].Days = ponteiro[num].Days;

            sub[i].Top10Times = ponteiro[num].Top10Times;

            sub[i].PeakPosition = ponteiro[num].PeakPosition;

            sub[i].PeakPositionXtimes = (char *)malloc(strlen(ponteiro[num].PeakPositionXtimes));
            sub[i].PeakPositionXtimes = ponteiro[num].PeakPositionXtimes;

            sub[i].PeakStreams = ponteiro[num].PeakStreams;

            sub[i].TotalStreams = ponteiro[i].TotalStreams;
        }
        cont++;

    }
  return sub;
}