#include <stdio.h>
#include <stdlib.h>

/*
    A sequência de Fibonacci é uma sequência de elementos f1, …, fn, definida 
    do seguinte modo: f1 = 0; f2 = 1; fj = fj-1 + fj-2 para j > 2.
    a. Elaborar um algoritmo recursivo para calcular a sequência de Fibonacci 
        para qualquer valor positivo de n;
    b. Construir uma versão não recursiva deste algoritmo;
*/

int fibonacciRec(int n)
{
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    else
        return fibonacciRec(n-1) + fibonacciRec(n-2);
}

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;    
    int fj=1, fjm1 = 0, fjm2 = 0;
    for(int i = 2; i <= n; i++)
    {
        fjm2 = fjm1;
        fjm1 = fj;
        fj = fjm1 + fjm2;
    }
    return fj;
}

int main(void)
{
    printf("Fibonacci Recursivo: \t\t");
    printf("%d", fibonacciRec(0));
    for(int i = 1; i < 10; i++)
        printf(", %d", fibonacciRec(i));
    printf("\n");

    printf("Fibonacci não Recursivo: \t");
    printf("%d", fibonacci(0));
    for(int i = 1; i < 10; i++)
        printf(", %d", fibonacci(i));
    printf("\n");

    return 0;
}