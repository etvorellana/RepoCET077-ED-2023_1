#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    long int ID;
    char *Name;
    char *Platform;
    int Year_Of_Release;
    char *Genre;
    char *Publisher;
    float NA_Sales;
    float EU_Sales;
    float JP_sales;
    float Other_Sales;
    float Global_Sales;
    
}Games;

void buscaId(int id, Games *jogos);

int main(){
  FILE *fp;
  Games *jogos;
  char str[900];
  char header[50];
  int ind=0;
  long int id=0;
  int stop=1;

  jogos = (Games*)malloc(16717*sizeof(Games));

  fp = fopen("../Grupo1DataSet.csv","r");

  if(fp == NULL){
    printf("Arquivo nao encontrado");
    return 0;
  }

  fscanf(fp,"%s",header);
  //printf("%s\n",header);
    
  while(!feof(fp)){

    fscanf(fp,"\n%ld",&jogos[ind].ID);
        
    fscanf(fp,",%[^,]s",str);
    jogos[ind].Name = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[ind].Name,str);
        
    fscanf(fp,",%[^,]s",str);
    jogos[ind].Platform = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[ind].Platform,str);

    fscanf(fp,",%d",&jogos[ind].Year_Of_Release);

    fscanf(fp,",%[^,]s",str);
    jogos[ind].Genre = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[ind].Genre,str);

    fscanf(fp,",%[^,]s",str);
    jogos[ind].Publisher = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(jogos[ind].Publisher,str);

        fscanf(fp,",%f,%f,%f,%f,%f,",&jogos[ind].NA_Sales,&jogos[ind].EU_Sales,&jogos[ind].JP_sales,&jogos[ind].Other_Sales,&jogos[ind].Global_Sales);

    fscanf(fp,"%[^\n]s",str);
    ind++;

  }

  while(stop!=0){
    
    printf("\n\nDigite o id do jogo: ");
    scanf("%ld",&id);
    scanf("%*[^\n]");
    scanf("%*c");
      
    buscaId(id,jogos);

    printf("\nDeseja continuar? (1-sim/0-não): ");
    scanf("%d", &stop);
    scanf("%*c");
    system("clear||cls");
  }

  for(int i = 0;i<(ind-1);i++ ){
    free(jogos[i].Name);
    free(jogos[i].Platform);
    free(jogos[i].Genre);
    free(jogos[i].Publisher);    
  }
   
  return 0;
}

void buscaId(int id, Games *jogos){
    for(int i=0; i<=16718; i++){
      if(jogos[i].ID == id){
         printf(" Nome: %s\n Plataforma: %s\n Ano de laçamento: %d\n Genero: %s\n Empresa: %s\n Vendas America do Norte: %.2f\n Vendas Estados Unidos: %.2f\n Vendas Japão: %.2f\n Outras vendas: %.f\n Vendas globais: %.2f\n ",jogos[i].Name,jogos[i].Platform,jogos[i].Year_Of_Release,jogos[i].Genre,jogos[i].Publisher,jogos[i].NA_Sales,jogos[i].EU_Sales,jogos[i].JP_sales,jogos[i].Other_Sales,jogos[i].Global_Sales);
        break;
      }
      if(i == 16718 && jogos[i].ID != id){
        printf("ID inexistente!!");
      }
    }
}