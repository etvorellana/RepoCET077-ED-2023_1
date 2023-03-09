
#include <stdlib.h>

int* randArray(int n, int a, int b)
{
    int* vet = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
    {
        vet[i] = a + rand()%(b - a + 1);
    }
    return vet;
}

