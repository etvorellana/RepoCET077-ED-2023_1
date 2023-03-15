#include <stdio.h>
#include <stdlib.h>

/*
    Considere um sistema numérico que não tenha a operação de adição 
    implementada e que você disponha somente dos operadores (funções) 
    sucessor e predecessor. Então, pede-se para escrever uma função 
    recursiva que calcule a soma de dois números x e y através desses dois 
    operadores.
*/

int sucessor(int n)
{
    return ++n;
}

int predecessor(int n)
{
    return --n;
}

int soma(int a, int b)
{
    if( b == 0)
        return a;
    else
        return soma(sucessor(a), predecessor(b));
}

int main(void)
{
    int a, b;

    printf("Entre com um valor inteiro a: ");
    scanf("%d", &a);
    printf("Entre com outro valor inteiro b: ");
    scanf("%d", &b);
    printf("A soma de %d e %d é %d\n", a, b, soma(a, b));
    return(0);
}