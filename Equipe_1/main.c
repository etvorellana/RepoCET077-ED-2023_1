#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main(void){
  Games *jogos;
  int tam;
  Tlinear linear[2];

  jogos = carregaDados("../../Data/Grupo1DataSet.csv" , &tam);

  //Criando nossa nova lista com 100 jogos
  Games *jogos02;
  int tam02 = 0; // tamanho de jogos 02
  int capacidade02 = 100; // capacidade de jogos 02
  linear[0].cap = capacidade02;
  linear[0].tam = tam02;
  linear[0].jogos = jogos02;
  linear[0].ordenada = 0;
  //alocando espaço para o novo array
  jogos02 = IniciaLista(capacidade02);
   
  int try = 0, ok = 0;  
  while(tam02 < capacidade02){ // enquanto não estiver cheia{
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try++;
    if(incJogo(jogos[idx], jogos02, &tam02))
      ok++;
  }

  printf("Foram realizadas %d tentativas de inclusão\n", try);
  printf("Foram incluídos %d registros na lista\n", ok);
    
  //Buscando jogos por id
  try = 0, ok = 0;  
  while(tam02 > ok){
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try++;
    jogos02[tam02].ID = jogos[idx].ID;
    if(buscaPorId(jogos[idx].ID, jogos02, &tam02) < tam02)
      ok++;
  }

  printf("Foram realizadas %d tentativas de busca\n", try);
  printf("Foram achados %d registros na lista\n", ok);

  //removendo jogos
  try = 0, ok = 0;  
  while(tam02 > 0){
    int idx = rand()%tam;
    try++;
    if(remJogo(jogos[idx], jogos02, &tam02))
      ok++;
  }
  linear[0].tam = tam02;

  printf("Foram realizadas %d tentativas de remoção\n", try);
  printf("Foram removidos %d registros na lista\n", ok);


//CRIANDO UMA LISTA COM 100 JOGOS ORDENADOS

  Games *jogos03;
  int tam03 = 0; // tamanho de jogos 02
  int capacidade03 = 100; // capacidade de jogos 02
  linear[1].tam = tam03;
  linear[1].cap = capacidade03;
  linear[1].jogos = jogos03;
  linear[1].ordenada = 1;
  //alocando espaço para o novo array
  jogos03 = IniciaLista(capacidade03);
   
  int try2 = 0, ok2 = 0;  
  while(tam03 < capacidade03){ // enquanto não estiver cheia{
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try2++;
    if(incJogoOrdenado(jogos[idx], jogos03, &tam03))
      ok2++;
  }

  printf("\n\nForam realizadas %d tentativas de inclusão na lista ordenada\n", try2);
  printf("Foram incluídos %d registros na lista ordenada\n", ok2);
    
  //Buscando jogos por id
  try2 = 0, ok2 = 0;  
  while(tam03 > ok2){
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try2++;
    if(buscaBinRecPorId(jogos[idx].ID,jogos03,0,tam03) < tam03)
      ok2++;
  }

  printf("Foram realizadas %d tentativas de busca na lista ordenada\n", try2);
  printf("Foram achados %d registros na lista ordenada\n", ok2);

  //removendo jogos
  try2 = 0, ok2 = 0;  
  while(tam03 > 0){
    int idx = rand()%tam;
    try2++;
    if(remJogoOrdenado(jogos[idx],jogos03,&tam03))
      ok2++;
  }
  linear[1].tam = tam03;

  printf("Foram realizadas %d tentativas de remoção na lista ordenada\n", try2);
  printf("Foram removidos %d registros na lista ordenada\n", ok2);

  //limpaJogos(jogos02, tam02);
  limpaJogos(jogos, tam);
  
  return 0;
}


// Biblioteca de funções
Games* IniciaLista(int capacidade);
int buscaPorId(int ID, Games* lista, int *tam);
int buscaBinPorId(int ID, Games *lista, int ini, int fim);

Games* carregaDados(char *fileName, int *tam)
{
  Games *jogos;
  FILE *fp;
  int i = 0;
  char str[900];
    
  jogos = IniciaLista(CSVSIZE);

  fp = fopen(fileName, "r");
    
  if(fp == NULL) {
    printf("Arquivo não pode ser aberto\n");
    return NULL;
  }

  // pegando o cabeçalho
  char header[50]; 
  fscanf(fp,"%s",header);
  //printf("%s\n",header);

  //lendo o arquivo
  while(!feof(fp)){

    //id
    fscanf(fp,"\n%d",&jogos[i].ID);
    //nome    
    fscanf(fp,",%[^,]s",str);
    jogos[i].Name = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[i].Name,str);
    //plataforma    
    fscanf(fp,",%[^,]s",str);
    jogos[i].Platform = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[i].Platform,str);
    //ano de lançamento
    fscanf(fp,",%d",&jogos[i].Year_Of_Release);
    //genero
    fscanf(fp,",%[^,]s",str);
    jogos[i].Genre = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[i].Genre,str);
    //Empresa que publicou
    fscanf(fp,",%[^,]s",str);
    jogos[i].Publisher = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[i].Publisher,str);
    //vendas
fscanf(fp,",%f,%f,%f,%f,%f,",&jogos[i].NA_Sales,&jogos[i].EU_Sales,&jogos[i].JP_sales,&jogos[i].Other_Sales,&jogos[i].Global_Sales);
    fscanf(fp,"%[^\n]s",str);
    
    i++;
  }
    *tam = i;
    int err = fclose(fp);
    if (err) // err != 0
    {
        printf("Arquivo incorretamente fechado!!\n");
    }
    return jogos;
}

Games* IniciaLista(int capacidade){
  Games* jogos;
  jogos = (Games*) malloc((capacidade+1)*sizeof(Games));
  return jogos;
}

void limpaJogos(Games *jogos, int tam){
  for(int j = 0; j < tam; j++){
    free(jogos[j].Name);
    free(jogos[j].Platform);
    free(jogos[j].Genre);
    free(jogos[j].Publisher);
  }
  free(jogos);
}

void limpaJogos02(Games *jogos, int Pos){
    free(jogos[Pos].Name);
    free(jogos[Pos].Platform);
    free(jogos[Pos].Genre);
    free(jogos[Pos].Publisher);
}

//FUNÇÕES PARA LISTAS DESORDENADAS

int buscaPorId(int ID, Games* lista, int *tam){
  for(int i = 0; i < *tam; i++){
    if(ID == lista[i].ID)
      return i;
    }
  return -1;
}

int incJogo(Games jogos, Games* jogos02, int* tam){
  int ok = buscaPorId(jogos.ID,jogos02, tam);
  if(ok==-1){
    jogos02[*tam].ID = jogos.ID;
        
    jogos02[*tam].Name = (char*)malloc((strlen(jogos.Name)+1)*sizeof(char));
    strcpy(jogos02[*tam].Name,jogos.Name);
            
    jogos02[*tam].Platform = (char*)malloc((strlen(jogos.Platform)+1)*sizeof(char));
    strcpy(jogos02[*tam].Platform,jogos.Platform);

    jogos02[*tam].Year_Of_Release =  jogos.Year_Of_Release;

    jogos02[*tam].Genre = (char*)malloc((strlen(jogos.Genre)+1)*sizeof(char));
    strcpy(jogos02[*tam].Genre,jogos.Genre);

    jogos02[*tam].Publisher = (char*)malloc((strlen(jogos.Publisher)+1)*sizeof(char));
    strcpy(jogos02[*tam].Publisher,jogos.Publisher);

    jogos02[*tam].NA_Sales = jogos.NA_Sales;

    jogos02[*tam].EU_Sales = jogos.EU_Sales;

    jogos02[*tam].JP_sales = jogos.JP_sales;

    jogos02[*tam].Other_Sales = jogos.Other_Sales;

    jogos02[*tam].Global_Sales = jogos.Global_Sales;

    ++(*tam);
    return 1;
  }
  else{
    return 0;
  }
}

int remJogo(Games jogo, Games* jogos02, int* tam){
  if(*tam>1){
    int ok = buscaPorId(jogo.ID,jogos02, tam);
    if(ok!=-1){
      limpaJogos02(jogos02, ok);
      jogos02[ok] = jogos02[*tam-1];
      --(*tam);
      return 1;
    }
  }
  if(*tam == 1){
    limpaJogos02(jogos02, 0);
    --(*tam);
  }
  return 0;
}

//FUNÇÕE PARA LISTAS ORDENADAS

int buscaBinRecPorId(int ID, Games *lista, int ini, int fim){
  if(fim>ini){
    int meio = (fim+ini)/2;
    if(ID == lista[meio].ID){
      return meio;
    }else if(lista[meio-1].ID < ID && lista[meio+1].ID>ID){
      return meio;
    }else if(ID < lista[meio].ID){
      return buscaBinRecPorId(ID, lista, ini, meio-1);
    }
    else if(ID > lista[meio].ID) {
      return buscaBinRecPorId(ID, lista, meio+1, fim);
    }
  }

}

int buscaBinPorId(int ID, Games *lista, int ini, int fim){

  if(fim>=ini){
    for(int i=0; i<(fim+ini); i++){
      int meio = (fim+ini)/2;
      if(ID == lista[meio].ID){
        return meio;
      }else if(ID < lista[meio].ID){
        fim = meio-1;
      }
      else{
        ini = meio+1;
      }
    }
  }
  return -1;
}

int remJogoOrdenado(Games jogo, Games* jogos03, int* tam){
  if((*tam)>1){
    int pos = buscaBinRecPorId(jogo.ID,jogos03,0,*tam);
    if(jogos03[pos].ID == jogo.ID){
      
      for(int i=pos; i<(*tam)-1; i++){
        limpaJogos02(jogos03, i);
    
        jogos03[i].ID = jogos03[i+1].ID;
        
        jogos03[i].Name = (char*)malloc((strlen(jogos03[i+1].Name)+1)*sizeof(char));
        strcpy(jogos03[i].Name,jogos03[i+1].Name);
            
        jogos03[i].Platform = (char*)malloc((strlen(jogos03[i+1].Platform)+1)*sizeof(char));
        strcpy(jogos03[i].Platform,jogos03[i+1].Platform);

        jogos03[i].Year_Of_Release =  jogos03[i+1].Year_Of_Release;

        jogos03[i].Genre = (char*)malloc((strlen(jogos03[i+1].Genre)+1)*sizeof(char));
        strcpy(jogos03[i].Genre,jogos03[i+1].Genre);

        jogos03[i].Publisher = (char*)malloc((strlen(jogos03[i+1].Publisher)+1)*sizeof(char));
        strcpy(jogos03[i].Publisher,jogos03[i+1].Publisher);

        jogos03[i].NA_Sales = jogos03[i+1].NA_Sales;

        jogos03[i].EU_Sales = jogos03[i+1].EU_Sales;

        jogos03[i].JP_sales = jogos03[i+1].JP_sales;

        jogos03[i].Other_Sales = jogos03[i+1].Other_Sales;

        jogos03[i].Global_Sales = jogos03[i+1].Global_Sales;
      
      }
      --(*tam);
      return 1;
    }
  }
  if(*tam == 1){
    limpaJogos02(jogos03, 0);
    --(*tam);
    return 1;
  }
  return 0;
}

int incJogoOrdenado(Games jogo, Games* jogos03, int* tam){

  int pos = buscaBinRecPorId(jogo.ID,jogos03,0,*tam);
  int i, j;
  if(jogos03[pos].ID != jogo.ID){
    // Mosve os elementos maiores para a direita para abrir espaço para o novo jogo
    for(j = *tam - 1; j >= i; j--){

      jogos03[j+1] = jogos03[j];

    }
    // Insere o novo jogo na posição correta

    jogos03[i].ID = jogo.ID;
        
    jogos03[i].Name = (char*)malloc((strlen(jogo.Name)+1)*sizeof(char));
    strcpy(jogos03[i].Name,jogo.Name);
            
    jogos03[i].Platform = (char*)malloc((strlen(jogo.Platform)+1)*sizeof(char));
    strcpy(jogos03[i].Platform,jogo.Platform);

    jogos03[i].Year_Of_Release =  jogo.Year_Of_Release;

    jogos03[i].Genre = (char*)malloc((strlen(jogo.Genre)+1)*sizeof(char));
    strcpy(jogos03[i].Genre,jogo.Genre);

    jogos03[i].Publisher = (char*)malloc((strlen(jogo.Publisher)+1)*sizeof(char));
    strcpy(jogos03[i].Publisher,jogo.Publisher);

    jogos03[i].NA_Sales = jogo.NA_Sales;

    jogos03[i].EU_Sales = jogo.EU_Sales;

    jogos03[i].JP_sales = jogo.JP_sales;

    jogos03[i].Other_Sales = jogo.Other_Sales;

    jogos03[i].Global_Sales = jogo.Global_Sales;

    ++(*tam);
    return 1;
  }
  return 0;
  
}