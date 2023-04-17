#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bidefun.h"

int main(void) {
  TSongs *acervo;
  int tam = 0;

  acervo = carregaDados("Data/newSongs.csv", &tam);

  // MENU
  printf("Bem vindo ao seu criador de estrutura de dados favorito!\n");
  printf("\nPressione enter para iniciar!");
  getchar();
  while (1) {
    system("clear");
    printf("\nDeseja Criar uma Pilha(1) ou uma Fila(2) ou encerrar o "
           "programa?(0)\n");
    int e = 0, pe = 0, fe = 0;
    scanf("%d", &e);
    setbuf(stdin, NULL);

    if (e == 1) {
      printf("Qual a Capacidade da pilha?\n");
      scanf("%d", &pe);
      setbuf(stdin, NULL);

      TPilhaLinear *pilha = criaPilhaLinear(pe);
      printf("Quantos itens deseja adicionar a pilha?\n");
      scanf("%d", &pe);
      setbuf(stdin, NULL);

      if (pilha->cap > pe) {
        for (int i = 0; i < pe;) {
          int aleatorio = rand() % 9000;
          if (BuscaPorRank(aleatorio, pilha->pilha, tam) == tam) {
            if (pushTSongs(acervo[aleatorio], pilha))
              i++;
          }
        }
        while (pilha->topo != pilha->cap) {
          while (1) {
            if (pilha->cap > pe) {
              printf("\nSua pilha tem %d espaços vazios", pilha->cap - pe);
              printf("\nDeseja adicionar mais X valores(1) ou preencher "
                     "completamente?(2)\n");
              int se;
              scanf("%d", &se);
              setbuf(stdin, NULL);

              if (se == 1) {
                while (1) {
                  printf("\nQuantos espaços deseja adicionar?\n");
                  int ep;
                  scanf("%d", &ep);
                  setbuf(stdin, NULL);

                  if (ep > pilha->cap - pe) {
                    printf("\nSeu limite e %d, nao pode ser mais!",
                           pilha->cap - pe);
                  } else {
                    for (int i = 0; i < ep;) {
                      int aleatorio = rand() % 9000;
                      if (BuscaPorRank(aleatorio, pilha->pilha, tam) == tam)
                        if (pushTSongs(acervo[aleatorio], pilha))
                          i++;
                    }
                    pe += ep;
                    break;
                  }
                }
              }
              if (se == 2) {
                printf("\nSerao adicionados %d itens a pilha!\n",
                       pilha->cap - pe);
                for (int i = 0; i < (pilha->cap - pe);) {
                  int aleatorio = rand() % 9000;
                  if (BuscaPorRank(aleatorio, pilha->pilha, tam) == tam)
                    if (pushTSongs(acervo[aleatorio], pilha))
                      i++;
                }
                pe += pilha->cap - pe;
              }
              if (se != 1 && se != 2) {
                printf("Escolha inválida!\nSelecione novametne!\n");
              }
              if (pilha->cap <= pe) {
                printf("\nSua pilha esta cheia agora, iremos esvaziar ela!");
                while (pilha->topo < 0)
                  popTSongs(pilha);
                printf("\nPilha Esvaziada!");
                printf("\nPressione enter para voltar ao menu principal!");
                getchar();
                setbuf(stdin, NULL);
                break;
              }
            } else if (pilha->cap < pe) {
              printf("Sua capacidade e %d, nao pode ser mais!\n", pilha->cap);
            }
          }
        }
      } else if (pilha->cap == pe) {
        printf("A pilha foi criada com %d elementos", pe);
        for (int i = 0; i < pe;) {
          int aleatorio = rand() % 9000;
          if (BuscaPorRank(aleatorio, pilha->pilha, tam) == tam) {
            if (pushTSongs(acervo[aleatorio], pilha) != pilha->cap)
              i++;
          }
        }
        printf("\nSua pilha esta cheia agora, iremos esvaziar ela!");
        while (pilha->topo < 0)
          popTSongs(pilha);
        printf("\nPilha Esvaziada!");
        printf("\nPressione enter para voltar ao menu principal!");
        getchar();
        setbuf(stdin, NULL);
      }
      free(pilha);
    }

    if (e == 2) {
      printf("Qual a Capacidade da fila?\n");
      scanf("%d", &fe);
      setbuf(stdin, NULL);

      TFilaLinear *fila = criaFila(fe);
      printf("Quantos itens deseja adicionar a fila?\n");
      scanf("%d", &fe);
      setbuf(stdin, NULL);
      int aleatorio;

      if (fila->cap > fe) {
        int i;
        for (int i = 0; i < fe;) {
          int aleatorio = rand() % 9000;
          if (BuscaPorRank(aleatorio, fila->fila, tam) == tam) {
            if (enqueue(acervo[aleatorio], fila) != fila->cap)
              i++;
          }
        }
        while (fila->ini != fila->cap) {
          while (1) {
            if (fila->cap > fe) {
              printf("\nSua fila tem %d espaços vazios", fila->cap - fe);
              printf("\nDeseja adicionar mais X valores(1) ou preencher "
                     "completamente?(2)\n");
              int se;
              scanf("%d", &se);
              setbuf(stdin, NULL);

              if (se == 1) {
                while (1) {
                  printf("\nQuantos espaços deseja adicionar?\n");
                  int ep;
                  scanf("%d", &ep);
                  setbuf(stdin, NULL);

                  if (ep > fila->cap - fe) {
                    printf("\nSeu limite e %d, nao pode ser mais!",
                           fila->cap - fe);
                  } else {
                    for (i = 0; i < ep;) {
                      int aleatorio = rand() % 9000;
                      if (BuscaPorRank(aleatorio, fila->fila, tam) == tam)
                        if (enqueue(acervo[aleatorio], fila) != fila->cap)
                          i++;
                    }
                    fe += ep;
                    break;
                  }
                }
              }
              if (se == 2) {
                printf("\nSerao adicionados %d itens a fila!\n",
                       fila->cap - fe);
                for (int i = 0; i < fe;) {
                  int aleatorio = rand() % 9000;
                  if (BuscaPorRank(aleatorio, fila->fila, tam) == tam) {
                    if (enqueue(acervo[aleatorio], fila) != fila->cap)
                      i++;
                  }
                }
              }
              if (se != 1 && se != 2) {
                printf("Escolha inválida!\nSelecione novametne!\n");
              }
              if (fila->cap <= fe) {
                printf("\nSua fila esta cheia agora, iremos esvaziar ela!");
                while (fila->ini != fila->fim)
                  dequeue(fila);
                printf("\nFila Esvaziada!");
                printf("\nPressione enter para voltar ao menu principal!");
                getchar();
                setbuf(stdin, NULL);
                break;
              }
            } else if (fila->cap < fe) {
              printf("Sua capacidade e %d, nao pode ser mais!\n", fila->cap);
            }
          }
        }
      } else if (fila->cap == fe) {
        printf("A fila foi criada com %d elementos", fe);
        for (int i = 0; i < fe;) {
          int aleatorio = rand() % 500;
          if (BuscaPorRank(aleatorio, fila->fila, tam) == tam) {
            if (enqueue(acervo[aleatorio], fila) != fila->cap)
              i++;
          }
        }
        printf("\nSua fila esta cheia agora, iremos esvaziar ela!");
        while (fila->ini != fila->fim)
          dequeue(fila);
        printf("\nFila Esvaziada!");
        printf("\nPressione enter para voltar ao menu principal!");
        getchar();
        setbuf(stdin, NULL);
      }
      free(fila);
    }
    if (e == 0) {
      printf("Obrigado por utilizar, volte sempre!<3");
      break;
    }
    if (e != 1 && e != 2 && e != 0) {
      printf("\nEscolha inválida!\nSelecione novametne!");
    }
  }
  printf("Obrigado por utilizar, volte sempre!<3");
  limpaAcervo(acervo, tam);
  return 0;
}
