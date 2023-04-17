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

int incJogo(Games jogos, Games* jogos02, int* tam){
  int ok = buscaPorId(jogos.ID,jogos02, *tam);
  if(ok == (*tam)){
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
  int j;
  if(jogos03[pos].ID != jogo.ID){
    // Mosve os elementos maiores para a direita para abrir espaço para o novo jogo
    for(j = *tam - 1; j >= pos; j--){

      jogos03[j+1] = jogos03[j];

    }
    // Insere o novo jogo na posição correta

    jogos03[pos].ID = jogo.ID;
        
    jogos03[pos].Name = (char*)malloc((strlen(jogo.Name)+1)*sizeof(char));
    strcpy(jogos03[pos].Name,jogo.Name);
            
    jogos03[pos].Platform = (char*)malloc((strlen(jogo.Platform)+1)*sizeof(char));
    strcpy(jogos03[pos].Platform,jogo.Platform);

    jogos03[pos].Year_Of_Release =  jogo.Year_Of_Release;

    jogos03[pos].Genre = (char*)malloc((strlen(jogo.Genre)+1)*sizeof(char));
    strcpy(jogos03[pos].Genre,jogo.Genre);

    jogos03[pos].Publisher = (char*)malloc((strlen(jogo.Publisher)+1)*sizeof(char));
    strcpy(jogos03[pos].Publisher,jogo.Publisher);

    jogos03[pos].NA_Sales = jogo.NA_Sales;

    jogos03[pos].EU_Sales = jogo.EU_Sales;

    jogos03[pos].JP_sales = jogo.JP_sales;

    jogos03[pos].Other_Sales = jogo.Other_Sales;

    jogos03[pos].Global_Sales = jogo.Global_Sales;

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

//FUNÇÕES PARA PILHAS

void demonstrar_add_pilha(int try1,int ok,TPilhaLinear *pilha){
  scanf("%*c");
  system("clear||cls");
  printf("\n--------------------------Inclusão Pilha---------------------");
  printf("\n\nTentativas de inclusão na Pilha: %d",try1);
  printf("\nforam incluidos %d registros na Pilha",ok);

  if(pilha->topo == pilha->cap){
    printf("\n\n\tPilha cheia\n");
  }
  
  for(int i = pilha->topo-1;i>=0;i-- ){
      printf("\n\t%d",pilha->pilha[i].ID);
    }

  
}

void demonstrar_rem_pilha(TPilhaLinear *pilha){
  scanf("%*c");
  system("clear||cls");
  printf("\n--------------------------Remoção Pilha---------------------");
 
  if(pilha->topo == 0){
    printf("\n\tPilha vazia");
  }else{
    for(int i = pilha->topo-1;i>=0;i-- ){
      printf("\n\t%d",pilha->pilha[i].ID);
    }
  }
  
  
}

TPilhaLinear* criaPilhaLinear(int cap){
    TPilhaLinear *fila;
  
    fila = (TPilhaLinear*)malloc(sizeof(TPilhaLinear));
    fila->cap = cap;
    fila->topo = 0;
    fila->pilha=IniciaLista(cap);
  
    return fila;
}

int insereNaPilha(Games jogo, TPilhaLinear* pilha){
    if(pilha->topo == pilha->cap){
      return 0;
    }

    int ok = buscaPorId(jogo.ID, pilha->pilha, pilha->topo);
    if(ok != pilha->topo){
      return 0;
    }
    else{
      
      pilha->pilha[pilha->topo].ID = jogo.ID;
          
      pilha->pilha[pilha->topo].Name = (char*)malloc((strlen(jogo.Name)+1)*sizeof(char));
      strcpy(pilha->pilha[pilha->topo].Name,jogo.Name);
              
      pilha->pilha[pilha->topo].Platform = (char*)malloc((strlen(jogo.Platform)+1)*sizeof(char));
      strcpy(pilha->pilha[pilha->topo].Platform,jogo.Platform);
  
      pilha->pilha[pilha->topo].Year_Of_Release =  jogo.Year_Of_Release;
  
      pilha->pilha[pilha->topo].Genre = (char*)malloc((strlen(jogo.Genre)+1)*sizeof(char));
      strcpy(pilha->pilha[pilha->topo].Genre,jogo.Genre);
  
      pilha->pilha[pilha->topo].Publisher = (char*)malloc((strlen(jogo.Publisher)+1)*sizeof(char));
      strcpy(pilha->pilha[pilha->topo].Publisher,jogo.Publisher);
  
      pilha->pilha[pilha->topo].NA_Sales = jogo.NA_Sales;
  
      pilha->pilha[pilha->topo].EU_Sales = jogo.EU_Sales;
  
      pilha->pilha[pilha->topo].JP_sales = jogo.JP_sales;
  
      pilha->pilha[pilha->topo].Other_Sales = jogo.Other_Sales;
  
      pilha->pilha[pilha->topo].Global_Sales = jogo.Global_Sales;

      pilha->topo++;
      return 1;
    }
}

Games* removeDaPilha(TPilhaLinear* pilha){
  
  if(pilha->topo == 0){
    return NULL;
  }
  else{
    Games *jogo_removido;
    jogo_removido = (Games*)malloc(sizeof(Games));
    jogo_removido = &(pilha->pilha[pilha->topo-1]);
    pilha->topo--;
    return jogo_removido;
  }
    
}

//FUNÇÕES PARA FILA

void demonstrar_add_fila(int try1,int ok,TFilaLinear *fila){
  scanf("%*c");
  system("clear||cls");
  printf("\n--------------------------Inclusão Fila---------------------");
  printf("\n\nTentativas de inclusão na Fila: %d",try1);
  printf("\nforam incluidos %d registros na Fila",ok);

  if(fila->fim - fila->ini == fila->cap){
    printf("\n\n\tFila cheia\n");
  }
  
  for(int i = fila->fim-1;i>=fila->ini;i-- ){
      printf("\n\t%d",fila->fila[i].ID);
    }
}

void demonstrar_rem_fila(TFilaLinear *fila){
  scanf("%*c");
  system("clear||cls");
  printf("\n--------------------------Remoção Fila---------------------");
 
  if(fila->ini == fila->fim){
    printf("\n\tFila vazia");
  }else{
    for(int i = fila->fim-1;i>=fila->ini;i-- ){
      printf("\n\t%d",fila->fila[i].ID);
    }
  }
}


TFilaLinear* criaFilaLinear(int cap){
  TFilaLinear *no;

  no = (TFilaLinear*) malloc(sizeof(TFilaLinear));
  no->fila = IniciaLista(cap);
  no->cap = cap;
  no->ini = 0;
  no->fim = 0;
  
  return no;
}

int insereNaFila(Games jogo, TFilaLinear* fila){

  if(fila->fim - fila->ini == fila->cap){
    return 0;
  }
  int ok = buscaPorId(jogo.ID, fila->fila, fila->fim);
  if(ok != fila->fim){
    return 0;
  }
  else{
    
    fila->fila[fila->fim].ID = jogo.ID;
          
    fila->fila[fila->fim].Name = (char*)malloc((strlen(jogo.Name)+1)*sizeof(char));
    strcpy(fila->fila[fila->fim].Name,jogo.Name);
              
    fila->fila[fila->fim].Platform = (char*)malloc((strlen(jogo.Platform)+1)*sizeof(char));
    strcpy(fila->fila[fila->fim].Platform,jogo.Platform);
  
    fila->fila[fila->fim].Year_Of_Release =  jogo.Year_Of_Release;
  
    fila->fila[fila->fim].Genre = (char*)malloc((strlen(jogo.Genre)+1)*sizeof(char));
    strcpy(fila->fila[fila->fim].Genre,jogo.Genre);
  
    fila->fila[fila->fim].Publisher = (char*)malloc((strlen(jogo.Publisher)+1)*sizeof(char));
    strcpy(fila->fila[fila->fim].Publisher,jogo.Publisher);
  
    fila->fila[fila->fim].NA_Sales = jogo.NA_Sales;
  
    fila->fila[fila->fim].EU_Sales = jogo.EU_Sales;
  
    fila->fila[fila->fim].JP_sales = jogo.JP_sales;
  
    fila->fila[fila->fim].Other_Sales = jogo.Other_Sales;
  
    fila->fila[fila->fim].Global_Sales = jogo.Global_Sales;

    fila->fim++;
    
    return 1;
      
  }
}

Games* removeDaFila(TFilaLinear* fila){
  if(fila->ini == fila->fim){
    return NULL;
  }
  else{
    Games *jogo_removido;
    jogo_removido = (Games*)malloc(sizeof(Games));
    jogo_removido = &(fila->fila[fila->ini]);
    fila->ini++;
    return jogo_removido;
  }
}