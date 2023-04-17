#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define TRUE 1
#define FALSE 0

int main(){ 

    Jogos* acervo;
    TPilhaLinear* PilhaLinear;
    TFilaLinear* FilaLinear;

    int capacidade, tamanhoAcervo, tentativa, conseguiuAdicionar, conseguiuRemover;

    capacidade = 100;
    tamanhoAcervo = 1000;

    //Carregando dados para o acervo
    acervo = carregaDados("../../Data/dataSetEquipe2.csv", &tamanhoAcervo);

    //Criando a Pilha
    PilhaLinear = criaPilhaLinear( capacidade );

    //Criando a Fila
    FilaLinear = criaFilaLinear( capacidade );

    //Preenchimento NA PILHA
    tentativa = 0, conseguiuAdicionar = 0;  
    while(!isPilhaCheia(PilhaLinear)) {
        
        int posicaoAleatoria = rand() % tamanhoAcervo;
        
        if ( insereNaPilha( acervo[posicaoAleatoria], PilhaLinear) ) conseguiuAdicionar++;
        tentativa++;
    }

    //Output das tentativas e conclusões de adição NA PILHA
    printf("Foram realizadas %d tentativas de inclusão - NA PILHA\n", tentativa);
    printf("Foram incluídos %d registros na coleção - NA PILHA\n\n", conseguiuAdicionar);

    //Looping para remoção NA PILHA
    tentativa = 0, conseguiuRemover = 0;  
    while( !isPilhaVazia(PilhaLinear) ) { 
        
        if ( removeDaPilha( PilhaLinear ) != NULL ) conseguiuRemover++;
        tentativa++;
    }

    //Output das tentativas e conclusões de remoção NA PILHA
    printf("Foram realizadas %d tentativas de remoção - NA PILHA\n", tentativa);
    printf("Foram removidos %d registros na coleção - NA PILHA\n\n", conseguiuRemover);

    //Preenchimento NA FILA
    tentativa = 0, conseguiuAdicionar = 0;  
    while(!isFilaCheia(FilaLinear)) {
        
        int posicaoAleatoria = rand() % tamanhoAcervo;
        
        if ( insereNaFila( acervo[posicaoAleatoria], FilaLinear) ) conseguiuAdicionar++;
        tentativa++;
    }

    //Output das tentativas e conclusões de adição NA FILA
    printf("Foram realizadas %d tentativas de inclusão - NA FILA\n", tentativa);
    printf("Foram incluídos %d registros na coleção - NA FILA\n\n", conseguiuAdicionar);

    //Looping para remoção NA FILA
    tentativa = 0, conseguiuRemover = 0;  
    while( !isFilaVazia(FilaLinear) ) { 
        
        if ( removeDaFila( FilaLinear ) ) conseguiuRemover++;
        
        tentativa++;
    }

    //Output das tentativas e conclusões de remoção NA FILA
    printf("Foram realizadas %d tentativas de remoção - NA FILA\n", tentativa);
    printf("Foram removidos %d registros na coleção - NA FILA\n\n", conseguiuRemover);

}