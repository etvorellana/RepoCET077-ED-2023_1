#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    A seguinte função aloca um array de valores inteiros de tamanho n 
    e preenche o mesmo com valores x inteiros, gerados de forma aleatória, 
    entre os limites a e b (a <= x <= b). Utilize esta função para gerar 
    um array de 10 posições e:
*/

int* randArray(int n, int a, int b)
{
    int* vet = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
    {
        vet[i] = a + rand()%(b - a + 1);
    }
    return vet;
}

/*
    Implemente uma função recursiva que retorna o maior valor de um array 
    de inteiros;
*/

int vetMax(int* vet, int n)
{
    if(n == 1)
        return vet[0];
    else
    {
        int max = vetMax(&vet[1], n - 1);
        max = vet[0] > max ? vet[0]:max; 
        return max;
    }
}

/*
    Implemente uma função recursiva que retorna a soma dos elementos do array;
*/
int vetSoma(int* vet, int n)
{
    if (n == 1)
        return vet[0];
    else
        return vet[0] + vetSoma(&vet[1], n - 1);
}


/* 
    Implemente uma função recursiva que retorna se um determinado valor 
    faz parte do array. Desta forma a função retorna verdadeiro o falso
*/

int valInVet(int val, int* vet, int n)
{
    if(n == 1)
        return val == vet[0];
    if (val == vet[0])
        return 1;
    else
        return valInVet(val, &vet[1], n-1 );
}

/* 
    Modifique a função anterior para que o retorno da função indique 
    em qual posição se encontra o valor no array. Se o valor não fizer 
    parte do array a função retorna o tamanho do array;
*/

int posValInVet(int val, int* vet, int n)
{
    if (n == 1) 
        if (val == vet[0])
            return 0;
        else
            return 1;
    
    if (val == vet[0])
        return 0;
    else
        return 1 + posValInVet(val, &vet[1], n - 1);

}

int main(void)
{
    srand(time(NULL));
    int *x = randArray(10, 0, 100);
    printf("[ ");
    for(int i = 0; i < 10; i++)
    {
        printf("%d", x[i]);
        if(i == 4)
        {
            printf("\n  ");
            continue;
        }
        if(i < 9)
            printf(", ");
    }
    printf(" ]\n");
    
    int max = x[0];
    for(int i = 1; i < 10; i++)
        if (max < x[i])
            max = x[i];
    printf("O maior valor do array é: %d\n", vetMax(x, 10));
    if (max == vetMax(x, 10))
        printf("A busca recursiva do máximo retornou o resultado coreto\n");
    else
        printf("A busca recursiva do máximo não retornou o resultado coreto\n");

    int soma = 0;
    for(int i = 0; i < 10; i++)
        soma += x[i];
    printf("A soma dos elementos do array é: %d\n", vetSoma(x, 10));
    if (soma == vetSoma(x, 10))
        printf("A soma recursiva retornou o resultado coreto\n");
    else
        printf("A soma recursiva não retornou o resultado coreto\n");
    printf("Procurando o elemento 101 que não pertence ao array\n");

    if (valInVet(101, x, 10))
        printf("A busca retornou um resultado errado!!!\n");
    else
        printf("A busca retornou o resultado esperado.\n");
    printf("Procurando um elemento que pertence ao array\n");
    if (!valInVet(x[5], x, 10))
        printf("A busca retornou um resultado errado!!!\n");
    else
        printf("A busca retornou o resultado esperado.\n");

    printf("Procurando o elemento 101 que não pertence ao array\n");
    if (posValInVet(101, x, 10) != 10)
        printf("A busca retornou um resultado errado!!!\n");
    else
        printf("A busca retornou o resultado esperado.\n");
    printf("Procurando um elemento que pertence ao array\n");
    if (posValInVet(x[5], x, 10) != 5)
        printf("A busca retornou um resultado errado!!!\n");
    else
        printf("A busca retornou o resultado esperado.\n");

    free(x);
}