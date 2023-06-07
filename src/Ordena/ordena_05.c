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
void selectionSort_SbS(PInfo lista, int n);
void bubbleSort_SbS(PInfo lista, int n);
void insertionSort_SbS(PInfo lista, int n);
void shellSort(PInfo lista, int n);

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

    //selectionSort(lista, N);
    //selectionSort_SbS(lista, N);
    //bubbleSort_SbS(lista, N);
    //insertionSort_SbS(lista, N);
    shellSort(lista, N);


    for(int i = 0; i < N; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("\n------------------\n");

    printf("Se a lista já estiver ordenada\n");
    //selectionSort_SbS(lista, N);
    //bubbleSort_SbS(lista, N);
    //insertionSort_SbS(lista, N);
    shellSort(lista, N);

    
    for(int i = 0; i < N; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }

    printf("\n------------------\n");
    printf("Pior caso: a lista ordenada em ordem inversa\n");

    for(int i = 0; i < N/2; i++)
    {
        TInfo aux = lista[i];
        lista[i] = lista[N-i-1];
        lista[N-i-1] = aux;
    }

    for(int i = 0; i < N; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }

    printf("\n------------------\n");

    //bubbleSort_SbS(lista, N); 
    //insertionSort_SbS(lista, N);
    shellSort(lista, N);
    
    for(int i = 0; i < N; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }

    return 0;
}

void selectionSort(PInfo lista, int n)
{
    for(int i = 0; i < (n-1); i++)
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

void selectionSort_SbS(PInfo lista, int n)
{
    int comp = 0, trocas = 0;
    for(int i = 0; i < n; i++)
    {
        printf("Iteração %d: \n", i);
        for(int j = i+1; j < n; j++)
        {   
            comp++;
            if(lista[i].key > lista[j].key)
            {   
                trocas++;
                TInfo aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
        for(int k = 0; k < n; k++)
        {
            printf("(%d, %.2f) \t", lista[k].key, lista[k].val);
            if ((k+1) % 5 == 0)
                printf("\n");
        }
        printf("Comp = %d, trocas = %d\n", comp, trocas);
    }
}

void bubbleSort_SbS(PInfo lista, int n)
{
    int trocou = 0;
    int comp = 0, trocas = 0;
    for(int i = 0; i < n-1; i++)
    {
        trocou = 0;
        printf("Iteração %d: \n", i);
        for(int j = 0; j < n - 1 - i; j++)
        {   
            comp++;
            if(lista[j].key > lista[j+1].key)
            {   
                trocas++;
                trocou = 1;
                TInfo aux = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux;
            }
        }
        for(int k = 0; k < n; k++)
        {
            printf("(%d, %.2f) \t", lista[k].key, lista[k].val);
            if ((k+1) % 5 == 0)
                printf("\n");
        }
        printf("Comp = %d, trocas = %d\n", comp, trocas);
        if(!trocou) break;
     }
}

void insertionSort_SbS(PInfo lista, int n)
{
    int comp = 0, trocas = 0;
    for(int i = 1; i < n; i++)
    {
        printf("Iteração %d: \n", i);
        TInfo aux = lista[i];
        int j = i - 1;
        comp++;
        while(j >= 0 && lista[j].key > aux.key)
        {
            comp++;
            trocas++;
            lista[j+1] = lista[j];
            j--;
        }
        lista[j+1] = aux;
        for(int k = 0; k < n; k++)
        {
            printf("(%d, %.2f) \t", lista[k].key, lista[k].val);
            if ((k+1) % 5 == 0)
                printf("\n");
        }
        printf("Comp = %d, trocas = %d\n", comp, trocas);
    }
}   

void shellSort(PInfo lista, int n)
{   
    int h = 1;
    while(h < n) h = 3*h + 1;
    while(h > 1)
    {
        h = h/3;
        for(int i = h; i < n; i++)
        {
            TInfo aux = lista[i];
            int j = i - h;
            while(j >= 0 && lista[j].key > aux.key)
            {
                lista[j+h] = lista[j];
                j = j - h;
            }
            lista[j+h] = aux;
        }
    }
}