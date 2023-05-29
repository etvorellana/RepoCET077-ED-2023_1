#include <stdio.h>
#include <stdlib.h>

// Definição de um nó da árvore
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

    // Inserindo nós na árvore
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


//funções

// Função para criar um novo nó da árvore
No* criarNo(int chave) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore
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

// Função para encontrar o nó com a chave mínima na árvore
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função para remover um nó da árvore
No* removerNo(No* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = removerNo(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = removerNo(raiz->direita, chave);
    } else {
        // O nó a ser removido foi encontrado

        // Caso 1: Nó folha
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            raiz = NULL;
        }
        // Caso 2: Nó com apenas um filho
        else if (raiz->esquerda == NULL) {
            No* temp = raiz;
            raiz = raiz->direita;
            free(temp);
        } else if (raiz->direita == NULL) {
            No* temp = raiz;
            raiz = raiz->esquerda;
            free(temp);
        }
        // Caso 3: Nó com dois filhos
        else {
            No* temp = encontrarMinimo(raiz->direita);
            raiz->chave = temp->chave;
            raiz->direita = removerNo(raiz->direita, temp->chave);
        }
    }

    return raiz;
}

// Função para imprimir a árvore em ordem (inorder)
void imprimirArvore(No* raiz) {
    if (raiz != NULL) {
        imprimirArvore(raiz->esquerda);
        printf("%d ", raiz->chave);
        imprimirArvore(raiz->direita);
    }
}
