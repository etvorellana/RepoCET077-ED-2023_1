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

void limpaRegistro(TSongs song) {
  free(song.ArtistName);
  free(song.SongName);
  free(song.PeakPositionXtimes);
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
  if (*tamaux == 0) {
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
  } else if (BuscaPorRank(song.Position, lista, *tamaux) != *tamaux) {
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

int RemRegistro(TSongs song, TSongs *lista, int *tamaux) {
  int a = BuscaPorRank(song.Position, lista, *tamaux);
  if (a != 0) {
    // //printf("Entrou na remoçao");
    // int i = 0;
    // // percorro a *lista até encontrar a posição
    // while(1)
    // {
    //   if(lista[i].Position == song.Position)
    //   {
    // limpa os campos
    limpaRegistro(lista[a]);

    // atribui a ultima posição a que eu quero excluir
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

int busca_binaria(TSongs *lista, int tamanho, int item) {
    int esquerda = 0, direita = tamanho - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (lista[meio].Position == item) {
            return meio;
        } else if (lista[meio].Position < item) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return esquerda;
}

int buscaBinporPOSICAO(int position, TSongs *lista, int tam, int *existe) {
  //essa função sempre vai retornar um indice, o ponteiro existe
  //que define se existe ou não.
  // << *existe = 0 que dizer que a chave buscada nao existe, e função vai retorar onde ele deveria esta >>
  //*existe = 1, a função vai retornar onde foi encontrado
  int inicio = 0;                // inicio do vetor
  int meio = (inicio + tam) / 2; // meio do vetor
  *existe = 1; //diz se exies ou nao
  while (inicio <= tam) {
    if (position == lista[meio].Position) // verificação se o elemento procurado está no meio
      return meio;
    else {
      if (position < lista[meio].Position) // verifica se o elemento do meio é
                                           // maior do que o procurado
        tam = meio - 1;
      else // ou se é menor
        inicio = meio + 1;
    }
    meio = (inicio + tam) / 2; // calculando o meio do vetor
  }
  *existe = 0; // elemento não encontrado
  return inicio; // elemento não encontrado e deveria esta nessa indice
}

int buscaBinporPOSICAOi(int position, TSongs *lista, int tam) {
  int inicio = 0;                // inicio do vetor
  int meio = (inicio + tam) / 2; // meio do vetor

  while (inicio <= tam) {
    if (position ==
        lista[meio]
            .Position) // verificação se o elemento procurado está no meio
      return meio;
    else {
      if (position < lista[meio].Position) // verifica se o elemento do meio é
                                           // maior do que o procurado
        tam = meio - 1;
      else // ou se é menor
        inicio = meio + 1;
    }
    meio = (inicio + tam) / 2; // calculando o meio do vetor
  }
  return -1; // elemento não encontrado
}

int IncRegistroOrd(TSongs song, TSongs *lista, int *tamaux) {
  int pos = busca_binaria(lista, *tamaux, song.Position);

  if (lista[pos].Position != song.Position) {
    for (int i = *tamaux; i > pos; i--)  
      lista[i+1] = lista[i];  // Abre espaço na lista para colocar o registro na posição correta

    lista[pos].Position = song.Position;
    lista[pos].Key = song.Key;

    // dava erro no tamanho estranhamente entao ao *2
    // garante que vai ter o espaço
    lista[pos].ArtistName = (char *)malloc(strlen(song.ArtistName) * 2);  
    strcpy(lista[pos].ArtistName, song.ArtistName);

    lista[pos].SongName = (char *)malloc(strlen(song.SongName) * 2);
    strcpy(lista[pos].SongName, song.SongName);

    lista[pos].Days = song.Days;
    lista[pos].Top10Times = song.Top10Times;
    lista[pos].PeakPosition = song.PeakPosition;

    lista[pos].PeakPositionXtimes =
        (char *)malloc(strlen(song.PeakPositionXtimes) * 2);
    strcpy(lista[pos].PeakPositionXtimes, song.PeakPositionXtimes);

    lista[pos].PeakStreams = song.PeakStreams;
    lista[pos].TotalStreams = song.TotalStreams;

    *tamaux = *tamaux + 1;
    return 1;
  }

  return 0;
}

int RemRegistroOrd(TSongs song, TSongs *lista, int *tamaux) {
  int pos = busca_binaria(lista, *tamaux, song.Position);
  
  if (lista[pos].Position == song.Position) {    
    // limpa os campos
    limpaRegistro(lista[pos]);

    if(*tamaux > 1)
      for (int i = *tamaux; i > pos; i--)
        lista[i-1] = lista[i];

    *tamaux = *tamaux - 1;
    return 1;
  }

  return 0;
}

int RemRegistro_nao_ordenado(TSongs song, TSongs *lista, int *tamaux) {
  int a = BuscaPorRank(song.Position, lista, *tamaux);
  if (a != *tamaux) {
    limpaRegistro(lista[a]);
    lista[a] = lista[*tamaux - 1];
    *tamaux = *tamaux - 1;
    return 1;
  }
  return 0;
}

int RemRegistro_ordenado(TSongs song, TSongs *lista, int *tamaux) {

  int a = buscaBinporPOSICAOi(song.Position,lista, *tamaux);
  if (a != -1) {
   
  
    free(lista[a].ArtistName);
    free(lista[a].SongName);
    free(lista[a].PeakPositionXtimes);
    lista[a] = lista[*tamaux -1];
    for (int i = a + 1; i < *tamaux; i++) {
      lista[i] = lista[i + 1];       
    }
    
    *tamaux = *tamaux - 1;
    return 1;
  }
  return 0;
}

TListaLinear* criaListaLinear(int cap, int eOrd) {
  TListaLinear *listaLinear;
  listaLinear->cap = cap;
  listaLinear->eOrd = eOrd;

  if (eOrd) 
    listaLinear->lista = (TSongs*) malloc(cap * sizeof(TSongs));
  else
    listaLinear->lista = (TSongs*) malloc((cap+1) * sizeof(TSongs));
  
  if (!listaLinear->lista) {
    printf("Erro de alocacao!!!");
    exit(-1);
  }

  return listaLinear;
}

/*
NÃO TESTEI AINDA E NÃO SEI SE (lista -> lista) ESTA CERTO
  */
int buscaNaLista(TSongs song, TListaLinear* listaLinear){
  int posicao;

  if(listaLinear->tam == 0){
    return 0;
  } else if(listaLinear->eOrd != 0){
    posicao = busca_binaria(listaLinear->lista, listaLinear->tam, song.Position);
    return posicao;
  } else{
    posicao = BuscaPorRank(song.Position, listaLinear->lista, listaLinear->tam);
    return posicao;
  }
}

int insereNaLista(TSongs song, TListaLinear* listaLinear) {
  //int pos = buscaNaLista(song, listaLinear);
  
  if (listaLinear->eOrd != 0) 
    return IncRegistroOrd(song, listaLinear->lista, &(listaLinear->tam));
  else 
    return IncRegistro(song, listaLinear->lista, &(listaLinear->tam));
}

/* 
  As funções de remoção foram modificadas para que retornem um ponteiro para o registro removido da lista
  e retirei as funções de busca, pois a função "buscaNaLista" que provavelmente deve ser usada
  No momento coloquei "_" para diferenciar, mas não está no .h
*/

TSongs* RemRegistroOrd_(TSongs song, TSongs *lista, int *tamaux, int pos) {
  // Ponteiro para o registro que será removido da lista
  TSongs *ptr = &(lista[pos]);
  
  if (lista[pos].Position == song.Position) {    
    // limpa os campos
    limpaRegistro(lista[pos]);

    if(*tamaux > 1)
      for (int i = *tamaux; i > pos; i--)
        lista[i-1] = lista[i];

    *tamaux = *tamaux - 1;

    return ptr;
  }

  return NULL;
}

TSongs* RemRegistro_nao_ordenado_(TSongs song, TSongs *lista, int *tamaux, int pos) {
  TSongs *ptr = &(lista[pos]);
  
  if (pos != *tamaux) {
    limpaRegistro(lista[pos]);
    lista[pos] = lista[*tamaux - 1];
    *tamaux = *tamaux - 1;
    return ptr;
  }
  return NULL;
}

TSongs* removeDaLista(TSongs song, TListaLinear* listaLinear) {
  int pos = buscaNaLista(song, listaLinear);
  
  if (listaLinear->eOrd != 0) {
    return RemRegistroOrd_(song, listaLinear->lista, &(listaLinear->tam), pos);
  }
  else {
    return RemRegistro_nao_ordenado_(song, listaLinear->lista, &(listaLinear->tam), pos);
  }
}
 