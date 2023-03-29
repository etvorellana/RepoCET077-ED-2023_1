#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main(void){
  Games *jogos;
  int tam;

  jogos = carregaDados("../../Data/Grupo1DataSet.csv", &tam);


/*
  do{
    printf("Entre com o índice de um dos jogos (%d < GameID < %d): ", 0, tam);
    scanf("%d", &id);
    if(id <= 0 && id >= tam){
      printf("\nId incorreto!!\n\n");
    }
  } while (id <= 0 && id >= tam);

  //printf(" Nome: %s\n Plataforma: %s\n Ano de laçamento: %d\n Genero: %s\n Empresa: %s\n Vendas America do Norte: %.2f\n Vendas Estados Unidos: %.2f\n Vendas Japão: %.2f\n Outras vendas: %.f\n Vendas globais: %.2f\n ",jogos[id].Name,jogos[id].Platform,jogos[id].Year_Of_Release,jogos[id].Genre,jogos[id].Publisher,jogos[id].NA_Sales,jogos[id].EU_Sales,jogos[id].JP_sales,jogos[id].Other_Sales,jogos[id].Global_Sales);
*/

  //Criando nossa nova lista com 100 jogos
  Games *jogos02;
  int tam02 = 0; // tamanho de jogos 02
  int capacidade02 = 100; // capacidade de jogos 02
    
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
  printf("Foram incluídos %d registros na coleção\n", ok);
    
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
  printf("Foram achados %d registros na coleção\n", ok);

  //teste
  //for(int i=0; i<100; i++){
    //printf("\n\n\n Nome: %s\n Plataforma: %s\n Ano de laçamento: %d\n Genero: %s\n Empresa: %s\n Vendas America do Norte: %.2f\n Vendas Estados Unidos: %.2f\n Vendas Japão: %.2f\n Outras vendas: %.f\n Vendas globais: %.2f\n\n\n ",jogos02[i].Name,jogos02[i].Platform,jogos02[i].Year_Of_Release,jogos02[i].Genre,jogos02[i].Publisher,jogos02[i].NA_Sales,jogos02[i].EU_Sales,jogos02[i].JP_sales,jogos02[i].Other_Sales,jogos02[i].Global_Sales);
  //}





  
  //removendo jogos
  try = 0, ok = 0;  
  while(tam02 > 0){
    int idx = rand()%tam;
    try++;
    if(remJogo(jogos[idx], jogos02, &tam02))
      ok++;
  }

  printf("Foram realizadas %d tentativas de remoção\n", try);
  printf("Foram removidos %d registros na coleção\n", ok);

  //limpaJogos(jogos02, tam02);
  limpaJogos(jogos, tam);
  
  return 0;
}