#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSVSIZE 10000

typedef struct ProjetoDataSet {
    char *nCdg;
    char *codigofp;
    char *marca;
    char *modelo;
    int anoModelo;
    int mesReferencia;
    int anoReferencia;
    float valor;
} t_Fipe;

// Protótipos
t_Fipe *carregaDados(char *arquivo, int *tam);
int buscaElemento(t_Fipe *fipe, int tam, char *idBusca);
t_Fipe *criar_sublista(t_Fipe *lista, int registro, int tam);
void incluir_item(t_Fipe item, t_Fipe **sublista, int *tam);
void remover_elemento(char *id_chave, t_Fipe *lista, int *tam);
int busca_binaria_recursiva(t_Fipe *array, int tam, char *id);
int procurar_id_estoque(t_Fipe *fipe, int n_registros, char *codigo_procurado);

int main() {

    t_Fipe *fipe;
    int tam;
    //int i;

    fipe = carregaDados("datasetFipe.csv", &tam);

    t_Fipe *sublista = NULL;
    int tam_sublista = 0;
    char idBuscado[20];
    int posicao;

    printf("digite o id do produto para criar a sublista: ");
    scanf("%s", idBuscado);
    posicao = buscaElemento(fipe, tam, idBuscado);
    if (posicao >= 0) {
        sublista = criar_sublista(fipe, posicao, tam_sublista + 1);
        tam_sublista++;
        printf("Sublista criada com o produto de id %s.\n", idBuscado);
    } else {
        printf("Produto nao encontrado para criar a sublista.\n");
    }

    printf("digite o id do produto para incluir na sublista: ");
    scanf("%s", idBuscado);
    posicao = buscaElemento(fipe, tam, idBuscado);
    if (posicao >= 0) {
        incluir_item(fipe[posicao], &sublista, &tam_sublista);
        printf("Produto de id %s incluido na sublista.\n", idBuscado);
    } else {
        printf("Produto nao encontrado para incluir na sublista.\n");
    }

    printf("digite o id do produto para remover da sublista: ");
    scanf("%s", idBuscado);
    remover_elemento(idBuscado, sublista, &tam_sublista);

    char id[15];
    printf("digite o id para busca binaria recursiva: ");
    scanf("%s", id);

    int resultado = busca_binaria_recursiva(fipe, tam, id);

    if (resultado != -1) {
        printf("Elemento '%s' encontrado na posicao %d\n", id, resultado);
    } else {
        printf("Elemento '%s' nao encontrado\n", id);
    }

    free(fipe);
    free(sublista);

    return 0;
}

//Carrega Dados do Arquivo
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

int procurar_id_estoque(t_Fipe *fipe, int n_registros, char *codigo_procurado)
{
    int encontrou = 0;

    for (int j = 0; j < n_registros; j++)
    {
        if (strcmp(fipe[j].nCdg, codigo_procurado) == 0)
        {
            encontrou = 1;
            printf("Registro encontrado:\n");
            printf("Num codigo: %s\n", fipe[j].nCdg);
            printf("Codigo fipe: %s\n", fipe[j].codigofp);
            printf("Marca: %s\n", fipe[j].marca);
            printf("Modelo: %s\n", fipe[j].modelo);
            printf("ano do Modelo: %d\n", fipe[j].anoModelo);
            printf("Mes de Referencia: %d\n", fipe[j].mesReferencia);
            printf("Ano de Referencia: %d\n", fipe[j].anoReferencia);
            printf("Valor: %.2f\n", fipe[j].valor);
        }
    }

    if (!encontrou)
    {
        printf("Nenhum registro encontrado com o idEstoque %s\n", codigo_procurado);
        return 0;
    }

    return 1;
}

int buscaElemento(t_Fipe *fipe, int tam, char *idBusca)
{
    for(int i = 0; i < tam; i++)
    {
        // Comparando o ID de busca 'idBusca' com o ID do elemento atual da lista 'fipe'
        if (strcmp(fipe[i].nCdg, idBusca) == 0)
        {
            // Se os IDs são iguais, retorna o índice do elemento encontrado
            return i;
        }
    }
    // Se o elemento não foi encontrado na lista, retorna -1
    return -1;
}


t_Fipe *criar_sublista(t_Fipe *lista, int registro, int tam) {
    // Alocando memória para a sublista com tamanho 'tam' vezes o tamanho de um elemento t_Fipe
    t_Fipe *sublista = (t_Fipe *)malloc(tam * sizeof(t_Fipe));


    if (sublista == NULL) {
        printf("ERRO! Falha ao alocar memoria para sublista!\n");
        exit(1);
    }

    // Copiando o elemento na posição 'registro' da lista original para a primeira posição da sublista
    sublista[0] = lista[registro];

    // Retornando o ponteiro para a sublista criada
    return sublista;
}


void incluir_item(t_Fipe item, t_Fipe **sublista, int *tam) {
    // Incrementa o tamanho da sublista em 1
    (*tam)++;

    // Realoca a memória da sublista para acomodar o novo elemento
    *sublista = (t_Fipe *)realloc(*sublista, (*tam) * sizeof(t_Fipe));

    if (*sublista == NULL) {
        printf("ERRO! Falha ao realocar memoria para sublista!\n");
        exit(1);
    }

    // Insere o novo item na última posição da sublista
    (*sublista)[*tam - 1] = item; //queremos acessar um elemento específico dentro do array
}


void remover_elemento(char *id_chave, t_Fipe *lista, int *tam) {
    // Inicializa o índice do elemento a ser removido como -1 (não encontrado)
    int index = -1;

    // Percorre a lista em busca do elemento com a chave id_chave
    for (int i = 0; i < *tam; i++) {
        if (strcmp(lista[i].nCdg, id_chave) == 0) {
            // Se o elemento for encontrado, guarda o índice e interrompe o loop
            index = i;
            break;
        }
    }

    // Se o elemento foi encontrado
    if (index >= 0) {
        // Desloca os elementos posteriores ao elemento encontrado uma posição à esquerda
        for (int i = index; i < (*tam) - 1; i++) {
            lista[i] = lista[i + 1];
        }
        // Decrementa o tamanho da lista em 1
        (*tam)--;
        printf("Elemento removido com sucesso.\n");
    } else {
        printf("Elemento nao encontrado na sublista.\n");
    }
}


int busca_binaria_recursiva(t_Fipe *array, int tam, char *id) {
    // Caso base: se o tamanho do array for 0, o elemento não foi encontrado
    if (tam == 0) {
        return -1;
    }

    // Encontre a posição do meio do array
    int posicao = tam / 2;
    // Compare o valor na posição do meio com o valor desejado
    int comparacao = strcmp(array[posicao].nCdg, id);

    // Se o valor do meio for menor que o valor desejado
    if (comparacao < 0) {
        // Chame a função recursivamente para a metade direita do array
        return busca_binaria_recursiva(array + posicao + 1, tam - posicao - 1, id);
    }
    // Se o valor do meio for igual ao valor desejado, retorne a posição encontrada
    else if (comparacao == 0) {
        return posicao;
    }
    // Se o valor do meio for maior que o valor desejado
    else {
        // Chame a função recursivamente para a metade esquerda do array
        return busca_binaria_recursiva(array, posicao, id);
    }
}


int busca_binaria_iterativa(t_Fipe *array, int tam, char *id) {
    int inicio = 0;

    // Enquanto o tamanho da parte do array a ser pesquisada for maior que 0
    while (tam > 0) {
        // Encontre a posição do meio da parte do array a ser pesquisada
        int posicao = tam / 2;
        // Compare o valor na posição do meio com o valor desejado
        int comparacao = strcmp(array[inicio + posicao].nCdg, id);

        // Se o valor do meio for menor que o valor desejado
        if (comparacao < 0) {
            // Ajuste o início para depois da posição do meio e diminue o tamanho
            inicio += posicao + 1;
            tam -= posicao + 1;
        }
        // Se o valor do meio for igual ao valor desejado, retorna a posição encontrada
        else if (comparacao == 0) {
            return inicio + posicao;
        }
        // Se o valor do meio for maior que o valor desejado, ajusta o tamanho
        else {
            tam = posicao;
        }
    }

    // Caso o valor desejado não seja encontrado, retorne -1
    return -1;
}

