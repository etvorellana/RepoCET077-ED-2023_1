#include <stdio.h>
#include <stdlib.h>

/*
    Implemente uma função recursiva soma(n) que calcula o somatório dos n 
    primeiros números inteiros.
*/

int somaNRec(int n)
{
    if(n == 0)
        return 0;
    return n + somaNRec(n-1);
}

int somaN(int n)
{
    int soma = 0;
    for(int i = 1; i <= n; i++)
        soma += i;
    return soma;
}

int main(void)
{
    printf("Soma Recursiva: \t");
    printf("%d", somaNRec(0));
    for(int i = 1; i < 10; i++)
        printf(", %d", somaNRec(i));
    printf("\n");

    printf("Soma não Recursivo: \t");
    printf("%d", somaN(0));
    for(int i = 1; i < 10; i++)
        printf(", %d", somaN(i));
    printf("\n");
    return 0;
}