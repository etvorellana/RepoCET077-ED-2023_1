#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(void){
  Games *jogos;
  int tam;
  jogos = carregaDados("../../../Data/Grupo1DataSet.csv" , &tam);
  
  //Pilha linear
  
  TPilhaLinear *pilha;
  Games *Jogo_removido;
  Jogo_removido = IniciaLista(1);
  pilha = criaPilhaLinear(10);

  printf("Clique no enter para ver as demonstrações");
  
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


