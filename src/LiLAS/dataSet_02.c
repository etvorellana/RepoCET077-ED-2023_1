#include <stdio.h>  // <- printf(), fopen(), fclose(), ...
#include <stdlib.h> // <- exit()
#include <string.h> // <- strcpy()

#include "bidefun.h"

int main(void)
{
    
    //Carregando o acervo do dataset  
    TBook *acervo;
    int id, tam;
    acervo = carregaDados("../../../Data/books.csv", &tam);

    
    // Criando uma sub lista do acervo
    TBook *colecao;
    int colTam = 0; // tamanho da coleção
    int colCap = (CSVSIZE / 3); // capacidade 
    /* 
        Tarefa para a aula de 27/03/2023 
        É possível transferir a inicialização da lista para uma 
        função;
        TBook* criaAcervo(int capacidade);
    */
    //alocando espaço para o array
    colecao = (TBook*) malloc((colCap+1)*sizeof(TBook));
    //                  posição extra ^

    /* 
        Tarefa para a aula de 27/03/2023 
        Teste de inclusão: Preencher a coleção com 
        registro do acervo. Neste exemplo estou monitorando
        quantas tentativas de inclusão foram feitas e quantas
        foram bem sucedidas.
    */
    int try = 0, ok = 0;  
    while(colTam < colCap) // enquanto não estiver cheia
    {
        //gera um índice aleatória do acervo
        int idx = rand()%tam;
        try++;
        if (incRegistro(acervo[idx], colecao, &colTam))
            ok++;
    }

    printf("Foram realizadas %d tentativas de inclusão\n", try);
    printf("Foram incluídos %d registros na coleção\n", ok);
    
    /* 
        Tarefa para a aula de 27/03/2023 
        Teste de busca: procurar por registros da coleção 
        utilizando os isbn dos registros do acervo. Neste exemplo 
        estou monitorando quantas buscas foram feitas 
        e quantas foram bem sucedidas.
    */
    try = 0, ok = 0;  
    while(colTam > ok) 
    {
        //gera um índice aleatória do acervo
        int idx = rand()%tam;
        try++;
        colecao[colTam].isbn = acervo[idx].isbn;
        if (buscaPorISBN(acervo[idx].isbn, colecao, colTam) < colTam)
            ok++;
    }

    printf("Foram realizadas %d tentativas de busca\n", try);
    printf("Foram achados %d registros na coleção\n", ok);

    /* 
        Tarefa para a aula de 27/03/2023 
        Teste de remoção: Remover todos os registros da coleção 
        utilizando os isbn dos registros do acervo. Neste exemplo 
        estou monitorando quantas tentativas de remoção foram feitas 
        e quantas foram bem sucedidas.
    */
    try = 0, ok = 0;  
    while(colTam > 0) // enquanto não estiver vazia
    {
        //gera um índice aleatória do acervo
        int idx = rand()%tam;
        try++;
        if (remRegistro(acervo[idx].isbn, colecao, &colTam))
            ok++;
    }

    printf("Foram realizadas %d tentativas de remoção\n", try);
    printf("Foram removidos %d registros na coleção\n", ok);

    limpaAcervo(colecao, colTam);
    limpaAcervo(acervo, tam);
    return 0;
}




/*
    Como compilar
    * Primeiro compile as partes por separado   
    $> gcc -O2 -o bidefun.o -c bidefun.c
        ^   ^   ^     ^      ^     ^
    $> gcc -O2 -o dataSet_01.o -c dataSet_01.c  
    * Depois juntar tudo
    $> gcc -O2 -o exem_01 bidefun.o dataSet_01.o
        ^    ^  ^    ^       ^         ^
*/