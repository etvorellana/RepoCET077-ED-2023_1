#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CSVSIZE 46068

typedef struct
{
    int appId;
    char *title;
    char *dataRelease;
    char *win;
    char *mac;
    char *linux;
    char *rating;
    int positiveRatio;
    int userReviews;
    float priceFinal;
    float priceOriginal;
    float discount;
    char *steamDeck;

} Jogos;

int buscaPorID(int idDoApp, Jogos *lista, int tam);
void imprimeOsDados(Jogos *lista, int i );
void limpaMemoria( Jogos *lista );

int main(void)
{
    Jogos *acervo;
    FILE *fp;
    char str[900];
    int i = 0;
    int id, escolha, idDoAPP, tam;
    tam = 0;

    acervo = (Jogos *)malloc(CSVSIZE * sizeof(Jogos));

    fp = fopen("../../Data/dataSetEquipe2.csv", "r");

    if (fp == NULL)
    {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    // pegando o cabeçalho
    char *ok;
    ok = fgets(str, 900, fp); // pega a string do arquivo

    if (!ok)
    {
        printf("Erro lendo o cabeçalho do CSV!!!", str);
        return 1;
    }

    i = 0;
    char sep[] = ",";

    while (!feof(fp) && i < CSVSIZE) // enquanto nâo chegar no final do arquivo ou no tamanho do array
    {
        ok = fgets(str, 900, fp); // pega a string do arquivo

        if (ok)
        {
            tam++;
            char *campo;

            // APP ID
            campo = strtok(str, sep);      // pega a string até a primeira ','
            acervo[i].appId = atoi(campo); // converte em int

            // TITLE
            campo = strtok(NULL, sep);
            int pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].title = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].title, campo);

            // Data release
            campo = strtok(NULL, sep);
            pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].dataRelease = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].dataRelease, campo);

            // WINDOWS
            campo = strtok(NULL, sep);
            acervo[i].win = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].win, campo);

            // MAC
            campo = strtok(NULL, sep);
            acervo[i].mac = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].mac, campo);

            // LINUX
            campo = strtok(NULL, sep);
            acervo[i].linux = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].linux, campo);

            // RATING
            campo = strtok(NULL, sep);
            pos = 0;
            while (campo[pos] != 15 && pos < strlen(campo))
                pos++;
            campo[pos] = '\0';
            acervo[i].rating = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].rating, campo);

            // POSITIVE RATIO
            campo = strtok(NULL, sep);
            acervo[i].positiveRatio = atoi(campo); // converte em int

            // USER REVIEWS
            campo = strtok(NULL, sep);
            acervo[i].userReviews = atoi(campo); // converte em int

            // PRICE FINAL
            campo = strtok(NULL, sep);
            acervo[i].priceFinal = atof(campo); // converte em float

            // PRICE ORIGINAL
            campo = strtok(NULL, sep);
            acervo[i].priceOriginal = atof(campo); // converte em float

            // DISCOUNT
            campo = strtok(NULL, sep);
            acervo[i].discount = atof(campo); // converte em float

            // STEAM DECK
            campo = strtok(NULL, sep);
            acervo[i].steamDeck = (char *)malloc(strlen(campo) + 1);
            strcpy(acervo[i].steamDeck, campo);

            i++;
        }
    }

    do
    {

        printf("Informe o modo de busca: \n1 - Indice\n2- Id do app\n\nResposta: ");
        scanf("%d", &escolha);

        if (escolha != 1 && escolha != 2) printf("Opção inválida, escolha 1 ou 2.\n");

    } while (escolha != 1 && escolha != 2);

    if (escolha == 1)
    {

        do
        {
            printf("\n\nEntre com índice de um item do acervo (-1 para sair) (%d < Indice < %d): ", 0, i - 1);
            scanf("%d", &id);

            if (id == -1)
            {
                exit(1);
            }
            else if (id > (i - 1))
            {
                printf("\nValor fora do intervalo!\n");
                continue;
            }

            imprimeOsDados( acervo, id );

        } while (id != -1);
    }
    else // Bloco de código para pesquisar por ID.
    {

        int index, idBusca;

        printf("Entre com o id do APP: ");
        scanf("%d", &idBusca);

        acervo[tam].appId = idBusca;
        index = buscaPorID(idBusca, acervo, tam);

        if(index < tam){
            imprimeOsDados( acervo, index );
        }else{
            printf("Nenhum jogo foi encontrado com o id %d\n\n", idBusca);
        }
        
    }

    limpaMemoria( acervo );

    free( acervo );

    int err = fclose(fp);

    if (err)
    {
        printf("Arquivo incorretamente fechado!!\n");
    }

    return 0;
}

int buscaPorID(int idDoAPP, Jogos *lista, int tam) //Função que realiza busca por ID.
{

    int cont = 0;

    while (cont < tam)
    {

        if (lista[cont].appId == idDoAPP)
        {
            return cont;
        }

        cont++;
    }

    if (cont >= tam) //Retorno para caso o jogo não tenha sido encontrado.
    {
        return tam;
    }
}

void imprimeOsDados(Jogos *lista, int i ) {//Esta função imprime os atributos da estrutura de acordo com o índice fornecido.

    printf("\nApp Id: %d\n", lista[i].appId);
    printf("Title: %s\n", lista[i].title);
    printf("Data Release: %s\n", lista[i].dataRelease);
    printf("Windows: %s\n", lista[i].win);
    printf("Mac: %s\n", lista[i].mac);
    printf("Linux: %s\n", lista[i].linux);
    printf("Rating: %s\n", lista[i].rating);
    printf("Ratio: %d\n", lista[i].positiveRatio);
    printf("Users Review: %d\n", lista[i].userReviews);
    printf("Final Price : %.2f\n", lista[i].priceFinal);
    printf("Original Price: %.2f\n", lista[i].priceOriginal);
    printf("Discount: %.2f\n", lista[i].discount);
    printf("Steam Deck: %s\n", lista[i].steamDeck);

}

void limpaMemoria( Jogos *lista ) { // Esta função realiza a liberação de memória que fora alocada.

    for(int j = 0; j < CSVSIZE; j++){
        free(lista[j].title);
        free(lista[j].dataRelease);
        free(lista[j].win);
        free(lista[j].mac);
        free(lista[j].linux);
        free(lista[j].rating);
        free(lista[j].steamDeck);
    }

}