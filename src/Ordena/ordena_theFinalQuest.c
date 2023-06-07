#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define N 1000000


typedef struct
{
    int key;
    float val;
}TInfo;

typedef TInfo *PInfo;

void sort(PInfo lista, int n, int ordType);
void selectionSort(PInfo lista, int n);
void bubbleSort(PInfo lista, int n);
void insertionSort(PInfo lista, int n);
void shellSort(PInfo lista, int n);
void quickSort(PInfo lista, int n);

int main(int argc, char *argv[])
{
    PInfo lista;
    clock_t start, end;
    double cpu_time_used;
    int ordType = 1;

    if(argc > 1)
        ordType = atoi(argv[1]);
    
    lista = (PInfo) malloc(N * sizeof(TInfo));
    // Criando uma lista
    for(int i = 0; i < N; i++)
    {
        lista[i].key = rand()%(4*N);
        lista[i].val = 5.0*rand()/RAND_MAX;
        //todo: verificar para nao ter chaves repetidas
    }

    for(int i = 0; i < 10; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("...\n");
    for(int i = 10; i > 0; i--){
        printf("(%d, %.2f) \t", lista[N - i].key, lista[N - i].val);
        if ((i-1) % 5 == 0)
            printf("\n");
    }
    printf("\n------------------\n");

    // Ordenando a lista
    
     
    start = clock();
    /* Do the work. */
    sort(lista, N, ordType);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", cpu_time_used);

    for(int i = 0; i < 10; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("...\n");
    for(int i = 10; i > 0; i--){
        printf("(%d, %.2f) \t", lista[N - i].key, lista[N - i].val);
        if ((i-1) % 5 == 0)
            printf("\n");
    }
    printf("\n------------------\n");

    printf("Se a lista já estiver ordenada\n");
    start = clock();
    /* Do the work. */
    sort(lista, N, ordType);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", cpu_time_used);

    
    for(int i = 0; i < 10; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("...\n");
    for(int i = 10; i > 0; i--){
        printf("(%d, %.2f) \t", lista[N - i].key, lista[N - i].val);
        if ((i-1) % 5 == 0)
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

    for(int i = 0; i < 10; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("...\n");
    for(int i = 10; i > 0; i--){
        printf("(%d, %.2f) \t", lista[N - i].key, lista[N - i].val);
        if ((i-1) % 5 == 0)
            printf("\n");
    }

    printf("\n------------------\n");

    start = clock();
    /* Do the work. */
    sort(lista, N, ordType);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", cpu_time_used);

    for(int i = 0; i < 10; i++){
        printf("(%d, %.2f) \t", lista[i].key, lista[i].val);
        if ((i+1) % 5 == 0)
            printf("\n");
    }
    printf("...\n");
    for(int i = 10; i > 0; i--){
        printf("(%d, %.2f) \t", lista[N - i].key, lista[N - i].val);
        if ((i-1) % 5 == 0)
            printf("\n");
    }

    return 0;
}

void sort(PInfo lista, int n, int ordType)
{
    switch(ordType)
    {
        case 0:
            selectionSort(lista, n);
            break;
        case 1:
            bubbleSort(lista, n);
            break;
        case 2:
            insertionSort(lista, n);
            break;
        case 3:
            shellSort(lista, n);
            break;
        case 4:
            quickSort(lista, n);
            break;
        default:
            printf("Opção inválida\n");
    }
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

void bubbleSort(PInfo lista, int n)
{
    int trocou = 0;
    for(int i = 0; i < n-1; i++)
    {
        trocou = 0;
        for(int j = 0; j < n - 1 - i; j++)
        {   
            if(lista[j].key > lista[j+1].key)
            {   
                trocou = 1;
                TInfo aux = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux;
            }
        }
        if(!trocou) break;
     }
}

void insertionSort(PInfo lista, int n)
{
    for(int i = 1; i < n; i++)
    {
        TInfo aux = lista[i];
        int j = i - 1;
        while(j >= 0 && lista[j].key > aux.key)
        {
            lista[j+1] = lista[j];
            j--;
        }
        lista[j+1] = aux;
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

void quickOrdena(PInfo lista, int start, int end){
    int i, j;
    TInfo aux, pivo;
    i = start;
    j = end - 1;
    pivo = lista[(start + end)/2];
    while(i <= j){
        while(lista[i].key < pivo.key && i < end) i++;
        while(lista[j].key > pivo.key && j > start) j--;
        if(i <= j){
            aux = lista[i];
            lista[i] = lista[j];
            lista[j] = aux;
            i++;
            j--;
        }
    }
    if(j > start) quickOrdena(lista, start, j+1);
    if(i < end) quickOrdena(lista, i, end);
}

void quickSort(PInfo lista, int n)
{
    quickOrdena(lista, 0, n);
}
