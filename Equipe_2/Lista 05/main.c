#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() {
    Jogos *acervo;
    Pilha *pilha;
    Fila *fila;
    Encadeado *listaEncadeada;
    srand( (unsigned)time(NULL) );

    int capacidade, tamanhoAcervo, tentativa, conseguiuAdicionar;

    capacidade = 100;
    tamanhoAcervo = 1000;

    //Carregando dados para o acervo
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &tamanhoAcervo);

    //Inicializando as estruturas.
    listaEncadeada = inicializaListaEncadeada();
    pilha = inicializaPilha();
    fila = inicializaFila();

    //Adição Lista Encadeada
    conseguiuAdicionar = tentativa = 0;
    while (conseguiuAdicionar < 100) {
        int posicaoAleatoria = rand() % tamanhoAcervo;

       if( insereEncadeado(&acervo[posicaoAleatoria], listaEncadeada) ) conseguiuAdicionar++;

    }

    //Saída - LISTA ENCADEADA
    printf("\nLISTA ENCADEADA:\n");
    printf("Primeiro elemento: ");
    imprimeElementoListaEncadeada(listaEncadeada);
    printf("\n");
    printf("Último elemento: ");
    imprimeUltimoElementoListaEncadeada(listaEncadeada);
    printf("\n");

    // ADICIONANDO NA PILHA
    conseguiuAdicionar = tentativa = 0;
    while (!isPilhaCheia(pilha) && listaEncadeada->topo != NULL) {
        
        if (empilhar( removeEncadeado( listaEncadeada ), pilha ))
        {
            conseguiuAdicionar++;
        }

        tentativa++;
    }

    //Saída - PILHA
    printf("PILHA:\n");
    printf("Primeiro elemento: ");
    imprimeElementoPilha(pilha);

    //Removendo da pilha e inserindo na Fila.
    conseguiuAdicionar = tentativa = 0;
    while( !isPilhaVazia(pilha) ) {

        if( insereNaFila( desempilha(pilha), fila ) ) conseguiuAdicionar++;

        tentativa++;

    }

    //Removendo da Fila e inserindo na Lista
    conseguiuAdicionar = tentativa = 0;
    listaEncadeada = inicializaListaEncadeada();
    while( listaEncadeada->tam < 100 ) {

        if( insereEncadeado( removeDaFila(fila), listaEncadeada ) ) conseguiuAdicionar++;

        tentativa++;

    }
    printf("\n\nLISTA ENCADEADA: \n");
    printf("Primeiro elemento: ");
    imprimeElementoListaEncadeada( listaEncadeada );
    printf("\n");
    printf("Último elemento: ");
    imprimeUltimoElementoListaEncadeada( listaEncadeada );
    printf("\n");

    return 0;
}