// O código encerra no meio da execução, lendo exatamente até a linha 5506


#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#define CSVSIZE 12000


// Armazenando as informa��es de um libro de acordo com os campos de CSV
typedef struct
{
    int bookID;             // bookID - 1,
    char *artist;            // title - Harry Potter and the Half-Blood Prince (Harry Potter  #6),
    char *song;          // authors - J.K. Rowling/Mary GrandPr�,
    int days;             // average_rating - 4.57,
    float topten;          // top 10,
    int peakposition;           // maior posicao,
    char *peakpostime;          // Numero de vezes maior posi��o,
    int peakstreams;          // peak streams - 2905678,
    char *totalstreams;        // total streams - 439785969,
} Tspotify;

int main(void)
{
    Tspotify *acervo;
    FILE *fp;
    char str[900];  // para ler uma linha do arquivo
    int i = 0;

    // Vamos criar um array para armazenar nossos livros
    acervo = (Tspotify*) malloc(CSVSIZE*sizeof(Tspotify));

    fp = fopen("songs.csv", "r");

    // Vamos abrir um arquivo para leitura e verificar se foi tudo bem
    if(fp == NULL) // Ponteiro nulo significa problemas na abertura do arquivo
    {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }
    // Se chegamos at� aqui � porque o arquivo est� aberto

    // pegando o cabe�alho
    char *ok; // se ok for NULL teve problema na leitura
    ok = fgets(str, 900, fp); // pega a string do arquivo
    if(!ok) // se ok != NULL (NULL � Falso, diferente de NULL verdadeiro)
    {
        printf("Erro lendo o cabe�alho do CSV!!!", str);
        return 1;
    }
    i = 0;
    char sep[] = ",";

    while(!feof(fp) && i < CSVSIZE) // enquanto n�o chegar no final do arquivo ou no tamanho do array
    {


        ok = fgets(str,900, fp); // pega a string do arquivo

        if(ok) // se ok != NULL (NULL � Falso, diferente de NULL verdadeiro)
        {
            char *campo;
             printf("\n Foi a %d musica\n", i);
 // printf("1\n");
            //int bookID
            campo = strtok(str, sep);  // pega a string at� a primeira ','
            acervo[i].bookID = atoi(campo); // converte em int
 //printf("2\n");
            //char *artist
            campo = strtok(NULL, sep); // pega a string at� a pr�xima ','
            acervo[i].artist = (char*) malloc(strlen(campo)+1); // aloca uma array
            strcpy(acervo[i].artist, campo); // copia o conte�do da string
 //printf("3\n");
            //char *song
            campo = strtok(NULL, sep);
            acervo[i].song = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].song, campo);
 //printf("4\n");
            //int days
            campo = strtok(NULL, sep);
            acervo[i].days = atoi(campo); // converte em int
 //printf("5\n");
            //float top 10
            campo = strtok(NULL, sep);
            acervo[i].topten = atof(campo);
 //printf("6\n");
            //int peak positions
            campo = strtok(NULL, sep);
            acervo[i].peakposition = atoi(campo);
// printf("7\n");
            //char *peak position times
            campo = strtok(NULL, sep);
            acervo[i].peakpostime = (char*)malloc(strlen(campo)+1);
            strcpy(acervo[i].peakpostime, campo);
 //printf("8\n");
            //int peak streams
            campo = strtok(NULL, sep);
            acervo[i].peakstreams = atoi(campo);
 //printf("9\n");
            //char *total streams
            campo = strtok(NULL, sep);
            int pos = 0;
            while(campo[pos] != 10 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].totalstreams = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].totalstreams, campo);
// printf("10\n");
            i++;
        }
        // printf("11\n");
    }
    int id;
   //  printf("%d",i);
    do
    {
        printf("Entre com �ndice de um item do acervo (%d < BookID < %d): ", 0, i);
        scanf("%d", &id);
    } while (id <= 0 && id >= i);

    printf("%d,", acervo[id].bookID);
    printf("%s,", acervo[id].artist);
    printf("%s,", acervo[id].song);
    printf("%i,", acervo[id].days);
    printf("%.2f,", acervo[id].topten);
    printf("%i,", acervo[id].peakposition);
    printf("%s,", acervo[id].peakpostime);
    printf("%d,", acervo[id].peakstreams);
    printf("%s\n,", acervo[id].totalstreams);

    for(int j = 0; j < i; j++)
    {
        free(acervo[j].artist);
        free(acervo[j].song);
        free(acervo[j].peakpostime);
        free(acervo[j].totalstreams);
    }
    free(acervo);
    int err = fclose(fp);
    if (err) // err != 0
    {
        printf("Arquivo incorretamente fechado!!\n");
    }
    return 0;
}

// colocar isto numa fun��o
