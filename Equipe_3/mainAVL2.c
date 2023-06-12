#include <stdio.h>
#include <stdlib.h>

#include "arvAvl.h"


typedef struct No{
    t_Fipe dados;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;



// Protótipos das funções
int max(int a, int b);
int altura(No* no);
int calcularBalanceamento(No* no);
No* criarNo(t_Fipe *chave);
No* rotacaoDireita(No* y);
No* rotacaoEsquerda(No* x);
No* inserirNo(No* no, t_Fipe *chave);
No* encontrarNoMinimo(No* no);
No* removerNo(No* raiz, int chave);
No* buscarNo(No* raiz, int chave);
void percursoEmOrdem(No* raiz);
void percursoPreOrdem(No* raiz);
void percursoPosOrdem(No* raiz);

int main()
{
     No* raiz = NULL;
    int tam = CSVSIZE;

    t_Fipe* fipe = carregaDados("datasetFipe.csv", &tam);

    // Inserindo os elementos na �rvore
    for (int i = 0; i < tam; i++) {
        raiz = inserirNo(raiz, &fipe[i]);
    }

    // Exemplo de busca de um nó na árvore
    No* resultadoBusca = buscarNo(raiz, 40);
    if(resultadoBusca != NULL) {
        printf("Nó encontrado: %d\n", resultadoBusca->dados.nCdg);
    } else {
        printf("Nó não encontrado.\n");
    }

    // Exemplo de remoção de um nó na árvore
    raiz = removerNo(raiz, 40);
    resultadoBusca = buscarNo(raiz, 40);
    if(resultadoBusca != NULL) {
        printf("Nó encontrado: %d\n", resultadoBusca->dados.nCdg);
    } else {
        printf("Nó não encontrado.\n");
    }

    // Exemplo de percurso em ordem
    printf("Percurso em ordem: ");
    percursoEmOrdem(raiz);
    printf("\n");

    // Exemplo de percurso em pré-ordem
    printf("Percurso em pré-ordem: ");
    percursoPreOrdem(raiz);
    printf("\n");

    // Exemplo de percurso em pós-ordem
    printf("Percurso em pós-ordem: ");
    percursoPosOrdem(raiz);
    printf("\n");

    return 0;

}

t_Fipe *carregaDados(char *arquivo, int *tam)
{
    t_Fipe *fipe;
    FILE *fp;

    char str[900];
    int i = 0;

    fipe = (t_Fipe *)malloc(CSVSIZE * sizeof(t_Fipe));

    if (fipe == NULL) {
        printf("ERRO! Falha ao alocar memoria!\n");
        exit(1);
    }

    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("ERRO! Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    char *ok;
    ok = fgets(str, 900, fp);
    if (ok == NULL) {
        printf("Erro lendo o cabecalho do CSV!!!\n");
        exit(1);
    }

    i = 0;
    char sep[] = ",";

    while (!feof(fp) && i < CSVSIZE) {
        ok = fgets(str, 900, fp);
        if (ok) {
            char *campo;
            campo = strtok(str, sep);
            fipe[i].nCdg = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].codigofp = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].marca = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].modelo = strdup(campo);
            campo = strtok(NULL, sep);
            fipe[i].anoModelo = atoi(campo);
            campo = strtok(NULL, sep);
            fipe[i].mesReferencia = atoi(campo);
            campo = strtok(NULL, sep);
            fipe[i].anoReferencia = atoi(campo);
            campo = strtok(NULL, sep);
            fipe[i].valor = atof(campo);
            i++;
        }
    }
    fclose(fp);
    *tam = i;
    return fipe;
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

No* criarNo(t_Fipe *chave) {
    No* novoNo = (No*) malloc(sizeof(No));

    novoNo->dados.nCdg = chave;
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

No* inserirNo(No* no, t_Fipe *chave)
{
    if(no == NULL)
    {
        return criarNo(chave);
    }

    if(strcmp(chave->nCdg, no->dados.nCdg) < 0) {
        no->esquerda = inserirNo(no->esquerda, chave);
    } else if(strcmp(chave->nCdg, no->dados.nCdg) > 0) {
        no->direita = inserirNo(no->direita, chave);
    } else {
        return no; // Não permitir chaves duplicadas
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;

    int balanceamento = calcularBalanceamento(no);

    // Caso de rotação esquerda-esquerda
    if(balanceamento > 1 && chave < no->esquerda->dados.nCdg) {
        return rotacaoDireita(no);
    }

    // Caso de rotação direita-direita
    if(balanceamento < -1 && chave > no->direita->dados.nCdg) {
        return rotacaoEsquerda(no);
    }

    // Caso de rotação esquerda-direita
    if(balanceamento > 1 && chave> no->esquerda->dados.nCdg) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso de rotação direita-esquerda
    if(balanceamento < -1 && chave < no->direita->dados.nCdg) {
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

    if(chave < raiz->dados.nCdg) {
        raiz->esquerda = removerNo(raiz->esquerda, chave);
    } else if(chave > raiz->dados.nCdg) {
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
            raiz->dados.nCdg = temp->dados.nCdg;
            raiz->direita = removerNo(raiz->direita, temp->dados.nCdg);
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
    if(raiz == NULL || raiz->dados.nCdg == chave) {
        return raiz;
    }

    if(chave < raiz->dados.nCdg) {
        return buscarNo(raiz->esquerda, chave);
    }
    else if(chave > raiz->dados.nCdg){
        return buscarNo(raiz->direita, chave);
    }
    return raiz;
}

void percursoEmOrdem(No* raiz) {
    if(raiz != NULL) {
        percursoEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dados.nCdg);
        percursoEmOrdem(raiz->direita);
    }
}

void percursoPreOrdem(No* raiz) {
    if(raiz != NULL) {
        printf("%d ", raiz->dados.nCdg);
        percursoPreOrdem(raiz->esquerda);
        percursoPreOrdem(raiz->direita);
    }
}

void percursoPosOrdem(No* raiz) {
    if(raiz != NULL) {
        percursoPosOrdem(raiz->esquerda);
        percursoPosOrdem(raiz->direita);
        printf("%d ", raiz->dados.nCdg);
    }
}
