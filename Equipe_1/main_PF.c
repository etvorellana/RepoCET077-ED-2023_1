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

