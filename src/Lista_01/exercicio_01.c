#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    Um problema típico em ciência da computação consiste em converter um 
    número da sua forma decimal para a forma binária. Por exemplo, o 
    número 12 tem a sua representação binária igual a 1100. A forma mais 
    simples de fazer isso é dividir o número sucessivamente por 2, onde o 
    resto da i-ésima divisão vai ser o dígito i do número binário (da 
    direita para a esquerda). Desenvolva algoritmos recursivos para gerar 
    a representação binária de um número inteiro. Utilize este algoritmo 
    para implementar a função:
*/

void binStr(int n, int pos, char* str)
{
    if(n != 0)
    {
        if (n % 2 == 1)
            str[pos] = '1';
        else
            str[pos] = '0';
        binStr(n / 2, pos - 1, str);
    }
}

char* int2bin(int n)
{
    int strSize = (int) log2(n) + 2;
    printf("strSize = %d \n", strSize);
    char* str = (char*) malloc(strSize * sizeof(char));
    str[strSize - 1] = '\0';
    int pos = strSize - 2;
    binStr(n, pos, str);
    return str;
}

int main(void)
{
    int n;
    char *str;
    do
    {
        printf("Entre com um valor inteiro maior que zero: ");
        scanf("%d", &n);
    } while ( n <= 0);

    str = int2bin(n);
    printf("A representação binária de %d é %s\n", n, str);
    free(str);
    return 0;
}