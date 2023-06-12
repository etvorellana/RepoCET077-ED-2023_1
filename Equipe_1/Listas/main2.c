#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"



int main(void){
  Games *jogos;
  int tam;
  Tlista lis[2];

  jogos = carregaDados("../../Data/Grupo1DataSet.csv" , &tam);
  

  lis[0] = criaListaLinear(100,0);
  lis[1] = criaListaLinear(100,1);

  //Criando nossa nova lista com 100 jogos
 
  
   
  int try = 0, ok = 0;  
  while(lis[0].tam < lis[0].capacidade){ // enquanto não estiver cheia{
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try++;
    if(Inc_Geral(jogos[idx], &(lis[0])) == 1)
      ok++;
  }

  printf("Foram realizadas %d tentativas de inclusão\n", try);
  printf("Foram incluídos %d registros na lista\n", ok);
    
  //Buscando jogos por id
  try = 0, ok = 0;  
  while(lis[0].tam > ok){
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try++;
    int pos = Busca_Geral(jogos[idx].ID, lis[0]);
    if(lis[0].Lista[pos].ID == jogos[idx].ID)
      ok++;
  }

  printf("Foram realizadas %d tentativas de busca\n", try);
  printf("Foram achados %d registros na lista\n", ok);

  //removendo jogos
  try = 0, ok = 0;  
  while(lis[0].tam > 0){
    int idx = rand()%tam;
    try++;
    if(Rem_Geral(jogos[idx],&(lis[0])) ==1)
      ok++;
  }
  
  printf("Foram realizadas %d tentativas de remoção\n", try);
  printf("Foram removidos %d registros na lista\n", ok);


//CRIANDO UMA LISTA COM 100 JOGOS ORDENADOS

  
   
  int try2 = 0, ok2 = 0;  
  while(lis[1].tam < lis[1].capacidade){ // enquanto não estiver cheia{
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try2++;
    if(Inc_Geral(jogos[idx], &(lis[1])))
      ok2++;
  }

  printf("\n\nForam realizadas %d tentativas de inclusão na lista ordenada\n", try2);
  printf("Foram incluídos %d registros na lista ordenada\n", ok2);
    
  //Buscando jogos por id
  try2 = 0, ok2 = 0;  
  while(lis[1].tam > ok2){
    //gera um índice aleatória do jogos
    int idx = rand()%tam;
    try2++;
    int pos = Busca_Geral(jogos[idx].ID, lis[1]);
    if(lis[1].Lista[pos].ID == jogos[idx].ID)
        ok2++;
  }

  printf("Foram realizadas %d tentativas de busca na lista ordenada\n", try2);
  printf("Foram achados %d registros na lista ordenada\n", ok2);

  //removendo jogos
  try2 = 0, ok2 = 0;  
  while(lis[1].tam > 0){
    int idx = rand()%tam;
    try2++;
    if(Rem_Geral(jogos[idx],&(lis[1])) == 1)
      ok2++;
  }
  

  printf("Foram realizadas %d tentativas de remoção na lista ordenada\n", try2);
  printf("Foram removidos %d registros na lista ordenada\n", ok2);

  //Pilha linear
  

  TPilhaLinear *pilha;
  Games *Jogo_removido;
  Jogo_removido = IniciaLista(1);
  pilha = criaPilhaLinear(10);

  
  int try3 = 0,ok3 = 0;
  while(pilha->topo<pilha->cap){
    int idx = rand()%tam;
    try3++;
    if(insereNaPilha(jogos[idx], pilha) == 1){
      ok3++;
      demonstrar_add_pilha(try3,ok3,pilha);
    }
  } 

    

  try3 = 0,ok3 = 0;
  while(pilha->topo > 0){
     demonstrar_rem_pilha(pilha);
     Jogo_removido = removeDaPilha(pilha);

     limpaJogos03(Jogo_removido);
  }


  demonstrar_rem_pilha(pilha);

  //Fila Linear

  TFilaLinear *fila;
  Games *Jogo_removido2;
  Jogo_removido2 = IniciaLista(1);
  fila = criaFilaLinear(10);

  
  int try4 = 0,ok4 = 0;
  while(fila->fim - fila->ini != fila->cap){
    int idx = rand()%tam;
    try4++;
    if(insereNaFila(jogos[idx], fila) == 1){
      ok4++;
      demonstrar_add_fila(try4,ok4,fila);
    }
  };

  try4 = 0,ok4 = 0;
  while(fila->ini != fila->fim){
     demonstrar_rem_fila(fila);
     Jogo_removido2 = removeDaFila(fila);

     limpaJogos03(Jogo_removido2);
  }
  demonstrar_rem_fila(fila);
  
  limpaJogos(jogos, tam);
  
  
  return 0;
}

