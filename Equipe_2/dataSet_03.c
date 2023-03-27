#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define CSVSIZE 46068

int main() {
    
    //Declaração das estruturas
    Jogos *acervo;
    Jogos *subColecao;

    //Declaração das Variáveis
    int tamanhoAcervo = CSVSIZE;
    int tamanhoColecao = 0;
    int capacidadeColecao = (CSVSIZE / 3);
    int tentativa, conseguiuAdicionar, conseguiuRemover, conseguiuBuscar;  
    
    //Carrega os dados do acervo
    acervo = carregaDados("../../../Data/dataSetEquipe2.csv", &tamanhoAcervo);
    
    //Aloca espaço para a subColecao
    subColecao = criaAcervo( capacidadeColecao + 1 );
    
    //Looping para preenchimento da subColecao
    tentativa = 0, conseguiuAdicionar = 0;  
    while(tamanhoColecao < capacidadeColecao) { // enquanto não estiver cheia
        int posicaoAleatoria = rand() % tamanhoAcervo; //Gera posição aleatória no Acervo
        
        if ( incRegistro(acervo[posicaoAleatoria], subColecao, &tamanhoColecao )) conseguiuAdicionar++;
        tentativa++;
    }

    //Output das tentativas e conclusões de adição
    printf("\nForam realizadas %d tentativas de inclusão\n", tentativa);
    printf("Foram incluídos %d registros na coleção\n\n", conseguiuAdicionar);
    
    //Looping para busca por id
    tentativa = 0, conseguiuBuscar = 0;  
    while(tamanhoColecao > conseguiuBuscar) {
        
        int posicaoAleatoria = rand()%tamanhoAcervo; //Gera posição aleatória no Acervo
        
        subColecao[tamanhoColecao].appId = acervo[posicaoAleatoria].appId;
        if ( buscaPorId(acervo[posicaoAleatoria].appId, subColecao, tamanhoColecao) < tamanhoColecao ) conseguiuBuscar++;
        tentativa++;

    }

    //Output das tentativas e conclusões de busca
    printf("Foram realizadas %d tentativas de busca\n", tentativa);
    printf("Foram achados %d registros na coleção\n\n", conseguiuBuscar);

    //Looping para remoção por id
    tentativa = 0, conseguiuRemover = 0;  
    while(tamanhoColecao > 0) { // enquanto não estiver vazia
        int posicaoAleatoria = rand()%tamanhoAcervo; //Gera posição aleatória no Acervo
        
        if ( remRegistro(acervo[posicaoAleatoria].appId, subColecao, &tamanhoColecao) ) conseguiuRemover++;
        tentativa++;
    }

    //Output das tentativas e conclusões de remoção
    printf("Foram realizadas %d tentativas de remoção\n", tentativa);
    printf("Foram removidos %d registros na coleção\n\n", conseguiuRemover);

    limpaAcervo(subColecao, tamanhoColecao);
    limpaAcervo(acervo, tamanhoAcervo);

    return 0;
}

Jogos *criaAcervo( int capacidade ) {

    Jogos *acervo;

    acervo = (Jogos*) malloc(capacidade * sizeof(Jogos));

    return acervo;
}

Jogos *carregaDados(char *fileName, int *tam) {

    int i;
    char sep[1];
    sep[0] = ',';
    char str[900];
    Jogos *acervo;
    FILE *fp = fopen("../../Data/dataSetEquipe2.csv", "r");
    acervo = criaAcervo(*tam);

    if (fp == NULL) // Conseguiu abrir?
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
        exit(1);
    }

    i = 0;

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
            acervo[i].title = (char *) malloc( strlen(campo) + 1 );
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
            //campo = strtok(NULL, sep);
            //acervo[i].steamDeck = (char *) malloc(strlen(campo) + 1);
            //strcpy(acervo[i].steamDeck, campo);

            i++;
        }
    }

    return acervo;
}

void imprimeOsDados(Jogos *lista, int i) { // Esta função imprime os atributos da estrutura de acordo com o índice fornecido.

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

int buscaPorId(int idDoApp, Jogos *lista, int tam) {

    int cont = 0;

    while (cont < tam)
    {

        if (lista[cont].appId == idDoApp)
        {
            return cont;
        }

        cont++;
    }

    if (cont >= tam) // Retorno para caso o jogo não tenha sido encontrado.
    {
        return tam;
    }
}

void limpaAcervo(Jogos *acervo, int tam) {

    for (int j = 0; j < tam; j++) {
        free(acervo[j].title);
        free(acervo[j].dataRelease);
        free(acervo[j].win);
        free(acervo[j].mac);
        free(acervo[j].linux);
        free(acervo[j].rating);
        //free(acervo[j].steamDeck);
    }
    
    free(acervo);
}

int verificaExistencia( Jogos* subColecao, int idDoApp, int tam ) { //Verifica existência de um elemento, retorna 1 se houver, senão 0.

    int cont = 0;

    while (cont <= tam) {

        if (subColecao[cont].appId == idDoApp) return 1;

        cont++;
    }

    if (cont >= tam) return 0;

}

int incRegistro(Jogos origem, Jogos* destino, int* tam) { //Função que realiza "cópia" dos atributos de Origem para Destino

    if( !verificaExistencia( destino, origem.appId, *tam ) ) { 
        
        destino[*tam].appId = origem.appId;

        //strcpy(destino[*tam].title, origem.title); Identificamos que destino.title pode nao ser string
        destino[*tam].title = origem.title;
        
        //strcpy(destino[*tam].dataRelease, origem.dataRelease);
        destino[*tam].dataRelease =  origem.dataRelease;
        
        //strcpy(destino[*tam].win, origem.win);
        destino[*tam].win = origem.win;

        //strcpy(destino[*tam].mac, origem.mac);
        destino[*tam].mac = origem.mac;

        //strcpy(destino[*tam].linux, origem.linux);
        destino[*tam].linux = origem.linux;

        //strcpy(destino[*tam].rating, origem.rating);
        destino[*tam].rating = origem.rating;

        destino[*tam].positiveRatio = origem.positiveRatio;
        destino[*tam].userReviews = origem.userReviews;
        destino[*tam].priceFinal = origem.priceFinal;
        destino[*tam].priceOriginal = origem.priceOriginal;
        destino[*tam].discount = origem.discount;

        //strcpy(destino[*tam].steamDeck, origem.steamDeck);
        destino[*tam].steamDeck = origem.steamDeck;

        (*tam)++;
    
        return 1;

    }else {

        return 0;
    }

}

int remRegistro( int idDoApp, Jogos* lista, int* tam ) {

    int posicao;
    if( verificaExistencia( lista, idDoApp, *tam ) ) {

        posicao = buscaPorId( idDoApp, lista, *tam );
        
        free(lista[posicao].title);
        free(lista[posicao].dataRelease);
        free(lista[posicao].win);
        free(lista[posicao].mac);
        free(lista[posicao].linux);
        free(lista[posicao].rating);
        free(lista[posicao].steamDeck);

        *tam -=1;

        return 1;
    }

    return 0;
}