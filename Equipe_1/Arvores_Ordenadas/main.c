#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define N 20

int main(void)
{
    Games *jogos;
    int tam = 0;
    jogos = carregaDados("../../Data/Grupo1DataSet.csv", &tam);

    Games *sub_jogo = IniciaLista(N);

    int aux;
    for (int i = 0; i < N; i++)
    {
        aux = rand() % tam;
        cpyGame(jogos[aux], &(sub_jogo[i]));
    }

    printf("------------Lista------------\n");

    for (int j = 0; j < N; j++)
    {
        primeiras_letras(sub_jogo[j].Name);
        printf(", %d)\n", sub_jogo[j].ID);
    }

    noArvBin *arv = NULL, *arvAVL = NULL;

    for (int i = 0; i < N; i++)
    {
        arv = insereNoArvBin(arv, sub_jogo[i]);
        arvAVL = insereNoArvAVL(arvAVL, sub_jogo[i]);
    }

    printf("\n\n------------Print arv tipo = 0------------\n");
    printf("\nArvore Binaria:\n\n");
    printArv(arv, 0);
    printf("\nArvore AVL:\n\n");
    printArv(arvAVL, 0);

    printf("\n\n------------Print arv tipo = 1------------\n");
    printf("\nArvore Binaria:\n\n");
    printArv(arv, 1);
    printf("\nArvore AVL:\n\n");
    printArv(arvAVL, 1);

    printf("\n\n------------Print arv tipo = 2------------\n");
    printf("\nArvore Binaria:\n\n");
    printArv(arv, 2);
    printf("\nArvore AVL:\n\n");
    printArv(arvAVL, 2);

    printf("\n\n------------Print arv tipo = 3-----------\n");
    printf("\nArvore Binaria:\n\n");
    printArv(arv, 3);
    printf("\nArvore AVL:\n\n");
    printArv(arvAVL, 3);

    printf("\n\n------------Busca da Arvore Binaria-----------\n");

    for (int i = 0; i < 5; i++)
    {
        aux = rand() % tam;
        noArvBin *no = buscaNaArv(arv, jogos[aux].ID);

        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore", jogos[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore na altura: %d", jogos[aux].ID, no->altura);
        }
    }

    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        aux = rand() % N;
        noArvBin *no = buscaNaArv(arv, sub_jogo[aux].ID);

        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore", sub_jogo[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore na altura: %d", sub_jogo[aux].ID, no->altura);
        }
    }

    printf("\n\n------------Busca da Arvore AVL-----------\n");

    for (int i = 0; i < 5; i++)
    {
        aux = rand() % tam;
        noArvBin *no = buscaNaArv(arvAVL, jogos[aux].ID);

        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore", jogos[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore na altura: %d", jogos[aux].ID, no->altura);
        }
    }

    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        aux = rand() % N;
        noArvBin *no = buscaNaArv(arvAVL, sub_jogo[aux].ID);

        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore", sub_jogo[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore na altura: %d", sub_jogo[aux].ID, no->altura);
        }
    }

    printf("\n\n------------Removendo da Arvore Binaria-----------\n\n");

    for (int i = 0; i < 2; i++)
    {

        aux = rand() % N;

        printf("\n---Tentando remover o ID: %d\n\n", sub_jogo[aux].ID);

        noArvBin *no = buscaNaArv(arv, sub_jogo[aux].ID);
        printArv(arv, 1);

        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore\n", sub_jogo[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore na altura: %d\n\n", sub_jogo[aux].ID, no->altura);
            arv = removeDaArv(arv, sub_jogo[aux].ID);
        }

        printArv(arv, 1);

        no = buscaNaArv(arv, sub_jogo[aux].ID);
        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore\n", sub_jogo[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore na altura: %d\n\n", sub_jogo[aux].ID, no->altura);
        }
    }

    printf("\n\n------------Removendo da Arvore AVL-----------\n\n");

    for (int i = 0; i < 2; i++)
    {

        aux = rand() % N;

        printf("\n---Tentando remover o ID: %d\n\n", sub_jogo[aux].ID);

        noArvBin *no = buscaNaArv(arvAVL, sub_jogo[aux].ID);
        printArv(arvAVL, 1);

        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore AVL\n", sub_jogo[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore AVL na altura: %d\n\n", sub_jogo[aux].ID, no->altura);
            arvAVL = removeDaArvAVL(arvAVL, sub_jogo[aux].ID);
        }

        printArv(arvAVL, 1);

        no = buscaNaArv(arvAVL, sub_jogo[aux].ID);
        if (no == NULL)
        {
            printf("\no ID: %d não esta na arvore AVL\n", sub_jogo[aux].ID);
        }
        else
        {
            printf("\no ID: %d esta na arvore AVL na altura: %d\n\n", sub_jogo[aux].ID, no->altura);
        }
    }
}
