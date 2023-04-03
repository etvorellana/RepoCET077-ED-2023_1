// Biblioteca de funções

#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "struct.h"
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
  if(fim>=ini){
    int meio = (fim+ini)/2;
    if(ID == lista[meio].ID){
      return meio;
    }else if(ID < lista[meio].ID){
      return buscaBinRecPorId(ID, lista, ini, meio-1);
    }
    else{
      return buscaBinRecPorId(ID, lista, meio+1, fim);
    }
  }
  return -1;
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
    int ok = buscaBinRecPorId(jogo.ID,jogos03,0,*tam);
    if(ok!=-1){
      
      for(int i=ok; i<(*tam)-1; i++){
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

  int ok = buscaBinRecPorId(jogo.ID,jogos03,0,*tam);
  int i, j;
  if(ok==-1){
    // Encontra a posição correta para o novo jogo
    for (i = 0; i < *tam; i++){
      if (jogo.ID > jogos03[i].ID){
        break;
      }
     }
    // Move os elementos maiores para a direita para abrir espaço para o novo jogo
    for(j = *tam - 1; j >= i; j--){

      jogos03[j+1].ID = jogos03[j].ID;
        
      jogos03[j+1].Name = (char*)malloc((strlen(jogos03[j].Name)+1)*sizeof(char));
      strcpy(jogos03[j+1].Name,jogos03[j].Name);
            
      jogos03[j+1].Platform = (char*)malloc((strlen(jogos03[j].Platform)+1)*sizeof(char));
      strcpy(jogos03[j+1].Platform,jogos03[j].Platform);

      jogos03[j+1].Year_Of_Release =  jogos03[j].Year_Of_Release;

      jogos03[j+1].Genre = (char*)malloc((strlen(jogos03[j].Genre)+1)*sizeof(char));
      strcpy(jogos03[j+1].Genre,jogos03[j].Genre);

      jogos03[j+1].Publisher = (char*)malloc((strlen(jogos03[j].Publisher)+1)*sizeof(char));
      strcpy(jogos03[j+1].Publisher,jogos03[j].Publisher);

      jogos03[j+1].NA_Sales = jogos03[j].NA_Sales;

      jogos03[j+1].EU_Sales = jogos03[j].EU_Sales;

      jogos03[j+1].JP_sales = jogos03[j].JP_sales;

      jogos03[j+1].Other_Sales = jogos03[j].Other_Sales;

      jogos03[j+1].Global_Sales = jogos03[j].Global_Sales;

      limpaJogos02(jogos03,j);
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