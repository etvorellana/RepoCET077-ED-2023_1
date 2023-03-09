// Biblioteca de funções

#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h"

TBook* carregaDados(char *fileName, int *tam)
{
    TBook *acervo;
    FILE *fp;
    char str[900];  // para ler uma linha do arquivo
    int i = 0;
    
    // Vamos criar um array para armazenar nossos livros
    acervo = (TBook*) malloc(CSVSIZE*sizeof(TBook));

    fp = fopen(fileName, "r");
    
    // Vamos abrir um arquivo para leitura e verificar se foi tudo bem
    if(fp == NULL) // Ponteiro nulo significa problemas na abertura do arquivo
    {
        printf("Arquivo não pode ser aberto\n");
        return NULL;
    }
    // Se chegamos até aqui é porque o arquivo está aberto
    
    // pegando o cabeçalho
    char *ok; // se ok for NULL teve problema na leitura
    ok = fgets(str, 900, fp); // pega a string do arquivo 
    if(!ok) // se ok != NULL (NULL é Falso, diferente de NULL verdadeiro)
    {
        printf("Erro lendo o cabeçalho do CSV!!!", str);
        return NULL;
    }     
    i = 0;
    char sep[] = ",";
    while(!feof(fp) && i < CSVSIZE) // enquanto nâo chegar no final do arquivo ou no tamanho do array
    {   
        ok = fgets(str, 900, fp); // pega a string do arquivo 
        if(ok) // se ok != NULL (NULL é Falso, diferente de NULL verdadeiro)
        {
            char *campo;

            //int bookID
            campo = strtok(str, sep);  // pega a string até a primeira ','
            acervo[i].bookID = atoi(campo); // converte em int
            
            //char *title
            campo = strtok(NULL, sep); // pega a string até a próxima ','
            acervo[i].title = (char*) malloc(strlen(campo)); // aloca uma array 
            strcpy(acervo[i].title, campo); // copia o conteúdo da string

            //char *authors
            campo = strtok(NULL, sep);
            acervo[i].authors = (char*) malloc(strlen(campo));
            strcpy(acervo[i].authors, campo);

            //float avgRating
            campo = strtok(NULL, sep);
            acervo[i].avgRating = atof(campo); // converte em float

            //char *isbn
            campo = strtok(NULL, sep);
            acervo[i].isbn = (char*) malloc(strlen(campo));
            strcpy(acervo[i].isbn, campo);

            //char *isbn13
            campo = strtok(NULL, sep);
            acervo[i].isbn13 = (char*) malloc(strlen(campo));
            strcpy(acervo[i].isbn13, campo);

            //char *lang
            campo = strtok(NULL, sep);
            acervo[i].lang = (char*) malloc(strlen(campo));
            strcpy(acervo[i].lang, campo);

            //int numPages
            campo = strtok(NULL, sep);
            acervo[i].numPages = atoi(campo);

            //int ratCounts
            campo = strtok(NULL, sep);
            acervo[i].ratCounts = atoi(campo);

            //int txtRevCounts
            campo = strtok(NULL, sep);
            acervo[i].txtRevCounts = atoi(campo);

            //char pubDate[11]
            campo = strtok(NULL, sep);
            acervo[i].pubDate = (char*) malloc(strlen(campo));
            strcpy(acervo[i].pubDate, campo);

            //char publisher[100];    // publisher - Scholastic Inc. 
            campo = strtok(NULL, sep);
            // o último campo termina com caractere 10 e pode conter lixo no final
            int pos = 0;
            while(campo[pos] != 10 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0'; // substituir 10 por '\0'
            acervo[i].publisher = (char*) malloc(strlen(campo));
            strcpy(acervo[i].publisher, campo);
            
            i++;  // próximo item 
        }
    }
    *tam = i;
    int err = fclose(fp);
    if (err) // err != 0
    {
        printf("Arquivo incorretamente fechado!!\n");
    }
    return acervo;
}

void limpaAcervo(TBook *acervo, int tam)
{
    for(int j = 0; j < tam; j++)
    {
        free(acervo[j].title);
        free(acervo[j].authors);
        free(acervo[j].isbn);
        free(acervo[j].isbn13);
        free(acervo[j].lang);
        free(acervo[j].pubDate);
        free(acervo[j].publisher);
    }
    free(acervo);
}
