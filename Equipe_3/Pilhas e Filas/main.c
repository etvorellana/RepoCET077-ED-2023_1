
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <stdbool.h>

#include"datafun.h"

int main()
{
    int tam = CSVSIZE; // Inicializa o tamanho da lista original a partir do valor definido na constante CSVSIZE
    int cap = 100; // Inicializa a capacidade da sublista a ser gerado
    int tamSubFipeValor = 0; // Inicializa o tamanho da sublista como zero
    int *tamSubFipe = &tamSubFipeValor; // Cria um ponteiro para o tamanho da sublista

    srand(time(NULL)); // Inicializa o gerador de n�meros aleat�rios

    t_Fipe *fipe = carregaDados("datasetFipe.csv", &tam); // Carrega os dados do arquivo CSV e atualiza o tamanho do conjunto original
    //t_ListaLinear *fipe = carregaDados("datasetFipe.csv", &tam);

    char idBusca[] = "13265"; // Define o ID a ser buscado na lista original
    int index = buscaPorId(fipe, tam, idBusca); // Busca o registro na lista original pelo ID e retorna seu �ndice
    printf("Id Buscado %s -> Indice %d\n", idBusca, index); // Imprime o resultado da busca

    t_Fipe *subFipe; // Cria um ponteiro para a sublista
    subFipe = criaFipe(cap + 1); // Aloca mem�ria para a sublista

    bool jaAddTodos = false; // Vari�vel de controle para verificar se a sublista j� cont�m todos os registros da lista original

    while (*tamSubFipe < cap && !jaAddTodos) { // Loop para gerar a sublista at� atingir a capacidade m�xima ou incluir todos os registros da lista original
        int index = rand() % tam; // Gera um �ndice aleat�rio da lista original
        bool jaAdd = false; // Vari�vel de controle para verificar se o registro j� foi adicionado a sublista

        // Verifica se o �ndice gerado aleatoriamente j� foi adicionado a sublista
        for (int i = 0; i < *tamSubFipe; i++) {
            if (strcmp(fipe[index].nCdg, subFipe[i].nCdg) == 0) { // Compara os c�digos de cada registro
                jaAdd = true;
                break;
            }
        }

        if (!jaAdd && incRegistro(fipe[index], subFipe, tamSubFipe)) { // Adiciona o registro ao subconjunto, se ainda n�o tiver sido adicionado
            printf("Registro inserido com sucesso!\n");
        } else {
            printf("Registro nao inserido!\n");
        }

        // Verifica se todos os registros da lista original j� foram adicionados a sublista
        jaAddTodos = (*tamSubFipe >= tam);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
    int contadorRemovidos = 0; // Contador de registros removidos
    bool *indicesRemovidos = calloc(*tamSubFipe, sizeof(bool)); // Array para acompanhar quais �ndices j� foram removidos

    // Loop que continua at� que todos os registros da sublista sejam removidos
    while(contadorRemovidos < *tamSubFipe)
    {
        int indice = rand() % *tamSubFipe; // Gera um �ndice aleat�rio da sublista

        // Verifica se o �ndice gerado n�o foi removido anteriormente
        if (!indicesRemovidos[indice]) {
            // Tenta remover o registro do �ndice gerado na sublista
            if (remRegistro(subFipe[indice].nCdg, subFipe, tamSubFipe) != -1) {
                printf("Registro removido com sucesso!\n");
                indicesRemovidos[indice] = true; // Marca o �ndice como removido
                contadorRemovidos++; // Incrementa o contador de registros removidos
            } else {
                printf("Registro nao removido!\n");
            }
        }
    }

    free(indicesRemovidos); // Libera a mem�ria alocada para o array de �ndices removidos

//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chamada da fun��o buscIdOrd
    int indexOrd = buscIdOrd(idBusca, fipe, tam); // Busca o registro na lista original de forma ordenada pelo ID e retorna seu �ndice
    printf("Id Buscado (busca ordenada) %s -> Indice %d\n", idBusca, indexOrd); // Imprime o resultado da busca ordenada
//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chamada da fun��o incRegOrd
    int posInc = incRegOrd(fipe[index], fipe, &tam);
    printf("Registro %s incluido na posicao ordenada %d\n", idBusca, posInc);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chamada da fun��o criaListaLinear
    int capacidade = 100;
    t_ListaLinear *listaLinear = criaListaLinear(capacidade, TRUE);
    printf("Lista linear criada com capacidade %d e ordenada: %d\n", listaLinear->cap, listaLinear->ehOrd);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*  // Chama a fun��o insereNaLista com um registro e a sublista
    int registrosInseridos = 0;
    for (int i = 0; i < cap; i++) {
        int index;
        bool registroJaAdicionado;
        do {
            index = rand() % tam;
            int posicaoEncontrada = BuscaNaListaLinear(fipe[index].nCdg, listaLinear);
            registroJaAdicionado = (posicaoEncontrada >= 0);
        } while (registroJaAdicionado);
        int resultadoInsercao = insereNaLista(fipe[index], listaLinear, 1); // 1 indica que a lista � ordenada
        if (resultadoInsercao) {
            printf("Registro inserido com sucesso!\n");
            registrosInseridos++; // Incrementa o contador de registros inseridos
        } else {
            printf("Registro nao inserido!\n");
        }
    }
    printf("Total de registros inseridos na lista linear: %d\n", registrosInseridos); // Imprime o total de registros inseridos na lista linear
 *//*   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chama a fun��o BuscaNaListaLinear com o ID de busca e a sublista
    char idChave[] = "35214";
    int posicaoEncontrada = BuscaNaListaLinear(idChave, listaLinear);
    if (posicaoEncontrada >= 0) {
        printf("Registro encontrado na posicao: %d\n", posicaoEncontrada);
    } else {
        printf("Registro nao encontrado. Posicao sugerida para insercao: %d\n", -posicaoEncontrada);
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
    //cria fila Linear
    t_FilaLinear *fila = criaFilaLinear(capacidade);

    if (fila == NULL) {
        printf("Falha ao criar a fila.\n");
        return 1;
    }

    printf("\nFila criada com sucesso! Capacidade: %d\n", fila->cap);

    printf("\nAdicionar elementos a fila.\n");
    int aux;
    for (int i = 0; i<90; i++){
        index = rand()%tam;
        aux = InserirNaFila(fila, fipe[index]);
        if (aux==1){
            printf("Elemento adicionado com sucesso!\n");
        }else{
            printf("Nao foi possivel adicionar o Elemento!\n");
        }
    }

    printf("\nQuantidade de Elementos na fila: %d\n", fila->fim-fila->ini);

    t_Fipe* trFila;
    printf("\nRemovendo 10 elementos da elementos da fila.\n\n");
    for(int i=0; i<10; i++){
        trFila = RemoveDaFila(fila);
        if (trFila != NULL){
            printf("Elemento removido com sucesso! Codigo do elemento removido: %s --\n", trFila->nCdg);
        } else {
            printf("Erro ao remover elemento!\n");
        }
    }

    printf("\nQuantidade de Elementos na fila: %d\n", fila->fim-fila->ini);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // cria pilha linear
    t_pilhaLinear *pilha = criaPilhaLinear(capacidade);

    if (pilha == NULL) {
        printf("Falha ao criar a pilha.\n");
        return 1;
    }

    printf("\nPilha criada com sucesso! Capacidade: %d\n", pilha->cap);

    printf("\nAdicionar Elementos a Pilha\n");

    for (int i = 0; i<150; i++){
        index = rand()%tam;
        if(insereNaPilha(fipe[index], pilha)){
            printf("Elemento empilhado com sucesso!\n");
        }
        else{
            printf("Erro ao Empilhar!\n\n");
            break;
        }
    }
    printf("\nQuantidade de Elementos na fila: %d\n", pilha->topo);

    printf("\Esvaziando a pilha.\n");

    t_Fipe* trPilha;
    for (int i=0; i<150; i++){
        trPilha = RemoverdaPilha(pilha);
        if (trPilha != NULL){
            printf("Elemento %s removido com sucesso.\n", trPilha->nCdg);
        } else {
            printf("Nao foi possivel remover! Pilha Vazia!\n\n");
            break;
        }
    }

    printf("\nQuantidade de Elementos na fila: %d\n", pilha->topo);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
//Feita por Henio
    if(estacheia(pilha)== -1 ){
        printf("n�o empilha");
    }
    else{
            printf("pilha vazia , vamos empilhar\n\n");
    for(int i = 0; i < 100; i++) {
    int index = rand() % (tam+1);
    printf("--[%d]-- %s\n",index,fipe[index].modelo);
    empilhar(fipe[index],pilha,100);
    }
    }
    if(estacheia(pilha))
    {
        printf("\nPilha Encheu\n");
    }
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    limpaFipe(fipe, tam); // Libera a mem�ria alocada para a lista original
    limpaFipe(subFipe, *tamSubFipe); // Libera a mem�ria alocada para a sublista
    free(tamSubFipe); // Libera a mem�ria alocada para o ponteiro que armazena o tamanho da sublista
    limpaListaLinear(listaLinear); // Limpa a lista linear
    // Liberar mem�ria alocada
    free(fila->dados);
    free(fila);
    free(pilha->pilha);
    free(pilha);

    printf("\nPrograma execultado com sucesso!!!\n\n");

    return 0;

}
