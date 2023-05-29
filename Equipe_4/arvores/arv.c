#include <stdio.h>
#include <stdlib.h>

#include "bidefun.h"

int main(void)
{
    Tinfo lista;
    NoArv *raiz = NULL;
    NoArv *busca = NULL;
    int opcao;
    int tipo;
    int key;

    do
    {
        printf("\n\t0 - sair\n\t1 - inserir\n\t2 - imprimir\n\t3 - buscar\n\t");
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            printf("Digite um valor\n");
            scanf("%f", &lista.value);
            lista.key = rand() % 100;
            raiz = inserir(raiz, lista, 0);
            break;
        case 2:
        printf("Digite o tipo(1 a 4) da impressao: ");
        scanf("%d", &tipo);
        printf("Impressao\n-----------------------------------------------\n");
            imprimir(raiz, tipo);
            break;
        case 3:
            printf("Digite a key do elemento que procura: ");
            scanf("%d", &key);
            busca = buscaRec(raiz, key);
            if (busca)
                printf("Valor encontrado: %d - %.2f\n", busca -> info.key, busca -> info.value);
            else 
                printf("Valor nao encontrado!\n");
            break;
        default:
            if (opcao != 0)
                printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);
    
    return 0;
}