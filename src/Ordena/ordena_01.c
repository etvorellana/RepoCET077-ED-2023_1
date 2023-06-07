#include <stdio.h>
#include <stdlib.h>
#define N 15
 
typedef struct
{ 
    int key;
    float val;
}TInfo;

typedef TInfo *PInfo;

void selectionSort(PInfo lista, int n);

int main(void)
{
    PInfo lista;
    
    lista = (PInfo) malloc(N * sizeof(TInfo));
    // Criando uma lista
    for(int i = 0; i < N; i++)
    {
        lista[i].key = rand() % 100;
        lista[i].val = 5.0*rand()/RAND_MAX;
        //todo: verificar para nao ter chaves repetidas
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("\n------------------\n");

    // Ordenando a lista

    selectionSort(lista, N);

    for(int i = 0; i < N; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("\n------------------\n");

    return 0;
}

void selectionSort(PInfo lista, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(lista[i].key > lista[j].key)
            {
                TInfo aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }
}
