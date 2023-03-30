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

/*
TSongs *sub_lista(TSongs *ponteiro, int tam, int *total) {
  // tam é o tamanho da sub lista a ser criada
  //  total é o numero de iteracoes totais
  int num, cont = 0, i = 1, falha, acerto;
  TSongs *sub = (TSongs *)malloc(tam * sizeof(TSongs));

  while (i <= tam) {
    // gerar um numero aleatorio de 0 a 20000
    num = rand() % 20000;

    if (num > 0 && num < CSVSIZE && ponteiro[num].Position != NULL) {
      i++;
      sub[i].Position = ponteiro[num].Position;

      sub[i].ArtistName = (char *)malloc(strlen(ponteiro[num].ArtistName));
      sub[i].ArtistName = ponteiro[num].ArtistName;

      sub[i].SongName = (char *)malloc(strlen(ponteiro[num].SongName));
      sub[i].SongName = ponteiro[num].SongName;

      sub[i].Days = ponteiro[num].Days;

      sub[i].Top10Times = ponteiro[num].Top10Times;

      sub[i].PeakPosition = ponteiro[num].PeakPosition;

      sub[i].PeakPositionXtimes =
          (char *)malloc(strlen(ponteiro[num].PeakPositionXtimes));
      sub[i].PeakPositionXtimes = ponteiro[num].PeakPositionXtimes;

      sub[i].PeakStreams = ponteiro[num].PeakStreams;

      sub[i].TotalStreams = ponteiro[i].TotalStreams;
    }
    cont++;
  }
  return sub;
}
*/

int BuscaPorRank(int R, TSongs *lista, int tam) {
  // printf("Entrou na busca\n");
  // printf("%d\n", tam);
  if (tam > 0) {
    int i = 0;
    // printf("\n teste busca");
    while (i != tam) {
      // printf("\n teste busca 2");
      if (R == lista[i].Position) {
        // printf("Encontrou\n");
        return 1;
      }
      i++;
    }
    // printf("nao encontrou\n");
    return 0;
  } else {
    // printf("1 execução\n");
    return 0;
  }
}

int IncRegistro(TSongs song, TSongs *lista, int *tamaux) {

  if (!(BuscaPorRank(song.Position, lista, *tamaux))) {
    lista[*tamaux].Position = song.Position;
    lista[*tamaux].Key = song.Key;
    lista[*tamaux].ArtistName = (char *) malloc(strlen(song.ArtistName) * 2); 
    // dava erro no tamanho estranhamente entao ao *2
    // garante que vai ter o espaço
    strcpy(lista[*tamaux].ArtistName, song.ArtistName);
    lista[*tamaux].SongName = (char *) malloc(strlen(song.SongName) * 2);
    strcpy(lista[*tamaux].SongName, song.SongName);
    lista[*tamaux].Days = song.Days;
    lista[*tamaux].Top10Times = song.Top10Times;
    lista[*tamaux].PeakPosition = song.PeakPosition;
    lista[*tamaux].PeakPositionXtimes = (char *) malloc(strlen(song.PeakPositionXtimes) * 2);
    strcpy(lista[*tamaux].PeakPositionXtimes, song.PeakPositionXtimes);
    lista[*tamaux].PeakStreams = song.PeakStreams;
    lista[*tamaux].TotalStreams = song.TotalStreams;
    *tamaux = *tamaux + 1;
    return 1;
  }
  return 0;
}

// nao implementado
int RemRegistro(TSongs song, TSongs *lista, int *tamaux){
  // se existir entra no laço
  if(BuscaPorRank(song.Position, lista, *tamaux))
  {
    int i = 0;
    // percorro a *lista até encontrar a posição
    while(1)
    {
      if(lista[i].Position == song.Position)
      {
        // limpa os campos 
        free(lista[i].ArtistName);
        free(lista[i].SongName);
        free(lista[i].PeakPositionXtimes);

        //atribui a ultima posição a que eu quero excluir 
        lista[i] = lista[*tamaux];
        *tamaux = *tamaux - 1;
        break;
      }
      i++;
    }
    return 1;
  } 
  return 0;
}
