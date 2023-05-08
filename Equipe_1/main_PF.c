#include <stdio.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "funcoes_PF.h"

int main(void) {
  Games *jogos;
  int tam;

  jogos = carregaDados("../../Data/Grupo1DataSet.csv", &tam);

  //"Inicializando" a lista com os eleemntos do DataSet.
  TListaEnc *lista;
  lista = iniListaEnc();

  for(int i = 0; i < 100 ; i++){
    insereNoFimListaEnc(jogos[i], lista);
  }

  printf("Primeiro Elemento da lista:");
  imprimirNo(lista->ini);
  printf("\nUltimo Elemento da lista:");
  
  imprimirNo(lista->fim);

  //Tira da lista para a Pilha:
  TPilhaEnc* pilha;
  pilha = iniPilhaEnc();

  int aux;
  Games *jogo_realocado;
  

  
  for(; 0 < lista->tam; ){
   
     jogo_realocado = removeDoIniListaEnc(lista);
     
     
     aux = empilhar(*jogo_realocado, pilha);
    
    
     //limpaJogos03(jogo_realocado);
  }
 printf("\n-----------Pilha----------------\n\n");
 imprimePilha(pilha);

  //Tira da Pilha para a Fila:

  TFilaEnc *fila;
  fila = iniFilaEnc();

  for(;0<pilha->tam;){
    jogo_realocado = desempilhar(pilha);
    aux = insereNaFila(*jogo_realocado, fila);
    //limpaJogos03(jogo_realocado);
  }

  printf("\n---------------Fila----------------\n\n");
  imprimFila(fila);

  //Tira da Pilha Poe na Lista:

  
  for(;0<fila->tam;){
    
    jogo_realocado = removeDaFila(fila);
    
    aux = insereNoFimListaEnc(*jogo_realocado, lista);
    //limpaJogos03(jogo_realocado);
  }

  printf("\n\nPrimeiro Elemento da lista:");
  imprimirNo(lista->ini);
  printf("\nUltimo Elemento da lista:");
   imprimirNo(lista->fim);
}

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

//-------------------------

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

No* AlocaNo(){
  No* p;
  p = (No*)malloc(sizeof(No));
  p->prox = NULL;
  return p;
}

void ExcluirNo(No** p){
  free((*p)->jogo.Name);
  free((*p)->jogo.Platform);
  free((*p)->jogo.Publisher);
  free((*p)->jogo.Genre);
  free((*p));
  
}

void imprimirNo(No*p){
   printf("\nNome do jogo: %s",p->jogo.Name);
   printf("\nID do jogo: %d\n",p->jogo.ID);
}

No* CriaListaENdeListaLinear(Games *jogos, int tam){
  No* ini;
  if(tam == 0){
    return NULL;
  }
  else{
    ini = AlocaNo();
    ini->jogo = CopyGames(jogos[0]);
    No* p;
    p = ini;
    for(int i = 1;i<tam;i++){
      p->prox = AlocaNo();
      p = p->prox;
      p->jogo = CopyGames(jogos[i]);
      
    }
  }
  
  return ini;
}

No* FimDaListaEN(No* ini){
  No* fim;
  if(ini == NULL){
    return NULL;
  }
  else{
    No*p;
    for(p=ini; p->prox != NULL; p = p->prox ){} 
    fim = p;
  }
  return fim;
}

TListaEnc *iniListaEnc(){
  TListaEnc *lista;
  lista = (TListaEnc*)malloc(sizeof(TListaEnc));
  lista->ini = NULL;
  lista->fim = NULL;
  lista->tam = 0;
  return lista;
}

int insereNoFimListaEnc(Games jogo,TListaEnc *lista){
  No*p;
  p = AlocaNo();
  p->jogo = CopyGames(jogo);
  p->prox = NULL;
  if(lista->tam == 0){
    lista->ini = p;
    lista->fim = p;
    lista->tam++;
    
  }
  else{
    lista->fim->prox = p;
    lista->fim = p;
    lista->tam++;
  }
  return 1;
}

Games* removeDoIniListaEnc(TListaEnc *lista){
  if(lista->tam == 0){
    return NULL;
  }
  else{
    No*p;
    p=AlocaNo();
    p = lista->ini;
    lista->ini = lista->ini->prox;

    Games jogo;
    jogo = CopyGames(p->jogo);
    
    Games* jogo_ponteiro;
    
    jogo_ponteiro = &jogo;
    
    
    ExcluirNo(&p);
    
    if(lista->tam == 1){
      lista->fim = NULL;
    }
    
    lista->tam--;
    return jogo_ponteiro;
    
  }
}

TPilhaEnc* iniPilhaEnc(){
  TPilhaEnc* pilha;
  pilha = (TPilhaEnc*)malloc(sizeof(TPilhaEnc));
  pilha->tam = 0;
  pilha->topo = NULL;
  return pilha;
}

int empilhar(Games jogo, TPilhaEnc *pilha){
  No* p;
  p = AlocaNo();
  p->jogo = CopyGames(jogo);
  p->prox = pilha->topo;
  pilha->topo = p;
  pilha->tam++;
  return 1;
  
}
Games* desempilhar(TPilhaEnc *pilha){
  if(pilha->topo == NULL){
    return NULL;
  }
  else{
    No *p;
    p = pilha->topo;
    pilha->topo= pilha->topo->prox;
    
    Games jogo;
    jogo = CopyGames(p->jogo);
    Games *jogo_ponteiro;
    jogo_ponteiro = &jogo;
    ExcluirNo(&p);
    pilha->tam--;
    return jogo_ponteiro;
  }

  
}

void imprimePilha(TPilhaEnc *pilha){
  for(No*p=pilha->topo; p!=NULL; p=p->prox){
    printf("\nNome: %s",p->jogo.Name);
    printf("\nID do jogo: %d",p->jogo.ID);
  }
}

TFilaEnc* iniFilaEnc(){
  TFilaEnc *fila;
  fila = (TFilaEnc*)malloc(sizeof(TFilaEnc));
  fila->fim = NULL;
  fila->ini = NULL;
  fila->tam=0;
  return fila;
}

int insereNaFila(Games jogo,TFilaEnc *fila){
    No*p;
    p = AlocaNo();
    p->jogo = CopyGames(jogo);
    
  if(fila->tam == 0){
    fila->ini = p;
    fila->fim = p;
    fila->tam++;
  }
  else{
    fila->fim->prox = p;
    fila->fim = p;
    fila->tam++;
  }
  return 1;
}

Games* removeDaFila(TFilaEnc *fila){
  if(fila->tam == 0){
    return NULL;
  }
  else{
    No*p;
    p=AlocaNo();
    p = fila->ini;
    fila->ini = fila->ini->prox;
    
    Games jogo;
    jogo = CopyGames(p->jogo);
    
    Games* jogo_ponteiro;
    jogo_ponteiro = &jogo;
    
    ExcluirNo(&p);
    
    if(fila->tam == 1){
      fila->fim = NULL;
    }
    
    fila->tam--;
    return jogo_ponteiro;
  }
}

void imprimFila(TFilaEnc *Fila){
  for(No*p=Fila->ini;p!=NULL;p=p->prox){
    printf("\nNome: %s",p->jogo.Name);
     printf("\nID do jogo: %d",p->jogo.ID);
  }
}
