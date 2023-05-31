#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h" // contem o struct dos dados

//manipular TSongs

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

TSongs* cpyTsong(TSongs song, TSongs *end) 
{
    end = malloc(sizeof(TSongs));

    if (end) {

        end->Position = song.Position;
        end->Key = song.Key;

        end->ArtistName = (char *)malloc(strlen(song.ArtistName) * 2);
        strcpy(end->ArtistName, song.ArtistName);

        end->SongName = (char *)malloc(strlen(song.SongName) * 2);
        strcpy(end->SongName, song.SongName);

        end->Days = song.Days;
        end->Top10Times = song.Top10Times;
        end->PeakPosition = song.PeakPosition;

        end->PeakPositionXtimes =
            (char *)malloc(strlen(song.PeakPositionXtimes) * 2);
        strcpy(end->PeakPositionXtimes, song.PeakPositionXtimes);

        end->PeakStreams = song.PeakStreams;
        end->TotalStreams = song.TotalStreams;

        return end;
    }

    return NULL;
}

//Árvores binárias

NoArv* newNoArvBin()
{
    NoArv *arv = (NoArv *) malloc(sizeof(NoArv));
    arv->dir = NULL;
    arv->esq = NULL;
    arv -> song = NULL;
    arv -> altura = 0;
    return arv;
}

int alturaNo(NoArv *raiz)
{
    if (!raiz) //raiz == NULL
        return -1;
    
    else // raiz != NULL
    {
        int esq = alturaNo(raiz -> esq);
        int dir = alturaNo(raiz -> dir);
        if (esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

NoArv* inserir(NoArv *raiz, TSongs song) //corpo da função para inserir elemento
{
    if (!raiz) //se raiz for igual a NULL
    {
        raiz = newNoArvBin(); //alocando espaço na memória
        raiz -> song = cpyTsong(song, raiz -> song); //atribuição do valor
    }

    else //caso contrário
    {
        if (song.Position < raiz -> song -> Position) //se value for menor que o valor que estiver no campo
            raiz -> esq = inserir(raiz -> esq, song);
        else //caso seja maior
            raiz -> dir = inserir(raiz -> dir, song);
    }

    raiz -> altura = alturaNo(raiz);
    return raiz;
}

void imprimir(NoArv *arv, int tipo)
{
    if(arv != NULL)
    {
        if (tipo == 0)
        {
            imprimir(arv->esq, tipo);
            printf("(%d, %s, %d)  ", arv->song->Position, arv->song->SongName, arv -> altura);
            imprimir(arv->dir, tipo);
        }else if (tipo == 1)
        {   
            printf("(%d, %s, %d)  ", arv->song->Position, arv->song->SongName, arv-> altura);
            imprimir(arv->esq, tipo);
            imprimir(arv->dir, tipo);
        }else if (tipo == 2)
        {
            imprimir(arv->esq, tipo);
            imprimir(arv->dir, tipo);
            printf("(%d, %s, %d)  ", arv->song->Position, arv->song->SongName, arv-> altura);
        }else{
            imprimir(arv->dir, tipo);
            printf("(%d, %s, %d)  ", arv->song->Position, arv->song->SongName, arv-> altura);
            imprimir(arv->esq, tipo);
        }
    }       
}

void inserir_i(NoArv **raiz, TSongs song) //corpo do procedimento
{
    NoArv *aux = *raiz;

    while(aux)
    {
        if (song.Position < aux -> song -> Position)
            raiz = &aux -> esq;
        else 
            raiz = &aux -> dir;

        aux = *raiz;
    }

    aux = newNoArvBin();
    aux -> song = cpyTsong(song, aux -> song);
    aux -> altura = alturaNo(aux);

    *raiz = aux;
}

NoArv* buscaRec(NoArv *raiz, int key) //corpo da função de busca recursiva
{
    if (raiz) 
    {
        if (key == raiz -> song -> Position)
            return raiz;
        else if (key < raiz -> song -> Position)
            return buscaRec(raiz -> esq, key);
        else
            return buscaRec(raiz -> dir, key);
    }

    return NULL;
}

NoArv* buscai(NoArv *raiz, int key) //corpo da função de busca iterativa
{
    NoArv *aux = raiz;
    while (aux) //enquanto aux != NULL
    {
        if (key < aux -> song -> Position)
            aux = aux -> esq;
        else if (key > aux -> song -> Position)
            aux = aux -> dir;
        else
            return aux;
    }

    return NULL;
}

NoArv* removeNoArv(NoArv *raiz, TSongs song) //corpo da função de remoção
{
    if (!raiz) //se raiz == NULL
        return NULL;
    else 
    {
        if (song.Position == raiz -> song -> Position) //encontrei o elemento
        {
            if (raiz -> esq && raiz -> dir) // se as duas sub-arvores são != NULL
            {
                NoArv *aux = raiz -> esq;
                while (aux -> dir)
                    aux = aux -> dir;
                raiz -> song = aux -> song;
                aux -> song = cpyTsong(song, aux->song);
                raiz -> esq = removeNoArv(raiz -> esq, song);
                return raiz;
            }

            else if (raiz -> esq) //se a sub-arvore da esquerda != NULL
            {
                NoArv *aux = raiz -> esq;
                limpaRegistro(*raiz->song);
                free(raiz);
                return aux;
            }

            else if (raiz -> dir) //se a sub-arvore da direita != NULL
            {
                NoArv *aux = raiz -> dir;
                limpaRegistro(*raiz->song);
                free(raiz);
                return aux;
            }

            else //se as duas sub-arvores forem nulas
            {
                limpaRegistro(*raiz->song);
                free(raiz);
                return NULL;
            }
        }
        
        else // caso não tenha encontrado
        {
            if (song.Position < raiz -> song -> Position) //se a key for menor que a key da raiz
                raiz -> esq = removeNoArv(raiz -> esq, song);
            else //se a key for maior que a key da raiz
                raiz -> dir = removeNoArv(raiz -> dir, song);

            return raiz;
        }
    }
}

void menu()
{
    int num;
    int tam;
    int opcao;
    int tipo;
    int key;
    TSongs *acervo = carregaDados("../../Data/songs.csv", &tam);
    NoArv *raiz = NULL;
    NoArv *busca = NULL;

    do
    {
        printf("\n\t0 - sair\n\t1 - inserir\n\t2 - imprimir\n\t3 - buscar\n\t4 - altura\n\t");
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            num = rand() % CSVSIZE;
            raiz = inserir(raiz, acervo[num]);
            break;
        case 2:
        printf("Digite o tipo(1 a 4) da impressao: ");
        scanf("%d", &tipo);
        printf("Impressao\n-----------------------------------------------\n");
            imprimir(raiz, tipo);
            break;
        case 3:
            printf("Digite a key do elemento que procura: ");
            scanf("%d", &key);
            busca = buscaRec(raiz, key);
            if (busca)
                printf("Valor encontrado: %d - %s\n", busca -> song -> Position, busca -> song -> SongName);
            else 
                printf("Valor nao encontrado!\n");
            break;
        case 4:
            printf("Altura da arvore: %d\n", raiz -> altura);
            break;
        default:
            if (opcao != 0)
                printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);
    
}