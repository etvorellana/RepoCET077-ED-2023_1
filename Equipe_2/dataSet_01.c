#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CSVSIZE 46068

typedef struct{
    
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

int main(void){
    Jogos *acervo;
    FILE *fp;
    char str[900];
    int i = 0;
    int id, escolha, idDoAPP;

    acervo = (Jogos *)malloc(CSVSIZE * sizeof(Jogos));

    fp = fopen("../../Data/dataSetEquipe2.csv", "r");

    if (fp == NULL){
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    // pegando o cabeçalho
    char *ok;
    ok = fgets(str, 900, fp); // pega a string do arquivo

    if (!ok){
        printf("Erro lendo o cabeçalho do CSV!!!", str);
        return 1;
    }

    i = 0;
    char sep[] = ",";

    while (!feof(fp) && i < CSVSIZE) // enquanto nâo chegar no final do arquivo ou no tamanho do array
    {
        ok = fgets(str, 900, fp); // pega a string do arquivo
        
        if (ok){
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

    do{

        printf("Informe o modo de busca: \n1 - Indice\n2- Id do app\n\nResposta: ");
        scanf("%d", &escolha);

        if (escolha != 1 && escolha != 2)
            printf("Opção inválida, escolha 1 ou 2.\n");

    } while (escolha != 1 && escolha != 2);

    if (escolha == 1){
        
        do{
            printf("\n\nEntre com índice de um item do acervo (-1 para sair) (%d < Indice < %d): ", 0, i - 1);
            scanf("%d", &id);

            if (id == -1){
                exit(1);
            }
            else if (id > (i - 1)) {
                printf("\nValor fora do intervalo!\n");
                continue;
            }

            printf("\nApp Id: %d\n", acervo[id].appId);
            printf("Title: %s\n", acervo[id].title);
            printf("Data Release: %s\n", acervo[id].dataRelease);
            printf("Windows: %s\n", acervo[id].win);
            printf("Mac: %s\n", acervo[id].mac);
            printf("Linux: %s\n", acervo[id].linux);
            printf("Rating: %s\n", acervo[id].rating);
            printf("Ratio: %d\n", acervo[id].positiveRatio);
            printf("Users Review: %d\n", acervo[id].userReviews);
            printf("Final Price : %.2f\n", acervo[id].priceFinal);
            printf("Original Price: %.2f\n", acervo[id].priceOriginal);
            printf("Discount: %.2f\n", acervo[id].discount);
            printf("Steam Deck: %s\n", acervo[id].steamDeck);

        } while (id != -1);
    
    }else{
        int cont = 0;
        printf("Entre com o ID do App: ");
        scanf("%d", &idDoAPP);

        while (cont < CSVSIZE){
            
            if (acervo[i].appId == idDoAPP){
                printf("\nApp Id: %d\n", acervo[cont].appId);
                printf("Title: %s\n", acervo[cont].title);
                printf("Data Release: %s\n", acervo[cont].dataRelease);
                printf("Windows: %s\n", acervo[cont].win);
                printf("Mac: %s\n", acervo[cont].mac);
                printf("Linux: %s\n", acervo[cont].linux);
                printf("Rating: %s\n", acervo[cont].rating);
                printf("Ratio: %d\n", acervo[cont].positiveRatio);
                printf("Users Review: %d\n", acervo[cont].userReviews);
                printf("Final Price : %.2f\n", acervo[cont].priceFinal);
                printf("Original Price: %.2f\n", acervo[cont].priceOriginal);
                printf("Discount: %.2f\n", acervo[cont].discount);
                printf("Steam Deck: %s\n", acervo[cont].steamDeck);
                break;
            }
            

            cont++;

        }

        if(cont >= CSVSIZE) {
            printf("O aplicativo não foi encontrado com o ID %d que foi informado.\n", idDoAPP);
            exit(1);
        }
            
    }

    for (int j = 0; j < CSVSIZE; j++) {
        free(acervo[j].title);
        free(acervo[j].dataRelease);
        free(acervo[j].win);
        free(acervo[j].mac);
        free(acervo[j].linux);
        free(acervo[j].rating);
        free(acervo[j].steamDeck);
    }

    free(acervo);

    int err = fclose(fp);
    
    if (err){
        printf("Arquivo incorretamente fechado!!\n");
    }

    return 0;
}