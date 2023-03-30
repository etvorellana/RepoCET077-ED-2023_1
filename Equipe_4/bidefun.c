#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h" // contem o struct dos dados das musicas

TSongs *carregaDados(char *fileName, int *tam) {
  TSongs *acervo;
  FILE *fp;
  char str[900];
  int i = 0, pos;

  // Criando o Array para armazenar as musicas
  acervo = (TSongs *)malloc(CSVSIZE * sizeof(TSongs));

  fp = fopen(fileName, "r");

  // Verificar se a leitura ocorreu bem
  if (fp == NULL) {
    printf("Error ao ler o arquivo");
    free(acervo);
    return NULL;
  }

  // Pegando o cabeçalho
  char *ok;
  ok = fgets(str, 900, fp);
  if (!ok) {
    printf("Erro ao ler o cabecalho");
    return NULL;
  }

  char sep[] = ",";
  char *campo;

  // enquanto não chegar no final do arquivo e no tamanho do array
  while (!feof(fp) && i < CSVSIZE) {
    ok = fgets(str, 900, fp);
    if (ok) {

      // int Posicao
      campo = strtok(str, sep);
      acervo[i].Position = atoi(campo);

      // long long int Key
      campo = strtok(NULL, sep);
      acervo[i].Key = atoi(campo);

      // char ArtistName
      campo = strtok(NULL, sep);
      acervo[i].ArtistName = (char *)malloc(strlen(campo) + 1);
      strcpy(acervo[i].ArtistName, campo);

      // char NameSong
      campo = strtok(NULL, sep);
      acervo[i].SongName = (char *)malloc(strlen(campo) + 1);
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
      acervo[i].PeakPositionXtimes = (char *)malloc(strlen(campo) + 1);
      strcpy(acervo[i].PeakPositionXtimes, campo);

      // int PeakStreams
      campo = strtok(NULL, sep);
      acervo[i].PeakStreams = atoi(campo);

      // int TotalStreams
      campo = strtok(NULL, sep);

      pos = 0;
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
    printf("Arquivo fechado incorretamente!\n");

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

int BuscaPorRank(int R, TSongs *lista, int tam) {
    int i = 0;
    while (i != tam) {
      if (R == lista[i].Position) {
        return i;
      }
      i++;
    }
    return tam;
}

int IncRegistro(TSongs song, TSongs *lista, int *tamaux) {
  if (*tamaux == 0){
    lista[*tamaux].Position = song.Position;
    lista[*tamaux].Key = song.Key;
    lista[*tamaux].ArtistName =
        (char *)malloc(strlen(song.ArtistName) *
                       2); // dava erro no tamanho estranhamente entao ao *2
                           // garante que vai ter o espaço
    strcpy(lista[*tamaux].ArtistName, song.ArtistName);
    lista[*tamaux].SongName = (char *)malloc(strlen(song.SongName) * 2);
    strcpy(lista[*tamaux].SongName, song.SongName);
    lista[*tamaux].Days = song.Days;
    lista[*tamaux].Top10Times = song.Top10Times;
    lista[*tamaux].PeakPosition = song.PeakPosition;
    lista[*tamaux].PeakPositionXtimes =
        (char *)malloc(strlen(song.PeakPositionXtimes) * 2);
    strcpy(lista[*tamaux].PeakPositionXtimes, song.PeakPositionXtimes);
    lista[*tamaux].PeakStreams = song.PeakStreams;
    lista[*tamaux].TotalStreams = song.TotalStreams;
    *tamaux = *tamaux + 1;
    return 1;
  }else if (BuscaPorRank(song.Position, lista, *tamaux) != *tamaux) {
    lista[*tamaux].Position = song.Position;
    lista[*tamaux].Key = song.Key;
    lista[*tamaux].ArtistName =
        (char *)malloc(strlen(song.ArtistName) *
                       2); // dava erro no tamanho estranhamente entao ao *2
                           // garante que vai ter o espaço
    strcpy(lista[*tamaux].ArtistName, song.ArtistName);
    lista[*tamaux].SongName = (char *)malloc(strlen(song.SongName) * 2);
    strcpy(lista[*tamaux].SongName, song.SongName);
    lista[*tamaux].Days = song.Days;
    lista[*tamaux].Top10Times = song.Top10Times;
    lista[*tamaux].PeakPosition = song.PeakPosition;
    lista[*tamaux].PeakPositionXtimes =
        (char *)malloc(strlen(song.PeakPositionXtimes) * 2);
    strcpy(lista[*tamaux].PeakPositionXtimes, song.PeakPositionXtimes);
    lista[*tamaux].PeakStreams = song.PeakStreams;
    lista[*tamaux].TotalStreams = song.TotalStreams;
    *tamaux = *tamaux + 1;
    return 1;
  }
  return 0;
}

int RemRegistro(TSongs song, TSongs *lista, int *tamaux){
  int a = BuscaPorRank(song.Position, lista, *tamaux);
  if(a != 0)
  {
    // //printf("Entrou na remoçao");
    // int i = 0;
    // // percorro a *lista até encontrar a posição
    // while(1)
    // {
    //   if(lista[i].Position == song.Position)
    //   {
        // limpa os campos 
        free(lista[a].ArtistName);
        free(lista[a].SongName);
        free(lista[a].PeakPositionXtimes);

        //atribui a ultima posição a que eu quero excluir 
      //   lista[i] = lista[*tamaux];
      //   *tamaux = *tamaux - 1;
      //   break;
      // }
      // i++;
      *tamaux = *tamaux - 1;
      return 1;
  }
  return 0;
}
