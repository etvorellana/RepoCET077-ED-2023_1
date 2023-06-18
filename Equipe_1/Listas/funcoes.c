#include "funcoes.h"
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

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
  jogos = (Games*) malloc((capacidade)*sizeof(Games));
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

void limpaJogos03(Games *jogo){
    free(jogo->Name);
    free(jogo->Platform);
    free(jogo->Genre);
    free(jogo->Publisher);
}

//FUNÇÕES PARA LISTAS DESORDENADAS

int buscaPorId(int ID, Games* lista, int tam){
  int i;
  for(i = 0; i < tam; i++){
    if(ID == lista[i].ID)
      return i;
    }
  return i;
}

Games CopyGames(Games jogo){
   Games cpyJogo;
  
   cpyJogo.ID = jogo.ID;

        
    cpyJogo.Name = (char*)malloc((strlen(jogo.Name)+1)*sizeof(char));
    strcpy(cpyJogo.Name,jogo.Name);
            
    cpyJogo.Platform = (char*)malloc((strlen(jogo.Platform)+1)*sizeof(char));
    strcpy(cpyJogo.Platform,jogo.Platform);

    cpyJogo.Year_Of_Release =  jogo.Year_Of_Release;

    cpyJogo.Genre = (char*)malloc((strlen(jogo.Genre)+1)*sizeof(char));
    strcpy(cpyJogo.Genre,jogo.Genre);

    cpyJogo.Publisher = (char*)malloc((strlen(jogo.Publisher)+1)*sizeof(char));
    strcpy(cpyJogo.Publisher,jogo.Publisher);

    cpyJogo.NA_Sales = jogo.NA_Sales;

    cpyJogo.EU_Sales = jogo.EU_Sales;

    cpyJogo.JP_sales = jogo.JP_sales;

    cpyJogo.Other_Sales = jogo.Other_Sales;

    cpyJogo.Global_Sales = jogo.Global_Sales;

   return cpyJogo;
  
}

int incJogo(Games jogos, Games* jogos02, int* tam){
  int ok = buscaPorId(jogos.ID,jogos02, *tam);
  if(ok == (*tam)){
    
    jogos02[*tam] = CopyGames(jogos);

    ++(*tam);
    return 1;
  }
  else{
    return 0;
  }
}

int remJogo(Games jogo, Games* jogos02, int* tam){
  if((*tam)>1){
    int ok = buscaPorId(jogo.ID,jogos02, *tam);
    if(ok != (*tam)){
      limpaJogos02(jogos02, ok);
      jogos02[ok] = jogos02[(*tam-1)];
      --(*tam);
      return 1;
    }
  }
  if(*tam == 1){
    limpaJogos02(jogos02, 0);
    --(*tam);
    return 1;
  }
  return 0;
}

//FUNÇÕE PARA LISTAS ORDENADAS

int buscaBinRecPorId(int ID, Games *lista, int ini, int fim){
  if(fim>ini){
    int meio = (fim+ini)/2;
    if(ID == lista[meio].ID){
      return meio;
    }else if(ID < lista[meio].ID){
      return buscaBinRecPorId(ID, lista, ini, meio-1);
    }
    else if(ID > lista[meio].ID) {
      return buscaBinRecPorId(ID, lista, meio+1, fim);
    }
  }
  return ini;

}

int buscaBinPorId(int ID, Games *lista, int tamanho){
    int inicio = 0;
    int fim  = tamanho-1;
    int meio;

    while(inicio<fim){
        meio = (inicio+fim)/2;

        if(lista[meio].ID == ID){
            return meio;
        }
        else if(lista[meio].ID<ID){
            inicio = meio + 1;
        }
        else{
            fim = meio-1;
        }

    }
    return -inicio;
  
}

int remJogoOrdenado(Games jogo, Games* jogos03, int* tam){
  if((*tam)>1){
    int pos = buscaBinRecPorId(jogo.ID,jogos03,0,*tam);
    if(jogos03[pos].ID == jogo.ID){
      
      for(int i=pos; i<(*tam)-1; i++){
        limpaJogos02(jogos03, i);
    
        jogos03[i] = CopyGames(jogos03[i+1]);
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
  int j;
  if(jogos03[pos].ID != jogo.ID){
    // Mosve os elementos maiores para a direita para abrir espaço para o novo jogo
    for(j = *tam - 1; j >= pos; j--){

      jogos03[j+1] = jogos03[j];

    }
    // Insere o novo jogo na posição correta

    jogos03[pos] = CopyGames(jogo);

    ++(*tam);
    return 1;
  }
  return 0;
  
}

//FUNÇÕES PARA BUSCA, REMOÇÃO E INCLUSÃO GERAL
  
Tlista criaListaLinear(int cap, int eOrd){
  
  Tlista l;
  
  Games* jogo = IniciaLista(cap);
  
  l.capacidade = cap;
  l.tam = 0;
  l.Lista = jogo;
  l.eOrdenada = eOrd;

  return l;
  
}

int Busca_Geral(int ID, Tlista l){
  if(l.eOrdenada == 0){
    if(l.tam == 0){
      return 0;
    }else{
       return buscaPorId(ID, l.Lista, l.tam);
    }
  }
  else{
   if(l.tam == 0){
     return 0;
   }
    else{
      return buscaBinRecPorId(ID, l.Lista, 0, l.tam);
    }
   
  }
}

int Inc_Geral(Games jogo, Tlista *l){
  if((*l).eOrdenada == 0){
     return incJogo(jogo, (*l).Lista, &((*l).tam));
  }
  else{
   int ok=incJogoOrdenado(jogo, (*l).Lista, &((*l).tam));
   
    return ok;
  }
}

int Rem_Geral(Games jogo, Tlista *l){
  
  if((*l).eOrdenada == 0){
    
     return remJogo(jogo, (*l).Lista, &((*l).tam));
  }
  else{
   return remJogoOrdenado(jogo, (*l).Lista, &((*l).tam));
  }
}
