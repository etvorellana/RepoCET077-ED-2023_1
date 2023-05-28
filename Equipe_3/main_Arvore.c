#include <stdio.h>
#include <stdlib.h>

// Defini��o de um n� da �rvore
typedef struct No {
    int chave;
    struct No* esquerda;
    struct No* direita;
} No;

//PROTOTIPOS
No* criarNo(int chave);
No* inserirNo(No* raiz, int chave);
No* encontrarMinimo(No* raiz);
No* removerNo(No* raiz, int chave);
void imprimirArvore(No* raiz);


int main() {
    No* raiz = NULL;

    // Inserindo n�s na �rvore
    raiz = inserirNo(raiz, 50);
    raiz = inserirNo(raiz, 30);
    raiz = inserirNo(raiz, 20);
    raiz = inserirNo(raiz, 40);
    raiz = inserirNo(raiz, 70);
    raiz = inserirNo(raiz, 60);
    raiz = inserirNo(raiz, 80);

    printf("Arvore original: ");
    imprimirArvore(raiz);
    printf("\n");

    int chaveRemover;
    printf("Digite a chave do no a ser removido: ");
    scanf("%d", &chaveRemover);

    raiz = removerNo(raiz, chaveRemover);

    printf("Arvore apos a remocao: ");
    imprimirArvore(raiz);
    printf("\n");

    return 0;
}


//fun��es

// Fun��o para criar um novo n� da �rvore
No* criarNo(int chave) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Fun��o para inserir um n� na �rvore
No* inserirNo(No* raiz, int chave) {
    if (raiz == NULL) {
        return criarNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserirNo(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = inserirNo(raiz->direita, chave);
    }

    return raiz;
}

// Fun��o para encontrar o n� com a chave m�nima na �rvore
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Fun��o para remover um n� da �rvore
No* removerNo(No* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = removerNo(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = removerNo(raiz->direita, chave);
    } else {
        // O n� a ser removido foi encontrado

        // Caso 1: N� folha
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            raiz = NULL;
        }
        // Caso 2: N� com apenas um filho
        else if (raiz->esquerda == NULL) {
            No* temp = raiz;
            raiz = raiz->direita;
            free(temp);
        } else if (raiz->direita == NULL) {
            No* temp = raiz;
            raiz = raiz->esquerda;
            free(temp);
        }
        // Caso 3: N� com dois filhos
        else {
            No* temp = encontrarMinimo(raiz->direita);
            raiz->chave = temp->chave;
            raiz->direita = removerNo(raiz->direita, temp->chave);
        }
    }

    return raiz;
}

// Fun��o para imprimir a �rvore em ordem (inorder)
void imprimirArvore(No* raiz) {
    if (raiz != NULL) {
        imprimirArvore(raiz->esquerda);
        printf("%d ", raiz->chave);
        imprimirArvore(raiz->direita);
    }
}
