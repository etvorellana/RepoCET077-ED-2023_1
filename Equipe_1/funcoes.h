// Biblioteca de funções

#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "struct.h"
Games* IniciaLista(int capacidade);
int buscaPorId(int ID, Games* lista, int *tam);

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

int buscaPorId(int ID, Games* lista, int *tam){
  
  for(int i = 0; i < *tam; i++){
    if(ID == lista[i].ID)
      return i;
    }
  return -1;
}

Games* IniciaLista(int capacidade){
  Games* jogos;
  jogos = (Games*) malloc((capacidade+1)*sizeof(Games));
  return jogos;
}


/* 
    Tarefa para a aula de 27/03/2023
    Esta função faz uma inclusão na lista, de tamanho tam,
    de um novo registro. 
    Antes de chamar esta função o usuário deve verificar se:
    * A lista tem capacidade para um novo registro, ou seja, se
    o tamanho é menor que a capacidade;
    Entrada 
    * book: Registro que se deseja incluir
    * lista: ponteiro para o array da lista
    * tam: ponteiro para quantidade de registros na lista
    Retorna
    * Verdadeiro (1) se conseguir incluir o novo registro na lista.
    Novos elementos sempre serão incluídos no final da lista (na 
    posição de índice tam) e após a inclusão o tamanho da lista deve
    ser incrementado;  
    * Falso (0) se não for possível incluir o registro na lista. Um 
    registro não poderá ser incluído na lista se já existir nela 
    outro registro com o mesmo campo chave (isbn) 
*/
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

/* 
    Tarefa para a aula de 27/03/2023
    Esta função faz uma remoção na lista, de tamanho tam,
    do registro com campo chave isbn. 
    Antes de chamar esta função o usuário deve verificar se:
    * A lista não está vazia, ou seja, se o tamanho é maior que 
    zero;
    Entrada 
    * isbn: Registro que se deseja remover
    * lista: ponteiro para o array da lista
    * tam: ponteiro para quantidade de registros na lista
    Retorna
    * Verdadeiro (1) se conseguir remover o registro na lista. A 
    remoção de um registro do interior da lista não pode deixar espaços 
    vazios no array e, após a mesma, o tamanho da lista deve ser 
    decrementado;
    * Falso (0) se não for possível remover o registro da lista. Um 
    registro não poderá ser removido da lista se não existir nela 
    um registro com o campo chave especificado (isbn). 
*/
int remJogo(Games jogo, Games* jogos02, int* tam){
  if(*tam>1){
    int ok = buscaPorId(jogo.ID,jogos02, tam);
    if(ok!=-1){
      //printf("\n\nTeste01\n\n");
      limpaJogos02(jogos02, ok);
      printf("\n\nTeste02\n\n");
      jogos02[ok] = jogo;
      --(*tam);
      return 1;
    }
  }
  return 0;
}
