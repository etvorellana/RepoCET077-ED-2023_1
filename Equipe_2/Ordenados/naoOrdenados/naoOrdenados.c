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
    int tamanhoAcervo = 10000;
    int tamanhoColecao = 0;
    int capacidadeColecao = 5000;
    int tentativa, conseguiuAdicionar, conseguiuRemover, conseguiuBuscar;  
    
    //Carrega os dados do acervo
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &tamanhoAcervo);
    
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