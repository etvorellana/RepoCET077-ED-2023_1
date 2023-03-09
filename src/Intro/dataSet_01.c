#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#define CSVSIZE 12000


// Armazenando as informações de um libro de acordo com os campos de CSV
typedef struct
{
    int bookID;             // bookID - 1,
    char *title;            // title - Harry Potter and the Half-Blood Prince (Harry Potter  #6),
    char *authors;          // authors - J.K. Rowling/Mary GrandPré,
    float avgRating;        // average_rating - 4.57,
    char *isbn;          // isbn - 0439785960,
    char *isbn13;        // isbn13 - 9780439785969,
    char *lang;           // language_code - eng,
    int numPages;           // num_pages - 652,
    int ratCounts;          // ratings_count - 2095690,
    int txtRevCounts;       // text_reviews_count - 27591,
    char *pubDate;       // publication_date - 9/16/2006,
    char *publisher;        // publisher - Scholastic Inc.  
} TBook;

int main(void)
{
    TBook *acervo;
    FILE *fp;
    char str[900];  // para ler uma linha do arquivo
    int i = 0;
    
    // Vamos criar um array para armazenar nossos livros
    acervo = (TBook*) malloc(CSVSIZE*sizeof(TBook));

    fp = fopen("../../Data/books.csv", "r");
    
    // Vamos abrir um arquivo para leitura e verificar se foi tudo bem
    if(fp == NULL) // Ponteiro nulo significa problemas na abertura do arquivo
    {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }
    // Se chegamos até aqui é porque o arquivo está aberto
    
    // pegando o cabeçalho
    char *ok; // se ok for NULL teve problema na leitura
    ok = fgets(str, 900, fp); // pega a string do arquivo 
    if(!ok) // se ok != NULL (NULL é Falso, diferente de NULL verdadeiro)
    {
        printf("Erro lendo o cabeçalho do CSV!!!", str);
        return 1;
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
            acervo[i].title = (char*) malloc(strlen(campo)+1); // aloca uma array 
            strcpy(acervo[i].title, campo); // copia o conteúdo da string

            //char *authors
            campo = strtok(NULL, sep);
            acervo[i].authors = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].authors, campo);


            //float avgRating
            campo = strtok(NULL, sep);
            acervo[i].avgRating = atof(campo); // converte em float

            //char *isbn
            campo = strtok(NULL, sep);
            acervo[i].isbn = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].isbn, campo);

            //char *isbn13
            campo = strtok(NULL, sep);
            acervo[i].isbn13 = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].isbn13, campo);

            //char *lang
            campo = strtok(NULL, sep);
            acervo[i].lang = (char*) malloc(strlen(campo)+1);
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
            acervo[i].pubDate = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].pubDate, campo);

            //char publisher[100];    // publisher - Scholastic Inc. 
            campo = strtok(NULL, sep);
            int pos = 0;
            while(campo[pos] != 10 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].publisher = (char*) malloc(strlen(campo)+1);
            strcpy(acervo[i].publisher, campo);
            
            i++;
        }
    }

    int id;
    do
    {
        printf("Entre com índice de um item do acervo (%d < BookID < %d): ", 0, i);
        scanf("%d", &id);
    } while (id <= 0 && id >= i);

    printf("%d,", acervo[id].bookID);
    printf("%s,", acervo[id].title);
    printf("%s,", acervo[id].authors);
    printf("%.2f,", acervo[id].avgRating);
    printf("%s,", acervo[id].isbn);
    printf("%s,", acervo[id].isbn13);
    printf("%s,", acervo[id].lang);
    printf("%d,", acervo[id].numPages);
    printf("%d,", acervo[id].ratCounts);
    printf("%d,", acervo[id].txtRevCounts);
    printf("%s,", acervo[id].pubDate);
    printf("%s\n", acervo[id].publisher);

    for(int j = 0; j < i; j++)
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
    int err = fclose(fp);
    if (err) // err != 0
    {
        printf("Arquivo incorretamente fechado!!\n");
    }
    return 0;
}

// colocar isto numa função