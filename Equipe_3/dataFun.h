#ifndef FIPE_DATA_H
#define FIPE_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSVSIZE 12000
#define TRUE 1
#define FALSE 0

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

typedef struct {
    t_Fipe *lista;
    int cap; //capacidade
    int tam; //tamanho
    int ehOrd; //True se for ordenada
} t_ListaLinear;

typedef struct {
    t_Fipe *pilha;
    int cap; //capacidade da pilha
    int topo; //topo da pilha
} t_pilhaLinear;

typedef struct {
    t_Fipe *dados;
    int cap; //capacidade
    int ini; //indice do primeiro elemento da fila
    int fim; //indice do ultimo elemento da fila
} t_FilaLinear;

t_Fipe *carregaDados(char *arquivo, int *tam);
void limpaFipe(t_Fipe *fipe, int tam);
void limpaRegistro(t_Fipe fipe);
int buscaPorId(t_Fipe *fipe, int tam, char *idBusca);
t_Fipe* criaFipe(int cap);
int incRegistro(t_Fipe fipe, t_Fipe *lista, int *tam);
int remRegistro(char *idBusca, t_Fipe *lista, int *tam);
int buscIdOrd(char *idBusca, t_Fipe *fipe, int tam);
int incRegOrd(t_Fipe fipe, t_Fipe *lista, int *tam);
void printRegistro(t_Fipe fipe);
void printLista(t_Fipe *fipe, int tam);
int BuscaNaListaLinear(char *idBusca, t_ListaLinear* fipe);
int remOrdFipe(char* idBusca, t_Fipe* fipe, int* tam);
t_ListaLinear *criaListaLinear(int cap, int ehOrd);
int insereNaLista(t_Fipe fipe, t_ListaLinear *lista, int ordenada);
void limpaListaLinear(t_ListaLinear *listaLinear);
//feita por henio
int estacheia ( t_pilhaLinear *p );
//void empilhar(t_Fipe lk, t_pilhaLinear *p, int cap);
//void RemoverdaPilha(t_Fipe lk, t_pilhaLinear *p, int topo);
t_Fipe* RemoverdaPilha(t_pilhaLinear *p);
int InserirNaFila (t_FilaLinear *fila, t_Fipe fipe);
t_Fipe* RemoveDaFila (t_FilaLinear* fila);
int insereNaPilha(t_Fipe fipe, t_pilhaLinear* pilha);
t_FilaLinear *criaFilaLinear(int cap);
t_pilhaLinear *criaPilhaLinear(int cap);

#endif
