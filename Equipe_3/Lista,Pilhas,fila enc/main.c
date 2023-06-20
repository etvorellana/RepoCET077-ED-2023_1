#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <stdbool.h>

#include"datafun.h"

int main() {
    int tam = CSVSIZE;
    srand(time(NULL));
    t_Fipe *fipe = carregaDados("datasetFipe.csv", &tam);

    // Criação da lista encadeada
    PNoFipeSE listaHead = NULL;
    for(int i = 0; i < 100; i++) {
        PNoFipeSE novoNo = (PNoFipeSE) malloc(sizeof(t_NoFipeSE));
        novoNo->fipe = fipe[rand() % tam];
        novoNo->prox = listaHead;
        listaHead = novoNo;
    }
    printf("Primeiro item da lista:\n");
    printRegistro(listaHead->fipe);
    PNoFipeSE listaTail = listaHead;
    while(listaTail->prox != NULL) {
        listaTail = listaTail->prox;
    }
    printf("\nUltimo item da lista:\n");
    printRegistro(listaTail->fipe);

    // Criação da pilha encadeada
    printf("\n------PILHA------\n");

    PilhaEnc *pilha = criaPilhaEnc();
    //PNoFipeSE p = listaHead;
    while(listaHead != NULL) {
        empilha(listaHead->fipe, pilha);
        listaHead = listaHead->prox;
    }
    //imprimePilha(pilha);  //teste para checar se a pilha esta sendo devidamente preenchida

    //////////////////////////////////////////////////////////////////
    // Remoção da pilha e adição na fila
    printf("\n------FILA------\n");

    FilaEnc *fila = criaFila();
    while(!pilhaVazia(pilha)) {
        t_Fipe f = desempilha(pilha);
        enfileira(f, fila);
    }
    //imprimeFila(fila);  //teste para checar se a fila esta sendo devidamente preenchida

    //////////////////////////////////////////////////////////////////
    // Remoção da fila e adição na lista
    listaHead = NULL;
    listaTail = NULL;
    while(!filaVazia(fila)) {
        t_Fipe f = desemfileira(fila);
        PNoFipeSE novoNo = (PNoFipeSE) malloc(sizeof(t_NoFipeSE));
        novoNo->fipe = f;
        novoNo->prox = NULL;
        if(listaHead == NULL) {
            listaHead = novoNo;
            listaTail = novoNo;
        } else {
            listaTail->prox = novoNo;
            listaTail = novoNo;
        }
    }

    //imprimeLista(listaHead);  //teste para saber se os elementos foram colocados de volta na lista

    // Imprime novamente primeiro e o último item da lista encadeada
    printf("Primeiro item da lista:\n");
    printRegistro(listaHead->fipe);
    printf("\n");

    PNoFipeSE ultimo = listaHead;
    while(ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }
    printf("Ultimo item da lista:\n");
    printRegistro(ultimo->fipe);
    printf("\n");

/////////////////////////////////////////////////////////////////////////////////
    free(pilha);
    free(fila);
    limpaFipe(fipe, tam); // Libera a mem�ria alocada para a lista original
    // Liberar mem�ria alocada
    PNoFipeSE atual = listaHead;
    while (atual != NULL) {
        PNoFipeSE proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    printf("\nPrograma execultado com sucesso!!!\n\n");

    return 0;
}