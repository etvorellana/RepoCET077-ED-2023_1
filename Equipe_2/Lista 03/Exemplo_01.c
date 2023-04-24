#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define TRUE 1
#define FALSE 0

int main(){ 

    Jogos* acervo;
    TListaLinear *listaOrdenada, *listaDesordenada;

    int capacidade, tamanhoOrdenada, tamanhoAcervo, tentativa, conseguiuAdicionar;
    int tamanhoDesordenada, conseguiuBuscar, conseguiuRemover;

    capacidade = 100;
    tamanhoAcervo = 1000;
    tamanhoOrdenada = tamanhoDesordenada = 0;

    //Carregando dados para o acervo
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &tamanhoAcervo);

    //Criando as listas
    listaOrdenada = criaListaLinear(capacidade, 1);
    listaDesordenada = criaListaLinear(capacidade, 0);

    //Preenchimento ORDENADO
    tentativa = 0, conseguiuAdicionar = 0;  
    while(listaOrdenada->tamanho < capacidade) {
        int posicaoAleatoria = rand() % tamanhoAcervo;
        
        if ( insereNaLista(acervo[posicaoAleatoria], listaOrdenada) ) conseguiuAdicionar++;
        
        tentativa++;
    }

    //Output das tentativas e conclusões de adição ORDENADA
    printf("Foram realizadas %d tentativas de inclusão - ORDENADA\n", tentativa);
    printf("Foram incluídos %d registros na coleção - ORDENADA\n\n", conseguiuAdicionar);

    //Preenchimento NÃO ORDENADA
    tentativa = 0, conseguiuAdicionar = 0;  
    while(listaDesordenada->tamanho < capacidade) {
        int posicaoAleatoria = rand() % tamanhoAcervo;
        
        if ( insereNaLista(acervo[posicaoAleatoria], listaDesordenada) ) conseguiuAdicionar++;
        
        tentativa++;
    }

    //Output das tentativas e conclusões de adição NÃO ORDENADA
    printf("Foram realizadas %d tentativas de inclusão - NÃO ORDENADA\n", tentativa);
    printf("Foram incluídos %d registros na coleção- NÃO ORDENADA\n\n", conseguiuAdicionar);

    //Looping para busca por id - ORDENADA
    tentativa = 0, conseguiuBuscar = 0;  
    while(listaOrdenada->tamanho > conseguiuBuscar) {
        
        int posicaoAleatoria = rand()%tamanhoAcervo;
        
        if ( buscaNaLista(acervo[posicaoAleatoria].appId, listaOrdenada) >= 0 ) conseguiuBuscar++;
        tentativa++;

    }

    //Output das tentativas e conclusões de busca - ORDENADA
    printf("Foram realizadas %d tentativas de busca - ORDENADA\n", tentativa);
    printf("Foram achados %d registros na coleção - ORDENADA\n\n", conseguiuBuscar);

    //Looping para busca por id - NÃO ORDENADA
    tentativa = 0, conseguiuBuscar = 0;  
    while(listaDesordenada->tamanho > conseguiuBuscar) {
        
        int posicaoAleatoria = rand()%tamanhoAcervo;
        int auxiliar = buscaNaLista(acervo[posicaoAleatoria].appId, listaDesordenada);
        
        if ( auxiliar < listaDesordenada->tamanho) conseguiuBuscar++;
        tentativa++;

    }

    //Output das tentativas e conclusões de busca - NÃO ORDENADA
    printf("Foram realizadas %d tentativas de busca - NÃO ORDENADA\n", tentativa);
    printf("Foram achados %d registros na coleção - NÃO ORDENADA\n\n", conseguiuBuscar);

    //Looping para remoção por id ORDENADA
    tentativa = 0, conseguiuRemover = 0;  
    while(listaOrdenada->tamanho > 0) { 
        int posicaoAleatoria = rand()%tamanhoAcervo;
        
        if ( removeDaLista(acervo[posicaoAleatoria].appId, listaOrdenada) ) conseguiuRemover++;
        tentativa++;
    }

    //Output das tentativas e conclusões de remoção ORDENADA
    printf("Foram realizadas %d tentativas de remoção - ORDENADA\n", tentativa);
    printf("Foram removidos %d registros na coleção - ORDENADA\n\n", conseguiuRemover);

    //Looping para remoção por id NÃO ORDENADA
    tentativa = 0, conseguiuRemover = 0;  
    while(listaDesordenada->tamanho > 0) { 
        int posicaoAleatoria = rand()%tamanhoAcervo;
        
        if ( removeDaLista(acervo[posicaoAleatoria].appId, listaDesordenada) ) conseguiuRemover++;
        tentativa++;
    }

    //Output das tentativas e conclusões de remoção NÃO ORDENADA
    printf("Foram realizadas %d tentativas de remoção - NÃO ORDENADA\n", tentativa);
    printf("Foram removidos %d registros na coleção - NÃO ORDENADA\n\n", conseguiuRemover);

}