#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int chave;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

// Protótipos das funções
int max(int a, int b);
int altura(No* no);
int calcularBalanceamento(No* no);
No* criarNo(int chave);
No* rotacaoDireita(No* y);
No* rotacaoEsquerda(No* x);
No* inserirNo(No* no, int chave);
No* encontrarNoMinimo(No* no);
No* removerNo(No* raiz, int chave);
No* buscarNo(No* raiz, int chave);
void percursoEmOrdem(No* raiz);
void percursoPreOrdem(No* raiz);
void percursoPosOrdem(No* raiz);

int main()
{
    No* raiz = NULL;

    // Exemplo de inserção de nós na árvore AVL
    raiz = inserirNo(raiz, 50);
    raiz = inserirNo(raiz, 30);
    raiz = inserirNo(raiz, 20);
    raiz = inserirNo(raiz, 40);
    raiz = inserirNo(raiz, 70);
    raiz = inserirNo(raiz, 60);
    raiz = inserirNo(raiz, 80);

    // Exemplo de remoção de um nó na árvore
    No* resultadoBusca = buscarNo(raiz, 40);
    if(resultadoBusca != NULL) {
        printf("No encontrado: %d\n", resultadoBusca->chave);
    } else {
        printf("No nao encontrado.\n");
    }

    // Exemplo de remoção de um nó na árvore
    raiz = removerNo(raiz, 40);
    resultadoBusca = buscarNo(raiz, 40);
    if(resultadoBusca != NULL) {
        printf("No encontrado: %d\n", resultadoBusca->chave);
    } else {
        printf("No nao encontrado.\n");
    }

    // Exemplo de percurso em ordem
    printf("Percurso em ordem: ");
    percursoEmOrdem(raiz);
    printf("\n");

    // Exemplo de percurso em pré-ordem
    printf("Percurso em pre-ordem: ");
    percursoPreOrdem(raiz);
    printf("\n");

    // Exemplo de percurso em pós-ordem
    printf("Percurso em pos-ordem: ");
    percursoPosOrdem(raiz);
    printf("\n");

    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(No* no) {
    if(no == NULL) {
        return 0;
    }
    return no->altura;
}

int calcularBalanceamento(No* no) {
    if(no == NULL) {
        return 0;
    }
    return altura(no->esquerda) - altura(no->direita);
}

No* criarNo(int chave) {
    No* novoNo = (No*) malloc(sizeof(No));

    novoNo->chave = chave;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 0;

    return novoNo;
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

No* inserirNo(No* no, int chave)
{
    if(no == NULL)
    {
        return criarNo(chave);
    }

    if(chave < no->chave) {
        no->esquerda = inserirNo(no->esquerda, chave);
    } else if(chave > no->chave) {
        no->direita = inserirNo(no->direita, chave);
    } else {
        return no; // Não permitir chaves duplicadas
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;

    int balanceamento = calcularBalanceamento(no);

    // Caso de rotação esquerda-esquerda
    if(balanceamento > 1 && chave < no->esquerda->chave) {
        return rotacaoDireita(no);
    }

    // Caso de rotação direita-direita
    if(balanceamento < -1 && chave > no->direita->chave) {
        return rotacaoEsquerda(no);
    }

    // Caso de rotação esquerda-direita
    if(balanceamento > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso de rotação direita-esquerda
    if(balanceamento < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

No* encontrarNoMinimo(No *no) {
    No* atual = no;
    while(atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

No* removerNo(No* raiz, int chave) {
    if(raiz == NULL) {
        return raiz;
    }

    if(chave < raiz->chave) {
        raiz->esquerda = removerNo(raiz->esquerda, chave);
    } else if(chave > raiz->chave) {
        raiz->direita = removerNo(raiz->direita, chave);
    } else {
        if(raiz->esquerda == NULL || raiz->direita == NULL) {
            No* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if(temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            No* temp = encontrarNoMinimo(raiz->direita);
            raiz->chave = temp->chave;
            raiz->direita = removerNo(raiz->direita, temp->chave);
        }

        if(raiz == NULL) {
            return raiz;
        }

        raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

        int balanceamento = calcularBalanceamento(raiz);

        // Caso de rotação esquerda-esquerda
        if(balanceamento > 1 && calcularBalanceamento(raiz->esquerda) >= 0)
            return rotacaoDireita(raiz);

        // Caso de rotação direita-direita
        if(balanceamento < -1 && calcularBalanceamento(raiz->direita) <= 0)
            return rotacaoEsquerda(raiz);

        // Caso de rotação esquerda-direita
        if(balanceamento > 1 && calcularBalanceamento(raiz->esquerda) < 0) {
            raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
            return rotacaoDireita(raiz);
        }

        // Caso de rotação direita-esquerda
        if(balanceamento < -1 && calcularBalanceamento(raiz->direita) > 0) {
            raiz->direita = rotacaoDireita(raiz->direita);
            return rotacaoEsquerda(raiz);
        }
    }

    return raiz;
}

No* buscarNo(No* raiz, int chave) {
    if(raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    if(chave < raiz->chave) {
        return buscarNo(raiz->esquerda, chave);
    }

    return buscarNo(raiz->direita, chave);
}

void percursoEmOrdem(No* raiz) {
    if(raiz != NULL) {
        percursoEmOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        percursoEmOrdem(raiz->direita);
    }
}

void percursoPreOrdem(No* raiz) {
    if(raiz != NULL) {
        printf("%d ", raiz->chave);
        percursoPreOrdem(raiz->esquerda);
        percursoPreOrdem(raiz->direita);
    }
}

void percursoPosOrdem(No* raiz) {
    if(raiz != NULL) {
        percursoPosOrdem(raiz->esquerda);
        percursoPosOrdem(raiz->direita);
        printf("%d ", raiz->chave);
    }
}
