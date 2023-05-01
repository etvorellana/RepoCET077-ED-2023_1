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

int busca_binaria(TSongs *lista, int tamanho, int item) {
  // printf("aaaaaaaaaaaaaaa%d", item);
  int esquerda = 0, direita = tamanho - 1;
  int meio = (esquerda + direita) / 2;
  while (esquerda <= direita) {
    // printf("entra no while");
    if (lista[meio].Position == item) {
      printf("achamo\n");
      return meio;
    } else if (lista[meio].Position < item) {
      esquerda = meio + 1;
    } else {
      direita = meio - 1;
    }
    meio = (esquerda + direita) / 2;
  }
  printf("!achamo\n");

  return esquerda;
}

int buscaBinporPOSICAO(int position, TSongs *lista, int tam, int *existe) {
  // essa função sempre vai retornar um indice, o ponteiro existe
  // que define se existe ou não.
  //  << *existe = 0 que dizer que a chave buscada nao existe, e função vai
  //  retorar onde ele deveria esta >>
  //*existe = 1, a função vai retornar onde foi encontrado
  int inicio = 0;                // inicio do vetor
  int meio = (inicio + tam) / 2; // meio do vetor
  *existe = 1;                   // diz se exies ou nao
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
  *existe = 0;   // elemento não encontrado
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

int RemRegistro_ordenado(TSongs song, TSongs *lista, int *tamaux) {

  int a = buscaBinporPOSICAOi(song.Position, lista, *tamaux);
  if (a != -1) {

    free(lista[a].ArtistName);
    free(lista[a].SongName);
    free(lista[a].PeakPositionXtimes);
    lista[a] = lista[*tamaux - 1];
    for (int i = a + 1; i < *tamaux; i++) {
      lista[i] = lista[i + 1];
    }

    *tamaux = *tamaux - 1;
    return 1;
  }
  return 0;
}
//
TListaLinear *criaListaLinear(int cap, int eOrd) {
  // printf("\nCriando lista\n");
  TListaLinear *listaLinear = (TListaLinear *)malloc(sizeof(TListaLinear));

  if (!listaLinear) {
    printf("Erro de alocacao!!!");
    exit(-1);
  }
  // printf("\nMorreu 0\n");
  listaLinear->cap = cap;
  listaLinear->tam = 0;
  listaLinear->eOrd = eOrd;
  // printf("\nMorreu 1\n");

  if (eOrd) {
    listaLinear->lista = (TSongs *)malloc(cap * sizeof(TSongs));
    // printf("\nMorreu 2.1\n");
  } else {
    listaLinear->lista = (TSongs *)malloc((cap + 1) * sizeof(TSongs));
    // printf("\nMorreu 2.2\n");
  }

  if (!listaLinear->lista) {
    printf("Erro de alocacao!!!");
    exit(-1);
  }

  // printf("\nRetornando lista\n");
  return listaLinear;
}
//
int buscaNaLista(TSongs song, TListaLinear *listaLinear) {
  // printf("entrou na busca\n");
  int posicao;

  if (listaLinear->tam == 0) {
    return 0;
  } else if (listaLinear->eOrd != 0) {
    // printf("entrou na busca ordenada\n");
    posicao =
        busca_binaria(listaLinear->lista, listaLinear->tam, song.Position);
    // printf("\nEsta na lista!\n");
    return posicao;
  } else {
    // printf("entrou na busca !ordenada\n");
    posicao = BuscaPorRank(song.Position, listaLinear->lista, listaLinear->tam);
    // printf("\nNao esta na lista!\n");

    return posicao;
  }
}

// Foram retiradas as funções de busca das funções de inclusão, pois a busca é
// feita no "insereNaLista"

int IncRegistroOrd(TSongs song, TSongs *lista, int *tamaux, int pos) {
  if (lista[pos].Position != song.Position) {
    for (int i = *tamaux; i > pos; i--)
      lista[i + 1] = lista[i]; // Abre espaço na lista para colocar o registro
                               // na posição correta

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

int IncRegistro(TSongs song, TSongs *lista, int *tamaux, int pos) {
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
  } else if (pos != *tamaux) {
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

int insereNaLista(TSongs song, TListaLinear *listaLinear) {
  // printf("entrou na inserção\n");
  int pos = buscaNaLista(song, listaLinear);

  if (listaLinear->lista[pos].Position != song.Position) {
    // printf("entrou no if");
    if (listaLinear->eOrd != 0) {
      // printf("entrou na inserção ordenada\n");
      return IncRegistroOrd(song, listaLinear->lista, &(listaLinear->tam), pos);
    } else {
      // printf("entrou na inserção !ordenada");
      return IncRegistro(song, listaLinear->lista, &(listaLinear->tam), pos);
    }
  }
}

/*
  As funções de remoção foram modificadas para que retornem um ponteiro para o
  registro removido da lista Foram retiradas as funções de busca das funções de
  remoção, pois a busca é feita no "insereNaLista"
*/

TSongs *RemRegistroOrd(TSongs song, TSongs *lista, int *tamaux, int pos) {
  // Ponteiro para o registro que será removido da lista
  TSongs *ptr = &(lista[pos]);

  if (lista[pos].Position == song.Position) {
    // limpa os campos
    limpaRegistro(lista[pos]);

    if (*tamaux > 1)
      for (int i = *tamaux; i > pos; i--)
        lista[i - 1] = lista[i];

    *tamaux = *tamaux - 1;
    return ptr;
  }

  return NULL;
}

TSongs *RemRegistro_nao_ordenado(TSongs song, TSongs *lista, int *tamaux,
                                 int pos) {
  TSongs *ptr = &(lista[pos]);

  if (pos != *tamaux) {
    limpaRegistro(lista[pos]);
    lista[pos] = lista[*tamaux - 1];
    *tamaux = *tamaux - 1;
    return ptr;
  }
  return NULL;
}

TSongs *removeDaLista(TSongs song, TListaLinear *listaLinear) {

  int pos = buscaNaLista(song, listaLinear);

  if (listaLinear->eOrd != 0) {

    return RemRegistroOrd(song, listaLinear->lista, &(listaLinear->tam), pos);
  } else {
    return RemRegistro_nao_ordenado(song, listaLinear->lista,
                                    &(listaLinear->tam), pos);
  }
}

TPilhaLinear *criaPilhaLinear(int cap) {
  TPilhaLinear *p = (TPilhaLinear *)malloc(sizeof(TPilhaLinear));
  if (p == NULL) {
    printf("Erro: memória insuficiente!\n");
    exit(1);
  }
  p->pilha = (TSongs *)malloc(cap * sizeof(TSongs));
  if (p->pilha == NULL) {
    printf("Erro: memória insuficiente!\n");
    exit(1);
  }
  p->cap = cap;
  p->topo = 0;
  return p;
}
// inicializa uma estrutura de pilha
/*int inicioPilhalinear(TPilhaLinear *pilha, int cap) {
  // capacidade total da pilha
  pilha -> cap = cap;

  // topo com posição inicial = 0
  pilha -> topo = 0;

  // alocação de memória
  pilha -> pilha = (TSongs*) malloc(cap * sizeof(TSongs));

  // se alocação for bem sucedida
  if(pilha -> pilha)
    return 1;
  else
    return 0;
}
*/
// inserir novo elemento na pilha
int pushTSongs(TSongs song, TPilhaLinear *pilha) {

  // se a pilha não estiver cheia
  if (pilha->topo < pilha->cap) {
    pilha->pilha[pilha->topo].Position = song.Position;
    pilha->pilha[pilha->topo].Key = song.Key;

    // dava erro no tamanho estranhamente entao ao *2
    // garante que vai ter o espaço
    pilha->pilha[pilha->topo].ArtistName =
        (char *)malloc(strlen(song.ArtistName) * 2);
    strcpy(pilha->pilha[pilha->topo].ArtistName, song.ArtistName);

    pilha->pilha[pilha->topo].SongName =
        (char *)malloc(strlen(song.SongName) * 2);
    strcpy(pilha->pilha[pilha->topo].SongName, song.SongName);

    pilha->pilha[pilha->topo].Days = song.Days;
    pilha->pilha[pilha->topo].Top10Times = song.Top10Times;
    pilha->pilha[pilha->topo].PeakPosition = song.PeakPosition;

    pilha->pilha[pilha->topo].PeakPositionXtimes =
        (char *)malloc(strlen(song.PeakPositionXtimes) * 2);
    strcpy(pilha->pilha[pilha->topo].PeakPositionXtimes,
           song.PeakPositionXtimes);

    pilha->pilha[pilha->topo].PeakStreams = song.PeakStreams;
    pilha->pilha[pilha->topo].TotalStreams = song.TotalStreams;

    // incremento topo
    pilha->topo++;

    return 1;
  }

  // caso contrário
  else
    return 0;
}

// remover elemento da pilha
int popTSongs(TPilhaLinear *pilha) {
  // verificando se existe algum elemento na pilha
  if (pilha->topo > 0) {
    // decremento do topo
    pilha->topo--;

    // limpando os campos
    free(pilha->pilha[pilha->topo].ArtistName);
    free(pilha->pilha[pilha->topo].SongName);
    free(pilha->pilha[pilha->topo].PeakPositionXtimes);

    return 1;
  }

  // caso contrário
  else
    return 0;
}

TFilaLinear *criaFila(int cap) {
  TFilaLinear *p = (TFilaLinear *)malloc(sizeof(TFilaLinear));
  if (p == NULL) {
    printf("Erro: memória insuficiente!\n");
    exit(1);
  }

  p->fila = (TSongs *)malloc(cap * sizeof(TSongs));
  if (p->fila == NULL) {
    printf("Erro: memória insuficiente!\n");
    exit(1);
  }
  p->cap = cap;
  p->ini = 0;
  p->fim = 0;
  return p;
}

int enqueue(TSongs song, TFilaLinear *fila) {
  if (fila->fim - fila->ini == fila->cap) { // a fila esta cheia
    return fila->cap;
  } else {
    // função para na inserir elementos repetidos da fila?
    fila->fila[fila->fim].Position = song.Position;
    fila->fila[fila->fim].Key = song.Key;

    fila->fila[fila->fim].ArtistName =
        (char *)malloc(strlen(song.ArtistName) * 2);
    strcpy(fila->fila[fila->fim].ArtistName, song.ArtistName);

    fila->fila[fila->fim].SongName = (char *)malloc(strlen(song.SongName) * 2);
    strcpy(fila->fila[fila->fim].SongName, song.SongName);

    fila->fila[fila->fim].Days = song.Days;
    fila->fila[fila->fim].Top10Times = song.Top10Times;
    fila->fila[fila->fim].PeakPosition = song.PeakPosition;

    fila->fila[fila->fim].PeakPositionXtimes =
        (char *)malloc(strlen(song.PeakPositionXtimes) * 2);
    strcpy(fila->fila[fila->fim].PeakPositionXtimes, song.PeakPositionXtimes);

    fila->fila[fila->fim].PeakStreams = song.PeakStreams;
    fila->fila[fila->fim].TotalStreams = song.TotalStreams;
    
    fila-> fim = fila->fim + 1;
    return 1;
  }
  return 0;
}

TSongs *dequeue(TFilaLinear *fila) {
  if (fila->ini == fila->fim) {
    return NULL;
  } else {
    TSongs* filaAux = (TSongs*) malloc(sizeof(TSongs));
    filaAux = &fila->fila[fila->ini];
    
    free(fila->fila[fila->ini].ArtistName);
    free(fila->fila[fila->ini].SongName);
    free(fila->fila[fila->ini].PeakPositionXtimes);
    
    fila->ini = fila->ini + 1;
    return filaAux;
  }
}

//listas encadeadas 
int cpyTsong(TSongs song, TSongs *end)
{
    end = (TSongs*) malloc(sizeof(TSongs));
    
    if(end)
    {
        // função para na inserir elementos repetidos da fila?
      end -> Position = song.Position;
      end -> Key = song.Key;

      end -> ArtistName = (char *) malloc(strlen(song.ArtistName) * 2);
      strcpy(end -> ArtistName, song.ArtistName);

      end -> SongName = (char *)malloc(strlen(song.SongName) * 2);
      strcpy(end -> SongName, song.SongName);

      end -> Days = song.Days;
      end -> Top10Times = song.Top10Times;
      end -> PeakPosition = song.PeakPosition;

      end -> PeakPositionXtimes = (char *) malloc(strlen(song.PeakPositionXtimes) * 2);
      strcpy(end -> PeakPositionXtimes, song.PeakPositionXtimes);

      end -> PeakStreams = song.PeakStreams;
      end -> TotalStreams = song.TotalStreams;
      
      return TRUE;
    }

    return FALSE;
}

//cria pilha encadeada
int cria_pilha(Tpilha *p)
{
  p -> topo = NULL;
  p -> tam = 0;
  return TRUE;
}

//insere na pilha 
int empilhaEnc(TSongs song, Tpilha *p)
{
  No *novo = malloc(sizeof(No));

  if(cpyTsong(song, &novo -> song))
  {
    // p->tam também serve de verificação 
    if (p -> topo == NULL)
    {
      p -> topo = malloc (sizeof(No));
      p -> topo = novo;
      p -> tam ++;
      return TRUE;
    }

    else
    {
      novo -> proximo = p -> topo;
      p -> topo = novo;
      p -> tam ++;
      return TRUE;
    }
  }

  return FALSE;
}

//desempilha
No* desempilhaEnc(Tpilha *p)
{
  //Se tiver algum elemento na lista 
  if(p -> topo)
  {
    No *remove = p -> topo;
    p -> topo = remove -> proximo;
    return remove;
  }

  return NULL;
}

//print pilha
void printPilhaEnc(Tpilha *p)
{
  No *print = p -> topo;

  //enquanto print for diferente de NULL
  while(print)
  {
    printf("posicao:\t%d\nmusica:\t%s", print -> song.Position, print -> song.SongName);
    print = print -> proximo;
  }
}