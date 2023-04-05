#include "struct.h"

Games* carregaDados(char *fileName, int *tam);

Games* IniciaLista(int capacidade);

void limpaJogos(Games *jogos, int tam);

void limpaJogos02(Games *jogos, int Pos);

int buscaPorId(int ID, Games* lista, int *tam);

int incJogo(Games jogos, Games* jogos02, int* tam);

int remJogo(Games jogo, Games* jogos02, int* tam);

int buscaBinPorId(int ID, Games *lista, int ini, int fim);

int remJogoOrdenado(Games jogo, Games* jogos03, int* tam);

int incJogoOrdenado(Games jogo, Games* jogos03, int* tam);
