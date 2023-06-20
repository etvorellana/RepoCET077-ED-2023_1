#ifndef FIPE_DATA_H
#define FIPE_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSVSIZE 12000
#define TRUE 1
#define FALSE 0

typedef struct ProjetoDataSet
{
  char *nCdg;
  char *codigofp;
  char *marca;
  char *modelo;
  int anoModelo;
  int mesReferencia;
  int anoReferencia;
  float valor;
} t_Fipe;


#endif